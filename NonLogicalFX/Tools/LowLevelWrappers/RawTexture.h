//
// Created by Oleg Utkin on 5/27/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#pragma once

#include "OpenGL_HEADER.h"
#include <string>

class RawTexture {
public:
    static RawTexture * emptyTexture;

    RawTexture();
    RawTexture(GLenum texType, GLint internalFormat, int width, int height, GLint border, GLenum format, GLenum type, void const *data);
    RawTexture(GLint internalFormat,
               int width, int height,
               GLint border, GLenum format,
               GLenum type, void const* data);
    virtual ~RawTexture();

    void destroy();
    void bind(GLenum texUnit);
    void unbind();

    void setInterpolation(GLint type);
    void setWrap(GLint swrap, GLint twrap);

    // Abstract function that reloads an reloads texture in higher classes
    virtual void reload();

    unsigned int id;
    GLenum texUnit;
    GLenum _textureType;
protected:
    void loadTexture2D(GLenum textureType, GLint level, GLint internalFormat, int width, int height, GLint border, GLenum format, GLenum type, void const *data);

private:

    bool destroyed;
    bool bound;
};
