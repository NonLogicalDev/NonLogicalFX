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

    this->deferredRenderPass1 = new RawFrameBuffer();
    this->deferredRenderPass2 = new RawFrameBuffer();
    this->screenPass = RawFrameBuffer::defaultFramebuffer();

    // Building a scene out of primitives
    buildScene();

    root.setGlobalUniformUpdateCallback([this](BaseMaterial *material){
        this->handleShaderUniformUpdate(material);
    });

    this->uvTexture = new FileTexture("UVTEST.png");
    fbPassThru = new SGViewPortPassThru();
    this->blurShader = new FXShader("PostProcessTest");
    fbPassThru->setFXShader(blurShader);
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
}

void GLFWWindowManager::updateProjectionMatrix() {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    float aspect = (float) width / (float) height;
    root.P = glm::perspective(20.0f, aspect, 1.0f, 1000.0f);

    if (texture1) delete texture1;
    texture1 = new RawTexture(GL_RGB16, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    deferredRenderPass1->attachToTexture2D(GL_COLOR_ATTACHMENT0, texture1);

    if (texture2) delete texture2;
    texture2 = new RawTexture(GL_RGB16, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    deferredRenderPass2->attachToTexture2D(GL_COLOR_ATTACHMENT0, texture2);
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
    float time = glfwGetTime() * 0.5;

    glm::vec3 eye(0.0f, 20*sin(time), 30.0f);
    glm::vec3 up(0.0f, 1.0f, 0.0f);
    glm::vec3 center(0.0f);
    root.V = glm::lookAt(eye, center, up);

    scene->applyTransform(glm::rotate(0.005f, glm::vec3(0.0, 1.0, 0.0)));
}

void GLFWWindowManager::handleShaderUniformUpdate(BaseMaterial *material) {
    GLuint tLoc = material->getShader()->uniform("iGlobalTime");
    float time = glfwGetTime();
    glUniform1f(tLoc, time);
}

void GLFWWindowManager::draw() {
    // ===========================================================================
    /* Make our background black */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Geometry Pass ==============
    deferredRenderPass1->bind(GL_FRAMEBUFFER);

    root.render();

    // Blur H Pass ================
    deferredRenderPass2->bind(GL_FRAMEBUFFER);
    fbPassThru->setFXShader(blurShader);
    fbPassThru->setTextures({
            MaterialTextureUnit("passThrough", 0, deferredRenderPass1->getAttachedTexture())
    });
    fbPassThru->setUniforms([](RawShader *s){
        glUniform1i(s->uniform("iDirection"), 1);
        glUniform1f(s->uniform("iGlobalTime"), glfwGetTime());
    });

    fbPassThru->render();

    // Blur V Pass =================
    deferredRenderPass1->bind(GL_FRAMEBUFFER);
    fbPassThru->setFXShader(blurShader);
    fbPassThru->setTextures({
            MaterialTextureUnit("passThrough", 0, deferredRenderPass2->getAttachedTexture())
    });
    fbPassThru->setUniforms([](RawShader *s){
        glUniform1i(s->uniform("iDirection"), 0);
        glUniform1f(s->uniform("iGlobalTime"), glfwGetTime());
    });

    fbPassThru->render();

    // Image Pass ===================
    screenPass->bind(GL_FRAMEBUFFER);
    fbPassThru->makePassThru();
    fbPassThru->setTextures({
            MaterialTextureUnit("passThrough", 0, deferredRenderPass1->getAttachedTexture())
    });
    fbPassThru->render();

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
}
