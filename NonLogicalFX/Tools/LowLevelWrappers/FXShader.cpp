//
// Created by Oleg Utkin on 5/29/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#include "FXShader.h"

FXShader::FXShader(std::string fxShaderSource, std::string name, bool isFile) {
    vertexShader = GLSL(
            out vec2 fragCoord;
            void main() {
                fragCoord = in_TexCoord;
                gl_Position = vec4(in_Position.xy, 0.0, 0.0);
            }
    );

    name += "_FX";

    std::string fragShader;
    if (isFile && readFile(fxShaderSource.c_str(), &fragShader)) {
        this->shaderFile = fxShaderSource;
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
