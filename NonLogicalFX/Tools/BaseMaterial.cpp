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

//void BaseMaterial::defaultShaderSetup() {
//    std::__1::string vertexShader = GLSL(
//            out vec2 ex_TexCoord;
//
//            void main() {
//                gl_Position = _MVP * vec4(in_Position, 1.0);
//                ex_TexCoord = in_TexCoord;
//            }
//    );
//
//    std::__1::string fragmentShader = GLSL(
//            in vec2 ex_TexCoord;
//            uniform sampler2D uvTexture;
//
//            void main() {
//                ex_fragColor = texture(uvTexture, ex_TexCoord);
//            }
//    );
//
//    shader = new RawShader(vertexShader, fragmentShader, "DefaultRawMaterialShader");
//    textures.push_back(
//            MaterialTextureUnit("uvTexture", 0, new FileTexture("UVTEST.png"))
//    );
//}

void BaseMaterial::defaultShaderSetup() {
    std::__1::string vertexShader = GLSL(

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
    GLint   MM = shader->uniform("_Model"),
            VV = shader->uniform("_View"),
            PP = shader->uniform("_Projection"),
            MV = shader->uniform("_MVP");

    glm::mat4 MVP = P * V * M;

    glUniformMatrix4fv(MM, 1, GL_FALSE, glm::value_ptr(M));
    glUniformMatrix4fv(VV, 1, GL_FALSE, glm::value_ptr(V));
    glUniformMatrix4fv(PP, 1, GL_FALSE, glm::value_ptr(P));
    glUniformMatrix4fv(MV, 1, GL_FALSE, glm::value_ptr(MVP));
}

void BaseMaterial::bind() {
    shader->bind();
    for(MaterialTextureUnit texture : textures) {
        texture.texture->bind(GL_TEXTURE0 + texture.glTextureUnit);
        GLuint loc = shader->uniform(texture.uniformName.c_str());
        glUniform1i(loc, texture.glTextureUnit);
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
