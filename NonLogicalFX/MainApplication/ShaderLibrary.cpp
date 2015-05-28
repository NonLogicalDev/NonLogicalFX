//
// Created by Oleg Utkin on 5/26/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#include "ShaderLibrary.h"

ShaderLibrary ShaderLibrary::i;

ShaderLibrary *ShaderLibrary::getInstance() {
    return &i;
}

void ShaderLibrary::add(std::string name) {
    add(name, new FileShader(name.c_str()));
}

void ShaderLibrary::add(std::string name, RawShader *shader) {
    getInstance()->collection[name] = shader;
}

RawShader *ShaderLibrary::get(std::string name) {
    RawShader *s = getInstance()->collection[name];
    return s;
}

ShaderLibrary::ShaderLibrary() {  }

