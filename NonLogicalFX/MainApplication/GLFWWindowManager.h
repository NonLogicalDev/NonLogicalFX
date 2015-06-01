//
//  GLFWWindowManager.h
//  NonLogicalFX
//
//  Created by Oleg Utkin on 5/26/15.
//  Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#pragma once

#include <stdio.h>
#include "OpenGL_HEADER.h"
#include "FileShader.h"
#include "SGRoot.h"
#include "SGViewPortPassThru.h"
#include "FileTexture.h"
#include "RawFrameBuffer.h"
#include "TextureFramebuffer.h"

class GLFWWindowManager {
public:
    GLFWWindowManager(char const *string, int i, int i1);
    void runEventLoop();
    SGRoot root;
    SGGroup *skybox;
    SGGroup *scene;
    SGViewPortPassThru *screen;
    glm::mat4 projectionMat;
    glm::mat4 inverseProjection;
    void reload();
private:
    GLFWwindow *window;
    FileShader *shader;
    RawShader *normalMapper;
    RawFrameBuffer *screenPass;
    FXShader *blurShader;
    FXShader *occlusionShader;
    TextureFramebuffer *depthPass;
    TextureFramebuffer *diffusePass;
    TextureFramebuffer *normalPass;
    TextureFramebuffer *occlusionPass;

    void update();
    void draw();

    void makeWindow(char const *title, int width, int height);

    void setUpOpenGLProfile();
    void handleCallbacks();
    void handleShaderUniformUpdate(BaseMaterial* material);

    void setUpOpenGL();

    void buildScene();

    void updateProjectionMatrix();

    FileTexture *uvTexture;

    RawTexture *noise;

    void makeSSAOKernel();

    std::vector<float> kernel;
    FXShader *compositor;
    TextureFramebuffer *occlusionPass2;
};
