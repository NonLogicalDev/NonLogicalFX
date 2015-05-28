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
        shader(nullptr)
{
}

void SGGeometry::bindTextures() {
    RawTexture::emptyTexture->bind(GL_TEXTURE0);
}

void SGGeometry::unbindTextures() {
    RawTexture::emptyTexture->unbind();
}

void SGGeometry::render(glm::mat4 M, glm::mat4 V, glm::mat4 P) {
    if (verticyCount > 0 && vertexArrayBuffer != 0 && shader != nullptr) {
        glBindVertexArray(vertexArrayBuffer);
        shader->bind(); bindTextures();

        updateUniforms(M, V, P);
        if(parent) parent->updateGlobalUniformsForShader(shader);

        glDrawArrays(drawMode, 0, verticyCount);
        shader->unbind(); unbindTextures();
    }
}

void SGGeometry::updateUniforms(glm::mat4 M, glm::mat4 V, glm::mat4 P) {
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

void SGGeometry::updateGlobalUniformsForShader(RawShader *shader) {}

void SGGeometry::reload() {
    shader->reload();
}
