//
// Created by Oleg Utkin on 5/27/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#pragma once

#include "ShaderLibrary.h"
#include "SGIndexedGeometry.h"
#include "FileTexture.h"

class Skybox : public SGIndexedGeometry {
public:
    Skybox(const char * cubeMapFileName);

    // Interface ======================================================
    virtual void constructGeometry();
    virtual void finalizeGeometry();
    virtual void updateUniforms();
    // ================================================================
};
