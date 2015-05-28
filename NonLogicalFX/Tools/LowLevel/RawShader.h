//
// Created by Oleg Utkin on 5/26/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <vector>

#define SHADER_VERSION_HEADER "#version 410 core"

class RawShader {
public:
    RawShader();
    RawShader(std::string vertexShader, std::string fragmentShader, std::string name = "Untitled", bool verbose = true);

    void bind();
    void unbind();

    GLint uniform(const char * uName);

    // Abstract function that reloads an recompiles the shader in higher classes
    virtual void reload();

    GLuint pid;

protected:
    bool compileShader(std::string shader, GLenum type, GLuint *compiledShaderOut);
    bool linkShaders(std::vector<GLuint> shaders, GLuint *linkedProgramOut);
    void initSimpleShader(std::string &vertexShader, std::string &fragmentShader, std::string &name);

    std::string name;
private:
    bool compileSuccessfull;
    bool initiated;
    bool verbose;

    std::string preprocessShader(GLenum shaderType, std::string shaderSource);
};

