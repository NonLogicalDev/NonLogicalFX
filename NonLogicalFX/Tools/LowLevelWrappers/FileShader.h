//
// Created by Oleg Utkin on 5/26/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#pragma once

#include <string>
#include "RawShader.h"

class FileShader : public RawShader {
public:
    FileShader();
    FileShader(char const *name);
    FileShader(char const *vertexShaderFilename, char const *fragmentShaderFilename, char const *name);

    virtual void reload();

protected:

    static bool readFile(char const *filename, std::string *sourceOut);
    static bool readFromCombFile(char const *combFilename, std::string *vertexSource, std::string *fragmentSource, char const *name);
    static bool readFromFiles(char const *vertexShaderFilename, std::string *vertexSource, char const *fragmentShaderFilename, std::string *fragmentSource, char const *name);

private:

    std::string vertFilename, fragFilename, combFilename;
};

