//
// Created by Oleg Utkin on 5/27/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#pragma once

#include <GLM/glm.h>
#include <functional>
#include "SGGroup.h"
#include "RawShader.h"

class SGRoot : public SGNode {
public:
    SGRoot();
    SGRoot(glm::mat4 M, glm::mat4 V, glm::mat4 P);

    virtual void render();

    virtual void render(glm::mat4 M, glm::mat4 V, glm::mat4 P);
    virtual void update();
    virtual void reload();

    void setGlobalUniformUpdateCallback(std::function<void (BaseMaterial*)> uniformUpdateCallback);

    void updateGlobalUniformsForMaterial(BaseMaterial *material);

    void addChild(SGNode* newChild);

    glm::mat4 M, V, P;
private:
    SGGroup* rootGroup;
    std::function<void (BaseMaterial*)> uniformUpdateCallback;
};


