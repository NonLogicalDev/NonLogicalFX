//
// Created by Oleg Utkin on 5/27/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#pragma once

#include "OpenGL_HEADER.h"
#include <string>

class RawTexture {

public:
    unsigned int id;
    GLenum texUnit;
    static RawTexture * emptyTexture;
    bool bound;

    RawTexture();
    RawTexture(GLint internalFormat,
               int width, int height,
               GLint border, GLenum format,
               GLenum type, void const* data);

    void loadTexture(GLint level, GLint internalFormat,
                     int width, int height,
                     GLint border, GLenum format,
                     GLenum type, void const* data);

    virtual ~RawTexture();

    virtual void reload();

    void bind(GLenum texUnit);
    void unbind();
};


