//
// Created by Oleg Utkin on 5/26/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#include "FileShader.h"
#include <fstream>
#include <cstdio>
#include <iostream>
#include <sstream>
#include "RawShader.h"

// Public:
RawShader::RawShader() {
    bound = false;
    destroyed = false;
    initiated = false;
    compileSuccessfull = false;
    verbose = true;
    pid = 0;
}

RawShader::RawShader(std::string vertexShader, std::string fragmentShader, std::string name, bool verbose) {
    bound = false;
    destroyed = false;
    initiated = false;
    initSimpleShader(vertexShader, fragmentShader, name);
    this->verbose = verbose;
}

RawShader::~RawShader() {
    destroy();
}

GLint RawShader::uniform(const char * uName) {
    return glGetUniformLocation(pid, uName);
}

void RawShader::destroy() {
    if(bound) unbind();

    if (pid != 0) {
        glDeleteProgram(pid);
        pid = 0;
    }

    destroyed = true;
}

void RawShader::bind() {
    if (compileSuccessfull && !destroyed) {
        glUseProgram(pid);
        bound = true;
    }

    if (destroyed) {
        fprintf(stderr, "WARNING! Binding destroyed shader.\n");
    }
}

void RawShader::unbind() {
    if (!destroyed) {
        glUseProgram(0);
        bound = false;
    }
}

// Protected:
void RawShader::initSimpleShader(std::string &vertexShader, std::string &fragmentShader, std::string &name) {
    if(initiated && compileSuccessfull) {
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


// Private:
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

// Stubs:
void RawShader::reload() { }

bool RawShader::separateSource(std::string source, std::string *vertexSource, std::string *fragSource) {
    std::stringstream vert, frag;
    std::string s = source;
    std::string delimiter = "\n";

    int state = 0; // 1 - Vertex, 2 - Fragment

    size_t pos = 0;
    std::string line;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        line = s.substr(0, pos);
        s.erase(0, pos + delimiter.length());

        if(line.find("//!! vertex:") == 0) {
            state = 1;
            continue;
        } else if(line.find("//!! fragment:") == 0) {
            state = 2;
            continue;
        }

        switch(state) {
            case 1:
                vert << line << std::__1::endl;
                break;
            case 2:
                frag << line << std::__1::endl;
                break;
            default:
                break;
        }
    }

    *vertexSource = vert.str();
    *fragSource = frag.str();

    if(vertexSource->length() != 0 && fragSource->length() != 0) {
        return true;
    } else {
        return false;
    }
}