//
// Created by Oleg Utkin on 5/26/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#pragma once

#include <string>
#include "RawShader.h"

class FileShader : public RawShader {
public:
    FileShader(char const *name);
    FileShader(char const *vertexShaderFilename, char const *fragmentShaderFilename, char const *name);
private:

    bool readFile(char const *filename, std::string *sourceOut);

    void readFromFiles(char const *vertexShaderFilename, char const *fragmentShaderFilename, char const *name);

    std::string vertFilename, fragFilename;

    virtual void reload();
};

