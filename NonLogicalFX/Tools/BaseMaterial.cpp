//
// Created by Oleg Utkin on 5/27/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#include "BaseMaterial.h"

#define GLSL(src) #src

BaseMaterial::BaseMaterial() {
    std::string vertexShader = GLSL(
        out vec2 ex_TexCoord;

        void main() {
            gl_Position = _MVP * vec4(in_Position, 1.0);
            ex_TexCoord = in_TexCoord;
        }
    );

    std::string fragmentShader = GLSL(
        in vec2 ex_TexCoord;
        uniform sampler2D uvTexture;

        void main() {
            ex_fragColor = texture(uvTexture, ex_TexCoord);
        }
    );

    shader = new RawShader(vertexShader, fragmentShader, "DefaultRawMaterialShader");
}

void BaseMaterial::setShader() {

}

void BaseMaterial::setTextures() {

}
