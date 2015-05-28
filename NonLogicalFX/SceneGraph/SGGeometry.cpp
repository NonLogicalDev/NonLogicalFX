//
// Created by Oleg Utkin on 5/27/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#include "SGGeometry.h"
#include "FileTexture.h"
#include <GLM/gtc/type_ptr.h>

SGGeometry::SGGeometry() :
        verticyCount(0),
        vertexArrayBuffer(0),
        drawMode(GL_TRIANGLES),
        material(nullptr)
{
}

void SGGeometry::bindTextures() {
    RawTexture::emptyTexture->bind(GL_TEXTURE0);
}

void SGGeometry::unbindTextures() {
    RawTexture::emptyTexture->unbind();
}

void SGGeometry::render(glm::mat4 M, glm::mat4 V, glm::mat4 P) {
    if (verticyCount > 0 && vertexArrayBuffer != 0 && material != nullptr) {
        material->bind();
        material->setMVPUniform(M, V, P);

        glBindVertexArray(vertexArrayBuffer);
        if(parent) parent->updateGlobalUniformsForMaterial(material);

        glDrawArrays(drawMode, 0, verticyCount);
        material->unbind();
    }
}

void SGGeometry::updateUniforms() { }

void SGGeometry::updateGlobalUniformsForMaterial(BaseMaterial* material) {}

void SGGeometry::reload() {
    material->reload();
}

void SGGeometry::update() {

}
