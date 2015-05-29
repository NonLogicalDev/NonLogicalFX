//
// Created by Oleg Utkin on 5/29/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#pragma once


#include "RawShader.h"
#include "FileShader.h"

class FXShader : public FileShader {
public:
    FXShader(std::string fxShaderSource, std::string name, bool isFile = false);
    std::string vertexShader;
    std::string shaderFile;
    virtual void reload();
};


