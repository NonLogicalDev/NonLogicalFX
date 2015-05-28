//
// Created by Oleg Utkin on 5/26/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#include <fstream>
#include <sstream>
#include "FileShader.h"

#define SHADER_DIR "/Users/olegutkin/Desktop/DeveloperLocal/NonLogicalFX/Resources/Shaders/"

FileShader::FileShader(char const *name) {
    std::stringstream vShader, fShader;
    vShader << SHADER_DIR;
    vShader << name << "V.glsl";
    fShader << SHADER_DIR;
    fShader << name << "F.glsl";
    readFromFiles(vShader.str().c_str(), fShader.str().c_str(), name);
}

FileShader::FileShader(char const *vertexShaderFilename, char const *fragmentShaderFilename, char const *name) {
    readFromFiles(vertexShaderFilename, fragmentShaderFilename, name);
}

void FileShader::readFromFiles(char const *vertexShaderFilename, char const *fragmentShaderFilename, char const *name) {
    this->vertFilename = vertexShaderFilename;
    this->fragFilename = fragmentShaderFilename;

    std::string vertexSource, fragmentSource;
    bool fileReadSuccessful = readFile(vertexShaderFilename, &vertexSource)
                            && readFile(fragmentShaderFilename, &fragmentSource);
    if (fileReadSuccessful) {
        std::string Sname = name;
        initSimpleShader(vertexSource, fragmentSource, Sname);
    }
}

bool FileShader::readFile(char const *filename, std::string *sourceOut) {
    std::ifstream file(filename);
    std::stringstream buffer;
    bool fileOk = (bool)file;

    if (fileOk) {
        buffer << file.rdbuf();
        *sourceOut = buffer.str();
    } else {
        fprintf(stderr, "Error [IO] Can not read file \"%s\"", filename);
    }

    return fileOk;
}

void FileShader::reload() {
    printf(">>>>>>> Reloading [%s]............\n", name.c_str());
    readFromFiles(vertFilename.c_str(), fragFilename.c_str(), name.c_str());
}
