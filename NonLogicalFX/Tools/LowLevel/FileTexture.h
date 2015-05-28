//
// Created by Oleg Utkin on 5/27/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#pragma once

#include "OpenGL_HEADER.h"
#include <string>
#include <vector>
#include <sstream>

class FileTexture
{
public:
    unsigned int id;
    GLenum texUnit;
    static FileTexture * emptyTexture;
    bool bound;

    FileTexture();
    FileTexture(std::string fname);
    virtual ~FileTexture();

    void reload();
    void bind(GLenum texUnit);
    void unbind();

    void loadFromFile(const char * filename);

    std::string fname;
};


