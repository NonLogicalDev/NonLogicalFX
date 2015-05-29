//
// Created by Oleg Utkin on 5/29/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#pragma once

#include <functional>
#include "SGGeometry.h"
#include "FXShader.h"

class SGViewPortHUD : public SGGeometry {
public:
    SGViewPortHUD();

    // Interface ======================================================
    virtual void constructGeometry();
    virtual void updateUniforms();
    virtual void update();
    virtual void reload();
    // ================================================================

    void setFXShader(FXShader *shader);
    void addTextures(std::list<MaterialTextureUnit> newTextures);
    void clearTexures();

    void render();
};


