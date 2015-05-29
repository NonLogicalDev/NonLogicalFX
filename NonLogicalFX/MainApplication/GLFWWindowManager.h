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
#include "SGViewPortHUD.h"

class GLFWWindowManager {
public:
    GLFWWindowManager(char const *string, int i, int i1);
    void runEventLoop();
    SGRoot root;
    SGGroup *skybox;
    SGGroup *scene;
    SGViewPortHUD *fbTarget;
private:
    GLFWwindow *window;
    FileShader *shader;

    void update();
    void draw();

    void makeWindow(char const *title, int width, int height);

    void setUpOpenGLProfile();
    void handleCallbacks();
    void handleShaderUniformUpdate(BaseMaterial* material);

    void setUpOpenGL();

    void buildScene();

    void updateProjectionMatrix();
};
