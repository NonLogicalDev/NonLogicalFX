//
// Created by Oleg Utkin on 5/27/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#include "SGIndexedGeometry.h"

SGIndexedGeometry::SGIndexedGeometry() {
    curTexCoord = glm::vec2(0.0);
    curNormal = glm::vec3(0.0);
    curVertexCount = 0;
}

void SGIndexedGeometry::updateUniforms(glm::mat4 M, glm::mat4 V, glm::mat4 P) {
    SGGeometry::updateUniforms(M, V, P);
}

void SGIndexedGeometry::constructGeometry() {
    clearBuffers();

    generateVertexArray();
    bindVertexArray();

    int start_line = 0 , end_line = 0, size;
    finalGeometry.clear();
    for(long i : indexes) {
        long vI = i*3, nI = i*3, tI = i*2;
        start_line = __LINE__;
        finalGeometry.push_back(verticies[vI + 0]);
        finalGeometry.push_back(verticies[vI + 1]);
        finalGeometry.push_back(verticies[vI + 2]);
        finalGeometry.push_back(normals[nI + 0]);
        finalGeometry.push_back(normals[nI + 1]);
        finalGeometry.push_back(normals[nI + 2]);
        finalGeometry.push_back(texCords[tI + 0]);
        finalGeometry.push_back(texCords[tI + 1]);
        end_line = __LINE__ - 1;
    }
    size = end_line - start_line;

    GLsizei stride = size * sizeof(float);

    // Recording data into a buffer
    generateAndBindBuffer(vbo);
    glBufferData(GL_ARRAY_BUFFER, finalGeometry.size() * sizeof(float), &finalGeometry[0], GL_STATIC_DRAW);

    // Binding position
    GLuint pLoc = 0;
    glEnableVertexAttribArray(pLoc);
    glVertexAttribPointer(pLoc, 3, GL_FLOAT, GL_FALSE, stride, 0);

    // Binding normals
    GLuint nLoc = 1;
    glEnableVertexAttribArray(nLoc);
    glVertexAttribPointer(nLoc, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(3 * sizeof(float)));

    // Binding texture coordinates
    GLuint tLoc = 2;
    glEnableVertexAttribArray(tLoc);
    glVertexAttribPointer(tLoc, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(6 * sizeof(float)));

    verticyCount = finalGeometry.size() / size;

    verticies.clear();
    normals.clear();
    texCords.clear();

    finalizeGeometry();
}

void SGIndexedGeometry::clearBuffers() {
    glDeleteBuffers((GLsizei)buffers.size(), &buffers[0]);
    buffers.clear();
}

void SGIndexedGeometry::generateAndBindBuffer(GLuint &buffer, bool record) {
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    if(record) buffers.push_back(buffer);
}

void SGIndexedGeometry::bindVertexArray() {
    glBindVertexArray(vertexArrayBuffer);
}

void SGIndexedGeometry::generateVertexArray() {
    deleteVertexArrayAndBuffers();
    glGenVertexArrays(1, &vertexArrayBuffer);
}

void SGIndexedGeometry::deleteVertexArrayAndBuffers() {
    if (vertexArrayBuffer != 0) {
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vertexArrayBuffer);
    }
}

void SGIndexedGeometry::addVertex(float x, float y, float z) {
    verticies.push_back(x);
    verticies.push_back(y);
    verticies.push_back(z);

    normals.push_back(curNormal.x);
    normals.push_back(curNormal.y);
    normals.push_back(curNormal.z);

    texCords.push_back(curTexCoord.x);
    texCords.push_back(curTexCoord.y);
}

void SGIndexedGeometry::addNormal(float nx, float ny, float nz) {
    curNormal = glm::vec3(nx, ny, nz);
}

void SGIndexedGeometry::addTexCoord(float u, float v) {
    curTexCoord = glm::vec2(u, v);
}

void SGIndexedGeometry::emitTriangle() {
    long i = verticies.size()/3 - 3;

    indexes.push_back(i + 0);
    indexes.push_back(i + 1);
    indexes.push_back(i + 2);
}

void SGIndexedGeometry::emitQuad() {
    long i = verticies.size()/3 - 4;

    indexes.push_back(i + 0);
    indexes.push_back(i + 1);
    indexes.push_back(i + 2);

    indexes.push_back(i + 0);
    indexes.push_back(i + 2);
    indexes.push_back(i + 3);
}

void SGIndexedGeometry::emitLine() {
    long i = verticies.size()/3 - 2;

    indexes.push_back(i + 0);
    indexes.push_back(i + 1);
}

void SGIndexedGeometry::emitStrip() {
    indexes.clear();
    for (int i = 0; i < verticies.size() / 3; ++i) {
        indexes.push_back(i);
    }
}

void SGIndexedGeometry::constructVertexAttribute(GLuint loc, void (*lambdaCreate)(GLuint, std::vector<long>), GLuint &buffer, bool purgeBuffer = false) {
    if (purgeBuffer) glDeleteBuffers(1, &buffer);

    bindVertexArray();
    generateAndBindBuffer(buffer, true);

    lambdaCreate(loc, indexes);
}

void SGIndexedGeometry::startDrawMode(GLenum mode) {
    indexes.clear();
    drawMode = mode;

    verticies.clear();
    normals.clear();
    texCords.clear();
}

void SGIndexedGeometry::finalizeGeometry() {  }
void SGIndexedGeometry::bindTextures() { SGGeometry::bindTextures(); }
void SGIndexedGeometry::unbindTextures() { SGGeometry::unbindTextures(); }
