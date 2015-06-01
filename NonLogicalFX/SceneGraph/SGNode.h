//
// Created by Oleg Utkin on 5/27/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#pragma once

#include <GLM/matrix.h>
#include "BaseMaterial.h"

class SGNode {
protected:
public:
    SGNode *parent;
    virtual void renderWithShader(RawShader* altShader, glm::mat4 M, glm::mat4 V, glm::mat4 P) = 0;
    virtual void render(glm::mat4 M, glm::mat4 V, glm::mat4 P) = 0;
    virtual void updateGlobalUniformsForMaterial(BaseMaterial *material) = 0;
    virtual void update() = 0;
    virtual void reload() = 0;
};
