//
// Created by Oleg Utkin on 5/28/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#include <cstdio>
#include "RawFrameBuffer.h"

RawFrameBuffer::RawFrameBuffer() {
    destroyed = false;
    bound = false;
    generateFramebuffer();
}

RawFrameBuffer::~RawFrameBuffer() {
    destroy();
}

void RawFrameBuffer::generateFramebuffer() {
    glGenFramebuffers(1, &fbo);
}

void RawFrameBuffer::destroy() {
    if(bound) unbind();

    if (fbo != 0) {
        glDeleteFramebuffers(1, &fbo);
        fbo = 0;
    }

    destroyed = true;
}

void RawFrameBuffer::bind(GLenum bindPoint) {
    if (fbo != 0) {
        this->bindPoint = bindPoint;
        glBindFramebuffer(bindPoint, fbo);
        bound = true;
    }

    if (destroyed) {
        fprintf(stderr, "WARNING! Binding destroyed shader.");
    }
}

void RawFrameBuffer::unbind() {
    if (bound) {
        glBindFramebuffer(this->bindPoint, 0);
        bound = false;
    }
}

void RawFrameBuffer::attachToTexture2D(GLenum attachmentPoint, RawTexture *texture) {
    glFramebufferTexture2D(bindPoint, attachmentPoint, GL_TEXTURE_2D, texture->id, 0);
}
