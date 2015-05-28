//
// Created by Oleg Utkin on 5/26/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#include <cstdio>
#include <iostream>
#include <sstream>
#include "RawShader.h"

RawShader::RawShader() {
    initiated = false;
    compileSuccessfull = false;
}

RawShader::RawShader(std::string vertexShader, std::string fragmentShader, std::string name, bool verbose) {
    initSimpleShader(vertexShader, fragmentShader, name);
    initiated = false;
    this->verbose = verbose;
}

void RawShader::initSimpleShader(std::string &vertexShader, std::string &fragmentShader, std::string &name) {
    if(initiated && compileSuccessfull) {
        glUseProgram(0);
        glDeleteProgram(pid);
    }
    this->name = name;
    std::vector<GLuint> shaders(2);
    compileSuccessfull = compileShader(vertexShader, GL_VERTEX_SHADER, &shaders[0])
                      && compileShader(fragmentShader, GL_FRAGMENT_SHADER, &shaders[1])
                      && linkShaders(shaders, &pid);
    if(compileSuccessfull) {
        if(verbose) printf("Shader[%s] Compiled and Liked Successfully\n", name.c_str());
    } else {
        if(verbose) printf("Error Shader[%s] Snapped...\n", name.c_str());
    }
    initiated = true;
}

std::string RawShader::preprocessShader(GLenum shaderType, std::string shaderSource) {
    std::string result;
    std::stringstream source;

    source << SHADER_VERSION_HEADER << std::endl;
    if (shaderType == GL_VERTEX_SHADER) {
        source << "layout(location=0) in vec3 in_Position;" << std::endl;
        source << "layout(location=1) in vec3 in_Normal;" << std::endl;
        source << "layout(location=2) in vec2 in_TexCoord;" << std::endl;
    } else if (shaderType == GL_FRAGMENT_SHADER) {
        source << " out vec4 ex_fragColor; " << std::endl;
    }

    source << "uniform mat4 _Model;"      << std::endl;
    source << "uniform mat4 _View;"       << std::endl;
    source << "uniform mat4 _Projection;" << std::endl;
    source << "uniform mat4 _MVP;"        << std::endl;

    source << "uniform float iGlobalTime;" << std::endl;
    source << "uniform vec3  iResolution;" << std::endl;
    source << "uniform vec4  iMouse;"      << std::endl;

    source << shaderSource;

    result = source.str();
    return result;
}

bool RawShader::compileShader(std::string shaderSource, GLenum shaderType, GLuint *compiledShaderOut) {
    GLuint shader;
    GLint isCompiled = 0;
    const GLchar *sourceCStr;

    shader = glCreateShader(shaderType);

    std::string source = preprocessShader(shaderType, shaderSource);

    sourceCStr = source.c_str();
    glShaderSource(shader, 1, &sourceCStr, 0);

    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE) {
        char *log;
        GLint logLength = 0;

        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

        log = new char[logLength];
        glGetShaderInfoLog(shader, logLength, &logLength, &log[0]);
        if(verbose) fprintf(stderr, "Shader[%s] Compile Errror: \n %s", name.c_str(), &log[0]);
        delete[] log;

        glDeleteShader(shader);
    }

    *compiledShaderOut = shader;
    return (isCompiled == GL_TRUE);
}


bool RawShader::linkShaders(std::vector<GLuint> shaders, GLuint *linkedProgramOut) {
    GLuint program;
    GLint isLinked = 0;

    program = glCreateProgram();
    for (GLuint shader : shaders) glAttachShader(program, shader);

    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
    if(isLinked == GL_FALSE) {
        char *log;
        GLint logLength = 0;

        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

        log = new char[logLength];
        glGetProgramInfoLog(program, logLength, &logLength, &log[0]);
        if(verbose) fprintf(stderr, "Shader[%s] Linking Errror: \n %s", name.c_str(), &log[0]);
        delete[] log;

        glDeleteProgram(program);
    }

    *linkedProgramOut = program;
    return (isLinked == GL_TRUE);
}

void RawShader::bind() {
    if (compileSuccessfull) {
        glUseProgram(pid);
    }
}

void RawShader::unbind() {
    glUseProgram(0);
}

// Empty fucntion that does not do anything
void RawShader::reload() { }

GLint RawShader::uniform(const char * uName) {
    return glGetUniformLocation(pid, uName);
}
