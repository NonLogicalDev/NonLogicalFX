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
    RawTexture(GLint internalFormat,
               int width, int height,
               GLint border, GLenum format,
               GLenum type, void const* data);
    virtual ~RawTexture();

    void destroy();
    void bind(GLenum texUnit);
    void unbind();

    // Abstract function that reloads an reloads texture in higher classes
    virtual void reload();

    unsigned int id;
    GLenum texUnit;
protected:
    void loadTexture(GLint level, GLint internalFormat,
            int width, int height,
            GLint border, GLenum format,
            GLenum type, void const* data);

private:

    bool destroyed;
    bool bound;
};
