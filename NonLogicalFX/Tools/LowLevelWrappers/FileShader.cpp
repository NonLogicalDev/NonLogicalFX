//
// Created by Oleg Utkin on 5/26/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#include <fstream>
#include <sstream>
#include "FileShader.h"

#define SHADER_DIR "/Users/olegutkin/Desktop/DeveloperLocal/NonLogicalFX/Resources/Shaders/"

FileShader::FileShader() {  }

FileShader::FileShader(char const *name) {
    std::stringstream Shader;
    Shader << SHADER_DIR;
    Shader << name << ".glsl";
    this->combFilename = combFilename;

    std::string vertexSource, fragmentSource;
    bool success = readFromCombFile(Shader.str().c_str(), &vertexSource, &fragmentSource, name);
    if (success) {
        std::string Sname = name;
        initSimpleShader(vertexSource, fragmentSource, Sname);
    }
}

FileShader::FileShader(char const *vertexShaderFilename, char const *fragmentShaderFilename, char const *name) {
    std::string vertexSource, fragmentSource;
    this->vertFilename = vertexShaderFilename;
    this->fragFilename = fragmentShaderFilename;

    bool fileReadSuccessful = readFromFiles(
            vertexShaderFilename, &vertexSource,
            fragmentShaderFilename, &fragmentSource,
            name
    );

    if (fileReadSuccessful) {
        std::string Sname = name;
        initSimpleShader(vertexSource, fragmentSource, Sname);
    }
}

bool FileShader::readFromCombFile(
        char const *combFilename,
        std::string *vertexSource,
        std::string *fragmentSource,
        char const *name
) {
    std::string combinedSource;
    bool fileReadSuccessful = readFile(combFilename, &combinedSource);
    if (fileReadSuccessful) {
        bool success = separateSource(combinedSource, vertexSource, fragmentSource);
        return success;
    }
    return false;
}

bool FileShader::readFromFiles(
        char const *vertexShaderFilename,
        std::string *vertexSource,
        char const *fragmentShaderFilename,
        std::string *fragmentSource,
        char const *name
) {
    bool fileReadSuccessful = readFile(vertexShaderFilename, vertexSource)
                           && readFile(fragmentShaderFilename, fragmentSource);

    return fileReadSuccessful;
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
    std::string vertexSource, fragmentSource, Sname = name;
    if (vertFilename.length() != 0) {
        readFromFiles(vertFilename.c_str(), &vertexSource, fragFilename.c_str(), &fragmentSource, name.c_str());
    } else if (combFilename.length() != 0) {
        readFromCombFile(combFilename.c_str(), &vertexSource, &fragmentSource, name.c_str());
    }
    initSimpleShader(vertexSource, fragmentSource, Sname);
}

