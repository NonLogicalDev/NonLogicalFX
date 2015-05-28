//
// Created by Oleg Utkin on 5/27/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#pragma once

#include "OpenGL_HEADER.h"
#include "RawTexture.h"
#include <string>
#include <vector>
#include <sstream>

class FileTexture : public RawTexture {
public:
    FileTexture();
    FileTexture(std::string fname);
    virtual ~FileTexture();

    void reload();

    void loadFromFile(const char * filename);

    std::string fname;
};


