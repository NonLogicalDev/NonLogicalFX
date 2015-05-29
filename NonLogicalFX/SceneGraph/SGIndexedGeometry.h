//
// Created by Oleg Utkin on 5/27/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#pragma once

#include <GLM/glm.h>
#include "SGGeometry.h"

class SGIndexedGeometry : public SGGeometry {
public:
    SGIndexedGeometry();

    // Interface ======================================================
    virtual void constructGeometry();
    virtual void finalizeGeometry();
    virtual void updateUniforms();
    // ================================================================

    void addVertex(float x, float y, float z);
    void addNormal(float nx, float ny, float nz);
    void addTexCoord(float u, float v);

protected:
    GLuint vbo;

    void startDrawMode(GLenum mode);
    void emitTriangle();
    void emitQuad();
    void emitLine();
    void emitStrip();

    void constructVertexAttribute(GLuint loc, void (*lambdaCreate)(GLuint, std::vector<long>), GLuint &buffer, bool purgeBuffer);

private:

    glm::vec3 curNormal;
    glm::vec2 curTexCoord;
    long curVertexCount;

    std::vector<float> verticies;
    std::vector<float> normals;
    std::vector<float> texCords;
    std::vector<float> finalGeometry;
    std::vector<long> indexes;

};


