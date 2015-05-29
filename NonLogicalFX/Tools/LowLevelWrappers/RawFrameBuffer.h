//
// Created by Oleg Utkin on 5/28/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#pragma once

#include "OpenGL_HEADER.h"
#include "RawTexture.h"

class RawFrameBuffer {

    RawFrameBuffer();
    virtual ~RawFrameBuffer();

    void destroy();
    void bind(GLenum bindPoint);
    void unbind();

    void attachToTexture2D(GLenum attachmentPoint, RawTexture* texture);

    GLenum bindPoint;
    GLuint fbo;

private:
    void generateFramebuffer();
    bool destroyed;
    bool bound;
};


