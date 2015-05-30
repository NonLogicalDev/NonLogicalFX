//
// Created by Oleg Utkin on 5/28/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#include <cstdio>
#include "RawFrameBuffer.h"

RawFrameBuffer *RawFrameBuffer::currentlyBound = nullptr;
RawFrameBuffer *RawFrameBuffer::defaultFramebufferVar = nullptr;


RawFrameBuffer::RawFrameBuffer(bool defaultFB) {
    fbo = 0;
    destroyed = false;
    bound = false;
    bindPoint = GL_FRAMEBUFFER;
    texture = nullptr;
}

RawFrameBuffer::RawFrameBuffer() {
    destroyed = false;
    bound = false;
    bindPoint = GL_FRAMEBUFFER;
    texture = nullptr;
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
    if(currentlyBound && currentlyBound->bindPoint == bindPoint && currentlyBound != this) {
      currentlyBound->bound = false;
    }

    if (!bound) {
        glBindFramebuffer(bindPoint, fbo);
        this->bindPoint = bindPoint;
        currentlyBound = this;
        bound = true;
    }

    if (destroyed) {
        fprintf(stderr, "WARNING! Binding destroyed shader.\n");
    }
}

void RawFrameBuffer::unbind() {
    if (bound) {
        glBindFramebuffer(this->bindPoint, 0);
        bound = false;
    }
}



void RawFrameBuffer::attachToTexture2D(GLenum attachmentPoint, RawTexture *texture) {
    bind(bindPoint);
    this->texture = texture;
    glFramebufferTexture2D(bindPoint, attachmentPoint, GL_TEXTURE_2D, texture->id, 0);
}

void RawFrameBuffer::clear(GLbitfield buffers) {
    bind(bindPoint);
    glClear(buffers);
}

RawFrameBuffer *RawFrameBuffer::defaultFramebuffer() {
    if (!defaultFramebufferVar) {
        defaultFramebufferVar = new RawFrameBuffer(true);
    }
    return defaultFramebufferVar;
}

RawTexture *RawFrameBuffer::getAttachedTexture() {
    if(texture == nullptr) {
        fprintf(stderr, "WARNING Accessing buffer's texture that has no texture. Returning empy texture\n");
        return RawTexture::emptyTexture;
    } else {
        return texture;
    }
}
