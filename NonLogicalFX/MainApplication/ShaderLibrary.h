//
// Created by Oleg Utkin on 5/26/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#pragma once

#define SL_BASIC_3D_SHADER "Basic3DShader"
#define SL_DEPTH_SHADER "DepthShader"
#define SL_TEST_SHADER "TestShader"
#define SL_UV_TEST "UVTest"
#define SL_NORMAL_MAPPER "NormalMapper"
#define SL_BLUR "blur"

#include <map>
#include <string>
#include "RawShader.h"
#include "FileShader.h"

class ShaderLibrary {
public:
    static void add(std::string name);
    static void add(std::string name, RawShader *);
    static RawShader *get(std::string name);

    static void initLibrary() {
        i.add(SL_BASIC_3D_SHADER);
        i.add(SL_DEPTH_SHADER);
        i.add(SL_TEST_SHADER);
        i.add(SL_UV_TEST);
        i.add(SL_NORMAL_MAPPER);
        i.add(SL_BLUR);
    }
private:
    std::map<std::string, RawShader*> collection;

    ShaderLibrary();
    static ShaderLibrary * getInstance();
    static ShaderLibrary i;
};
