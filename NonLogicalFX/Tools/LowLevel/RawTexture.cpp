//
// Created by Oleg Utkin on 5/27/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#include "RawTexture.h"

RawTexture* RawTexture::emptyTexture = new RawTexture();

RawTexture::RawTexture() {
    id = 0;
    texUnit = GL_TEXTURE0;
    bound = false;
}

RawTexture::RawTexture(GLint internalFormat, int width, int height, GLint border, GLenum format, GLenum type, void const *data) {
    GLuint lid;     // storage for one texture
    glGenTextures(1, &lid);
    loadTexture(lid, 0, internalFormat, width, height, border, format, type, data);
    id = lid;
}

void RawTexture::loadTexture(GLuint lid, GLint level, GLint internalFormat, int width, int height, GLint border, GLenum format, GLenum type, void const *data) {
    glBindTexture(GL_TEXTURE_2D, lid);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, level, internalFormat, width, height, border, format, type, data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

RawTexture::~RawTexture() {  }

void RawTexture::reload() {  }

void RawTexture::bind(GLenum texUnit) {
    if (bound) unbind();

    this->texUnit = texUnit;
    glActiveTexture(texUnit);
    glBindTexture(GL_TEXTURE_2D, id);
    bound = true;
}

void RawTexture::unbind() {
    glActiveTexture(texUnit);
    glBindTexture(GL_TEXTURE_2D, 0);
    bound = false;
}
