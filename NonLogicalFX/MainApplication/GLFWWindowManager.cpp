//
//  GLFWWindowManager.cpp
//  NonLogicalFX
//
//  Created by Oleg Utkin on 5/26/15.
//  Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <vector>
#include <GLM/glm.h>
#include <GLM/gtx/transform.h>
#include <GLM/gtc/type_ptr.h>
#include <GLM/gtx/string_cast.h>
#include <OpenGL/OpenGL.h>
#include <random>
#include "GLFWWindowManager.h"
#include "Skybox.h"
#include "SimpleCube.h"


struct {
    bool state;
    GLFWWindowManager *w;
} state;

GLFWWindowManager::GLFWWindowManager(char const *title, int width, int height) {
    setUpOpenGLProfile();
    makeWindow(title, width, height);
    std::cout << std::endl;

    // Setting up callbacks
    handleCallbacks();

    // Standard settings
    setUpOpenGL();

    // Initiating shader library for our obejects
    ShaderLibrary::initLibrary();

    this->screen = new SGViewPortPassThru();

    this->diffusePass = new TextureFramebuffer();
    this->depthPass = new TextureFramebuffer();
    this->occlusionPass = new TextureFramebuffer();
    this->occlusionPass2 = new TextureFramebuffer();
    this->normalPass = new TextureFramebuffer();
    this->screenPass = RawFrameBuffer::defaultFramebuffer();

    // Building a scene out of primitives
    buildScene();

    root.setGlobalUniformUpdateCallback([this](BaseMaterial *material){
        this->handleShaderUniformUpdate(material);
    });

    this->uvTexture = new FileTexture("UVTEST.png");
    this->blurShader = new FXShader("blur");
    this->occlusionShader = new FXShader("SSAO");
    this->normalMapper = new FileShader("NormalMapper");
    this->compositor = new FXShader("Composite");

    int nS = 6;
    srand(glfwGetTime() * 1000);
    std::vector<float> texture;
    for(int i = 0; i < nS * nS; i++) {
        float x = (float)rand()/(float)(RAND_MAX);
        texture.push_back(x);
    }
    this->noise = new RawTexture(GL_TEXTURE_2D,GL_R8,nS,nS,0,GL_RED,GL_FLOAT,&texture[0]);
    this->noise->bind(GL_TEXTURE0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    this->noise->unbind();

    makeSSAOKernel();

    screen->setFXShader(blurShader);
}

void GLFWWindowManager::makeSSAOKernel() {
    std::vector<float> kernel;
    int kernelSize = 80;
    for(int i = 0; i < kernelSize; i++) {
        float x = (float)rand()/(float)(RAND_MAX) * 2.0 - 1.0;
        float y = (float)rand()/(float)(RAND_MAX) * 2.0 - 1.0;
        glm::vec3 kern = normalize(glm::vec3(x,y,0.0));

        float scale = float(i) / float(kernelSize);
        scale = scale * scale;

        scale = 0.1f*(1.0-scale) + 1.0f*(scale);
        kern = kern * scale;

        kernel.push_back(kern.x);
        kernel.push_back(kern.y);
        kernel.push_back(0);
    }
    this->kernel = kernel;
}

void GLFWWindowManager::buildScene() {

    // Setting up camera
    glm::vec3 eye(0.0f, 0.0f, 30.0f);
    glm::vec3 up(0.0f, 1.0f, 0.0f);
    glm::vec3 center(0.0f);
    root.V = glm::lookAt(eye, center, up);

    // Setting up projection
    updateProjectionMatrix();

    skybox = new SGGroup();
    scene = new SGGroup();
    root.addChild(skybox);
    root.addChild(scene);

    // Adding skybox as a skybox
    skybox->addChild(new Skybox("skybox.jpg"));

    // Add a scene which consists of just a cube
    scene->addChild(new SimpleCube());

    scene->applyTransform(glm::rotate(0.3f, glm::vec3(0.0, 1.0, 0.0)));
}

void GLFWWindowManager::updateProjectionMatrix() {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    float aspect = (float) width / (float) height;
    projectionMat = glm::perspective(20.0f, aspect, 1.0f, 1000.0f);
    inverseProjection = glm::inverse(projectionMat);
    root.P = projectionMat;

    diffusePass->updateTexture(
            new RawTexture(GL_RGB16, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL)
    );
    diffusePass->attachTo(GL_COLOR_ATTACHMENT0);

    normalPass->updateTexture(
            new RawTexture(GL_RGB16, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL)
    );
    normalPass->attachTo(GL_COLOR_ATTACHMENT0);

    depthPass->updateTexture(
            new RawTexture(GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL)
    );
    depthPass->attachTo(GL_DEPTH_ATTACHMENT);

    occlusionPass->updateTexture(
            new RawTexture(GL_RGB16, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL)
    );
    occlusionPass->attachTo(GL_COLOR_ATTACHMENT0);
    occlusionPass2->updateTexture(
            new RawTexture(GL_RGB16, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL)
    );
    occlusionPass2->attachTo(GL_COLOR_ATTACHMENT0);
}


#pragma MARK - Window Management

void GLFWWindowManager::handleCallbacks() {
    state.w = this;

    // Handle key presses
    glfwSetKeyCallback(window, [](GLFWwindow *w, int k, int s, int a, int m) {
        SGRoot &root = state.w->root;
        if (k == GLFW_KEY_ESCAPE && a == GLFW_PRESS) {
            glfwSetWindowShouldClose(w, GL_TRUE);
        }

        if (a == GLFW_RELEASE) return;

        switch(k) {
            case 'S': {

            }
            case 'R': {
                state.w->reload();
            }
            default:
                break;
        }
    });

    glfwSetWindowSizeCallback(window, [](GLFWwindow *w, int x, int y) {
        state.w->updateProjectionMatrix();
    });
}

void GLFWWindowManager::makeWindow(char const *title, int width, int height) {
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if(!window) { exit(EXIT_FAILURE); }

    glfwMakeContextCurrent(window);
    printf("Supported OpenGL is %s\n", (const char*)glGetString(GL_VERSION));
    printf("Supported GLSL is %s\n", (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void GLFWWindowManager::runEventLoop() {
    while(!glfwWindowShouldClose(window)) {
        update();
        draw();
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
}




#pragma mark - Drawing/Animation

void GLFWWindowManager::update() {
    //float time = glfwGetTime() * 0.5;
    float time =  0.5;

    glm::vec3 eye(0.0f, 20*sin(time), 30.0f);
    glm::vec3 up(0.0f, 1.0f, 0.0f);
    glm::vec3 center(0.0f);
    root.V = glm::lookAt(eye, center, up);

    //scene->applyTransform(glm::rotate(0.5f, glm::vec3(0.0, 1.0, 0.0)));
}

void GLFWWindowManager::handleShaderUniformUpdate(BaseMaterial *material) {
    GLuint tLoc = material->getShader()->uniform("iGlobalTime");
    float time = glfwGetTime();
    glUniform1f(tLoc, time);
}

void GLFWWindowManager::draw() {
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    // ===========================================================================
    /* Make our background black */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Geometry Pass ==============
    diffusePass->bind(GL_FRAMEBUFFER);
    diffusePass->clear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    root.render();
    diffusePass->unbind();

    depthPass->bind(GL_FRAMEBUFFER);
    depthPass->clear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glDrawBuffer(GL_DEPTH_ATTACHMENT);
    root.render();
    depthPass->unbind();

    normalPass->bind(GL_FRAMEBUFFER);
    normalPass->clear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    root.renderWithShader(normalMapper);
    normalPass->unbind();

    // Occlusion Pass
    occlusionPass->bind(GL_FRAMEBUFFER);
    occlusionPass->clear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    screen->setFXShader(occlusionShader);
    screen->setTextures({
            MaterialTextureUnit("noiseMap", noise),
            MaterialTextureUnit("normalMap", normalPass->getAttachedTexture()),
            MaterialTextureUnit("depthMap", depthPass->getAttachedTexture())
    });
    screen->setUniforms([this, width, height](RawShader* s) {
        glUniformMatrix4fv(s->uniform("_Projection"), 1, GL_FALSE, glm::value_ptr(projectionMat));
        glUniformMatrix4fv(s->uniform("unProj"), 1, GL_FALSE, glm::value_ptr(inverseProjection));
        glUniform3f(s->uniform("iResolution"), (float)width, (float)height, 0);
        glUniform3fv(s->uniform("_SampleKernel"), 80, &this->kernel[0]);
        //glUniform1f(s->uniform("_Radius"), 0.1);
    });
    screen->render();
    occlusionPass->unbind();

    occlusionPass2->bind(GL_FRAMEBUFFER);
    occlusionPass2->clear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    screen->setFXShader(blurShader);
    screen->setTextures({
            MaterialTextureUnit("passThrough", occlusionPass->getAttachedTexture())
    });
    screen->setUniforms([this, width, height](RawShader* s) {
        glUniform2f(s->uniform("dir"), 1, 0);
    });

    screen->render();
    occlusionPass2->unbind();

    // Image Pass ===================
    screenPass->bind(GL_FRAMEBUFFER);
    screen->setFXShader(compositor);
    screen->setTextures({
            MaterialTextureUnit("diffuseMap", diffusePass->getAttachedTexture()),
            MaterialTextureUnit("occlusionMap", occlusionPass2->getAttachedTexture())
    });
    screen->render();

    glfwSwapBuffers(window);
    // ===========================================================================
}





#pragma MARK - OpenGL Settings

void GLFWWindowManager::setUpOpenGL() {
    glfwSwapInterval(1);
    glClearColor(0, 0, 0, 0);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}

void GLFWWindowManager::setUpOpenGLProfile() {
    // Setting up core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    glfwWindowHint(GLFW_DOUBLEBUFFER, 1);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    glfwWindowHint(GLFW_SAMPLES, 2);
}

void GLFWWindowManager::reload() {
    root.reload();
    blurShader->reload();
    occlusionShader->reload();
    normalMapper->reload();
    compositor->reload();
}
