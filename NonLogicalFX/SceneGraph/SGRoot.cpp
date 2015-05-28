//
// Created by Oleg Utkin on 5/27/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#include "SGRoot.h"

SGRoot::SGRoot(glm::mat4 M, glm::mat4 V, glm::mat4 P) :M(M), V(V), P(P)
{
    rootGroup = new SGGroup();
    rootGroup->parent = this;
}

SGRoot::SGRoot() :M(glm::mat4(1.0)), V(glm::mat4(1.0)), P(glm::mat4(1.0))
{
    rootGroup = new SGGroup();
    rootGroup->parent = this;
}

void SGRoot::render(glm::mat4 M, glm::mat4 V, glm::mat4 P) {
    rootGroup->render(M, V, P);
}

void SGRoot::render() {
    rootGroup->render(M, V, P);
}

void SGRoot::update() {
    rootGroup->update();
}

void SGRoot::addChild(SGNode *newChild) {
    rootGroup->addChild(newChild);
}

void SGRoot::updateGlobalUniformsForMaterial(BaseMaterial *material) {
    if (uniformUpdateCallback) uniformUpdateCallback(material);
}

void SGRoot::setGlobalUniformUpdateCallback(std::function<void (BaseMaterial*)> uniformUpdateCallback) {
    this->uniformUpdateCallback = uniformUpdateCallback;
}

void SGRoot::reload() {
    rootGroup->reload();
}
