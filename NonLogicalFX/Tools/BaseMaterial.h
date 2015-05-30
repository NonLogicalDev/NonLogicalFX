//
// Created by Oleg Utkin on 5/27/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#pragma once


#include "RawShader.h"
#include "RawTexture.h"
#include <GLM/glm.h>
#include <GLM/gtc/type_ptr.h>
#include <list>


struct MaterialTextureUnit {
    std::string uniformName;
    int glTextureUnit;
    RawTexture *texture;
    MaterialTextureUnit() {}
    MaterialTextureUnit(std::string name, RawTexture *tex, int unit) {
        uniformName = name; glTextureUnit = unit; texture = tex;
    }
};

class BaseMaterial {
public:
    BaseMaterial();
    BaseMaterial(RawShader* shader);
    BaseMaterial(RawShader* shader, std::list<MaterialTextureUnit> textures);

    virtual void setMVPUniform(glm::mat4 M, glm::mat4 V, glm::mat4 P);

    virtual void setShader(RawShader *newShader);
    virtual void setTextures(std::list<MaterialTextureUnit> newTextures);
    virtual void defaultShaderSetup();

    void bind();
    void unbind();
    void reload();
    RawShader* getShader();

    void clearTextures();
    std::list<MaterialTextureUnit> getTextures();

private:
    RawShader *shader;
    std::list<MaterialTextureUnit> textures;
};
