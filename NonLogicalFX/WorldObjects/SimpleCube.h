//
// Created by Oleg Utkin on 5/27/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#pragma once


#include "SGIndexedGeometry.h"
#include "FileTexture.h"

class SimpleCube : public SGIndexedGeometry {
public:
    SimpleCube();
    // Interface ======================================================
    virtual void constructGeometry();
    virtual void finalizeGeometry();
    virtual void bindTextures();
    virtual void unbindTextures();
    virtual void updateUniforms(glm::mat4 M, glm::mat4 V, glm::mat4 P);
    virtual void update();
    // ================================================================
private:
    FileTexture *texture;
};


