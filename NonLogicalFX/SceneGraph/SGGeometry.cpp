//
// Created by Oleg Utkin on 5/27/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#include "SGIndexedGeometry.h"
#include "SGGeometry.h"
#include "FileTexture.h"
#include <GLM/gtc/type_ptr.h>
#include <OpenGL/OpenGL.h>

SGGeometry::SGGeometry() :
        verticyCount(0),
        vertexArrayBuffer(0),
        drawMode(GL_TRIANGLES),
        material(nullptr)
{
    parent = nullptr;
}


void SGGeometry::render(glm::mat4 M, glm::mat4 V, glm::mat4 P) {
    if (verticyCount > 0 && vertexArrayBuffer != 0 && material != nullptr) {
        material->bind();
        material->setMVPUniform(M, V, P);
        updateUniforms();

        glBindVertexArray(vertexArrayBuffer);
        if(parent) parent->updateGlobalUniformsForMaterial(material);

        glDrawArrays(drawMode, 0, verticyCount);
        material->unbind();
    }
}

void SGGeometry::updateUniforms() {
    if(updateUniformsCB) {
        updateUniformsCB(material->getShader());
    }
}

void SGGeometry::updateGlobalUniformsForMaterial(BaseMaterial* material) {}

void SGGeometry::reload() {
    material->reload();
}

void SGGeometry::update() {

}

void SGGeometry::clearBuffers() {
    glDeleteBuffers((GLsizei)buffers.size(), &buffers[0]);
    buffers.clear();
}

void SGGeometry::generateAndBindBuffer(GLuint *buffer, bool record) {
    glGenBuffers(1, buffer);
    glBindBuffer(GL_ARRAY_BUFFER, *buffer);
    if(record) buffers.push_back(*buffer);
}

void SGGeometry::generateAndBindBufferWithData(GLuint *buffer, GLsizeiptr size, void const *data, GLenum usage, bool record) {
    generateAndBindBuffer(buffer, record);
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void SGGeometry::bindBufferToData(GLsizeiptr size, void const *data, GLenum usage) {
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void SGGeometry::bindVertexArray() {
    glBindVertexArray(vertexArrayBuffer);
}

void SGGeometry::generateVertexArray() {
    deleteVertexArrayAndBuffers();
    glGenVertexArrays(1, &vertexArrayBuffer);
}

void SGGeometry::deleteVertexArrayAndBuffers() {
    if (vertexArrayBuffer != 0) {
        clearBuffers();
        glDeleteVertexArrays(1, &vertexArrayBuffer);
    }
}

void SGGeometry::bindVertexAttribute(GLuint pLoc, GLenum type, GLint size, GLsizei stride, GLint offset, GLenum normalize) {
    glEnableVertexAttribArray(pLoc);
    glVertexAttribPointer(pLoc, size, type, normalize, stride, (void*)offset);
}

void SGGeometry::setUniforms(std::function<void(RawShader *)> callback) {
    updateUniformsCB = callback;
}

