//
// Created by Oleg Utkin on 5/29/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#pragma once

#include <functional>
#include "SGGeometry.h"
#include "FXShader.h"

class SGViewPortPassThru : public SGGeometry {
public:
    SGViewPortPassThru();

    // Interface ======================================================
    virtual void constructGeometry();
    virtual void updateUniforms();
    virtual void update();
    virtual void reload();
    // ================================================================

    void setFXShader(FXShader *shader);
    std::list<MaterialTextureUnit> getTextures();
    void setTextures(std::list<MaterialTextureUnit> newTextures);
    void clearTexures();

    void render();
    std::vector<float> verticies;

    void makePassThru();
    FXShader *passThroughShader;
};


