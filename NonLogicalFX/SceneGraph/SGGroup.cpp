//
// Created by Oleg Utkin on 5/27/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#include "SGGroup.h"

SGGroup::SGGroup(): M(glm::mat4(1.0)) {
    appliesTransform = false;
}

SGGroup::SGGroup(glm::mat4 M): M(M) {
    appliesTransform = true;
}

void SGGroup::renderWithShader(RawShader *altShader, glm::mat4 M, glm::mat4 V, glm::mat4 P) {
    if (appliesTransform) M = this->M * M;
    for(SGNode* node : children) {
        node->renderWithShader(altShader, M, V, P);
    }
}

void SGGroup::render(glm::mat4 M, glm::mat4 V, glm::mat4 P) {
    if (appliesTransform) M = this->M * M;
    for(SGNode* node : children) {
        node->render(M, V, P);
    }
}

void SGGroup::update() {
    for(SGNode* node : children) {
        node->update();
    }
}

void SGGroup::addChild(SGNode *newChild) {
    children.push_back(newChild);
    newChild->parent = this;
}

void SGGroup::deleteTransform() {
    appliesTransform = false;
    M = glm::mat4(1.0);
}

void SGGroup::setTransform(glm::mat4 M) {
    appliesTransform = true;
    this->M = M;
}

void SGGroup::applyTransform(glm::mat4 M) {
    appliesTransform = true;
    this->M = M * this->M;
}

void SGGroup::updateGlobalUniformsForMaterial(BaseMaterial *material) {
    if(parent) parent->updateGlobalUniformsForMaterial(material);
}

void SGGroup::reload() {
    for(SGNode* node : children) {
        node->reload();
    }
}

