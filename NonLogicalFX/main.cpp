//
//  main.cpp
//  NonLogicalFX
//
//  Created by Oleg Utkin on 5/25/15.
//  Copyright (c) 2015 NonLogicalDev. All rights reserved.
//


#include <cstdlib>
#include <cstdio>
#include "GLFWWindowManager.h"


static void errorCallback(int error, const char * description) {
    fprintf(stderr, "GLFW_ERROR[%i]:%s", error, description);
}

int main(int argc, const char * argv[]) {
    glfwSetErrorCallback(errorCallback);
    if (!glfwInit()) { exit(EXIT_FAILURE); }

    GLFWWindowManager window = GLFWWindowManager("NonlogicalFX", 512, 512);
    window.runEventLoop();

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

