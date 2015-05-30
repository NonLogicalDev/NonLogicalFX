//
// Created by Oleg Utkin on 5/28/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#pragma once

#include "OpenGL_HEADER.h"
#include "RawTexture.h"

class RawFrameBuffer {
public:
    RawFrameBuffer();
    virtual ~RawFrameBuffer();

    void destroy();
    void bind(GLenum bindPoint);
    void unbind();

    void attachToTexture2D(GLenum attachmentPoint, RawTexture* texture);
    RawTexture *getAttachedTexture();

    void clear(GLbitfield buffers);

    GLenum bindPoint;
    GLuint fbo;

    static RawFrameBuffer *defaultFramebuffer();

private:
    RawFrameBuffer(bool defaultFB);
    void generateFramebuffer();
    bool destroyed;
    bool bound;
    RawTexture *texture;
    static RawFrameBuffer *currentlyBound;
    static RawFrameBuffer *defaultFramebufferVar;
};


