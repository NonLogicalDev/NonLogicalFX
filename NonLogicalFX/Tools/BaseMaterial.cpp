//
// Created by Oleg Utkin on 5/27/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#include "BaseMaterial.h"
#include "FileTexture.h"


BaseMaterial::BaseMaterial() {
    defaultShaderSetup();
}

BaseMaterial::BaseMaterial(RawShader *shader) {
    this->shader = shader;
}

BaseMaterial::BaseMaterial(RawShader *shader, std::list<MaterialTextureUnit> textures) {
    this->shader = shader;
    this->textures = textures;
}

void BaseMaterial::defaultShaderSetup() {
    std::string vertexShader = GLSL(

    void main() {
        gl_Position = _MVP * vec4(in_Position, 1.0);
    }

    );

    std::__1::string fragmentShader = GLSL(

    void main() {
        ex_fragColor = vec4(1.0);
    }

    );

    shader = new RawShader(vertexShader, fragmentShader, "DefaultRawMaterialShader");
    textures.clear();
}

void BaseMaterial::setMVPUniform(glm::mat4 M, glm::mat4 V, glm::mat4 P) {
    shader->setMVPUniform(M, V, P);
}

void BaseMaterial::bind() {
    shader->bind();
    int i = 0;
    for(MaterialTextureUnit texture : textures) {
        texture.texture->bind(GL_TEXTURE0 + i);
        GLuint loc = shader->uniform(texture.uniformName.c_str());
        glUniform1i(loc, i);
        i++;
    }
}

void BaseMaterial::unbind() {
    for(MaterialTextureUnit texture : textures) {
        texture.texture->unbind();
    }
    shader->unbind();
}

void BaseMaterial::setShader(RawShader *newShader) {
    shader = newShader;
}

void BaseMaterial::setTextures(std::list<MaterialTextureUnit> newTextures) {
    textures = newTextures;
}

void BaseMaterial::reload() {
    shader->reload();
    for(MaterialTextureUnit texture : textures) {
        texture.texture->reload();
    }
}

RawShader *BaseMaterial::getShader() {
    return shader;
}

void BaseMaterial::clearTextures() {
    textures.clear();
}
