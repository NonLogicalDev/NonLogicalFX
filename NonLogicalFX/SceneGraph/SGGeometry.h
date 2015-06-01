//
// Created by Oleg Utkin on 5/27/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#pragma once

#include <GLM/glm.h>
#include <functional>
#include "OpenGL_HEADER.h"
#include "SGNode.h"
#include "RawShader.h"

class SGGeometry : public SGNode {

public:
    // Interface ======================================================
    virtual void constructGeometry() = 0;
    virtual void updateUniforms();
    virtual void update();
    virtual void reload();
    // ================================================================

    virtual void renderWithShader(RawShader* altShader, glm::mat4 M, glm::mat4 V, glm::mat4 P);
    virtual void render(glm::mat4 M, glm::mat4 V, glm::mat4 P);
    virtual void updateGlobalUniformsForMaterial(BaseMaterial *material);

    void setUniforms(std::function<void(RawShader *)> callback);
protected:
    std::function<void (RawShader*)> updateUniformsCB;

    SGGeometry();

    std::vector<GLuint> buffers;

    BaseMaterial* material;

    long verticyCount;
    GLuint vertexArrayBuffer;
    GLenum drawMode;

    void generateVertexArray();
    void bindVertexArray();
    void deleteVertexArrayAndBuffers();

    void generateAndBindBuffer(GLuint *buffer, bool record = true);
    void generateAndBindBufferWithData(GLuint *buffer, GLsizeiptr size, void const *data, GLenum usage, bool record = true);
    void bindVertexAttribute(GLuint pLoc, GLenum type, GLint size, GLsizei stride, GLint offset, GLenum normalize);
    void clearBuffers();

    static void bindBufferToData(GLsizeiptr size, void const *data, GLenum usage);
};


