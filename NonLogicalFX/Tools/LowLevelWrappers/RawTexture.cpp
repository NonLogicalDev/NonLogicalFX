//
// Created by Oleg Utkin on 5/27/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#include "RawTexture.h"

// Public:
RawTexture* RawTexture::emptyTexture = new RawTexture();

RawTexture::RawTexture() {
    destroyed = false;
    id = 0;
    texUnit = GL_TEXTURE0;
    bound = false;
}

RawTexture::RawTexture(GLint internalFormat, int width, int height, GLint border, GLenum format, GLenum type, void const *data) {
    destroyed = false;
    loadTexture(0, internalFormat, width, height, border, format, type, data);
}

RawTexture::~RawTexture() {
    destroy();
}

void RawTexture::destroy() {
    if (bound) unbind();

    if (id != 0) {
        glDeleteTextures(1, &id);
        id = 0;
    }

    destroyed = true;
}

void RawTexture::bind(GLenum texUnit) {
    if (!destroyed) {
        if (bound) unbind();

        this->texUnit = texUnit;
        glActiveTexture(texUnit);
        glBindTexture(GL_TEXTURE_2D, id);
        bound = true;
    }

    if (destroyed) {
        fprintf(stderr, "WARNING! Binding destroyed texture.");
    }
}

void RawTexture::unbind() {
    if (!destroyed) {
        glActiveTexture(texUnit);
        glBindTexture(GL_TEXTURE_2D, 0);
        bound = false;
    }
}

// Protected:
void RawTexture::loadTexture(GLint level, GLint internalFormat, int width, int height, GLint border, GLenum format, GLenum type, void const *data) {
    if (id != 0) destroy();

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, level, internalFormat, width, height, border, format, type, data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

// Stubs
void RawTexture::reload() {  }
