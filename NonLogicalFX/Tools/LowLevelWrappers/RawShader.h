//
// Created by Oleg Utkin on 5/26/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#pragma once

#include <GLFW/glfw3.h>
#include <GLM/glm.h>
#include <string>
#include <vector>

#define SHADER_VERSION_HEADER "#version 410 core"

// Vertex Shader Inputs:
//
//   layout(location=0) in vec3 in_Position;
//   layout(location=1) in vec3 in_Normal;
//   layout(location=2) in vec2 in_TexCoord;

// Fragment Shader Default outputs:
//
//   out vec4 ex_fragColor; " << std::endl;

// Matrix Block Provided:
//
// uniform mat4 _Model;
// uniform mat4 _View;
// uniform mat4 _Projection;
// uniform mat4 _MVP;

// Uniforms Provided (These must be set through uniform update callback)
//
// uniform float iGlobalTime;
// uniform vec3  iResolution;
// uniform vec4  iMouse;

#define GLSL(src) #src

class RawShader {

public:
    RawShader();
    RawShader(std::string vertexShader, std::string fragmentShader, std::string name = "Untitled", bool verbose = true);
    virtual ~RawShader();

    GLint uniform(const char * uName);
    void destroy();
    void bind();
    void unbind();

    // Abstract function that reloads an recompiles the shader in higher classes
    virtual void reload();

    GLuint pid;

    void setMVPUniform(glm::mat4 M, glm::mat4 V, glm::mat4 P);

protected:
    bool compileShader(std::string shader, GLenum type, GLuint *compiledShaderOut);
    bool linkShaders(std::vector<GLuint> shaders, GLuint *linkedProgramOut);
    void initSimpleShader(std::string &vertexShader, std::string &fragmentShader, std::string &name);

    std::string name;

    static bool separateSource(std::string source, std::string *vertexSource, std::string *fragSource);

private:
    bool compileSuccessfull;
    bool initiated;
    bool destroyed;
    bool bound;
    bool verbose;

    std::string preprocessShader(GLenum shaderType, std::string shaderSource);
};

