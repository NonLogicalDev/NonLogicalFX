//
// Created by Oleg Utkin on 5/29/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#include <sstream>
#include "FXShader.h"

#define SHADER_DIR "/Users/olegutkin/Desktop/DeveloperLocal/NonLogicalFX/Resources/Shaders/"

FXShader::FXShader(std::string fxShaderSource) {
    std::stringstream Shader;
    Shader << SHADER_DIR;
    Shader << fxShaderSource << ".glsl";

    initialize(true, Shader.str(), fxShaderSource);
}

FXShader::FXShader(std::string name, std::string fxShaderSource) {
    initialize(false, fxShaderSource, name);
}

FXShader::FXShader(bool isFile, std::string fxShaderSource, std::string name) {
    initialize(isFile, fxShaderSource, name);
}

void FXShader::initialize(bool isFile, std::string fxShaderSource, std::string name) {
    vertexShader = GLSL(
            out vec2 fragCoord;
            void main() {
                fragCoord = in_TexCoord;
                gl_Position = vec4(in_Position.xy, 0.5, 1.0);
            }
    );

    name += "_FX";


    std::string fragShader;
    if (isFile && readFile(fxShaderSource.c_str(), &fragShader)) {

        shaderFile = fxShaderSource;
        initSimpleShader(vertexShader, fragShader, name);
    } else {
        initSimpleShader(vertexShader, fxShaderSource, name);
    }
}

void FXShader::reload() {
    printf(">>>>>>> Reloading [%s]............\n", name.c_str());
    if(this->shaderFile.length() != 0) {
        std::string fragShader;
        readFile(shaderFile.c_str(), &fragShader);
        initSimpleShader(vertexShader, fragShader, name);
    }
}

