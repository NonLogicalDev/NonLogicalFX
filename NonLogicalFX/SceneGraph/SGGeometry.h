//
// Created by Oleg Utkin on 5/27/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#pragma once

#include "OpenGL_HEADER.h"
#include "SGNode.h"
#include "RawShader.h"

class SGGeometry : public SGNode {
public:
    // Interface ======================================================
    virtual void constructGeometry() = 0;
    virtual void bindTextures();
    virtual void unbindTextures();
    virtual void updateUniforms();
    virtual void update();
    virtual void reload();
    // ================================================================

    virtual void render(glm::mat4 M, glm::mat4 V, glm::mat4 P);
    virtual void updateGlobalUniformsForMaterial(BaseMaterial *material);

protected:
    SGGeometry();

    BaseMaterial* material;

    long verticyCount;
    GLuint vertexArrayBuffer;
    GLenum drawMode;
};


