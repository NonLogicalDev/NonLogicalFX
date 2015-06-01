//
// Created by Oleg Utkin on 5/27/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#pragma once

#include <list>
#include <GLM/glm.h>
#include "SGNode.h"

class SGGroup : public SGNode {
public:
    SGGroup();
    SGGroup(glm::mat4 M);

    virtual void renderWithShader(RawShader* altShader, glm::mat4 M, glm::mat4 V, glm::mat4 P);
    virtual void render(glm::mat4 M, glm::mat4 V, glm::mat4 P);
    virtual void updateGlobalUniformsForMaterial(BaseMaterial *material);
    virtual void update();
    virtual void reload();

    void addChild(SGNode* newChild);

    void deleteTransform();
    void setTransform(glm::mat4 M);
    void applyTransform(glm::mat4 M);


private:
    glm::mat4 M;
    bool appliesTransform;
    std::list<SGNode*> children;
};
