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

RawTexture::RawTexture(GLenum texType, GLint internalFormat, int width, int height, GLint border, GLenum format, GLenum type, void const *data) {
    destroyed = false;
    id = 0;
    texUnit = GL_TEXTURE0;
    bound = false;
    this->_textureType = texType;
    loadTexture2D(texType, 0, internalFormat, width, height, border, format, type, data);
}

RawTexture::RawTexture(GLint internalFormat, int width, int height, GLint border, GLenum format, GLenum type, void const *data) {
    destroyed = false;
    id = 0;
    texUnit = GL_TEXTURE0;
    bound = false;
    this->_textureType = GL_TEXTURE_2D;
    loadTexture2D(GL_TEXTURE_2D, 0, internalFormat, width, height, border, format, type, data);
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
        glBindTexture(_textureType, id);
        bound = true;
    }

    if (destroyed) {
        fprintf(stderr, "WARNING! Binding destroyed texture.");
    }
}

void RawTexture::unbind() {
    if (!destroyed) {
        glActiveTexture(texUnit);
        glBindTexture(_textureType, 0);
        bound = false;
    }
}

// Protected:
void RawTexture::loadTexture2D(GLenum textureType, GLint level, GLint internalFormat, int width, int height, GLint border, GLenum format, GLenum type, void const *data) {
    if (id != 0) destroy();

    glGenTextures(1, &id);
    glBindTexture(textureType, id);
    glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    if (textureType == GL_TEXTURE_2D) {
        glTexImage2D(GL_TEXTURE_2D, level, internalFormat, width, height, border, format, type, data);
    } else if (GL_TEXTURE_CUBE_MAP) {
        glTexParameteri(textureType, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        for (GLuint i = 0 ; i < 6 ; i++) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, level, internalFormat, width, height, border, format, type, data);
        }
    }
    glBindTexture(textureType, 0);

    destroyed = false;
}

void RawTexture::setWrap(GLint swrap, GLint twrap) {

}

void RawTexture::setInterpolation(GLint type) {

}


// Stubs
void RawTexture::reload() {  }

