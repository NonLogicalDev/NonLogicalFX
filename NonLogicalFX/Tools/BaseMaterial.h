//
// Created by Oleg Utkin on 5/27/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#pragma once


#include "RawShader.h"
#include "FileTexture.h"
#include <list>

class BaseMaterial {
public:
    BaseMaterial();

    void setShader();
    void setTextures();
private:
    RawShader *shader;
    std::list<FileTexture *> textures;
};
