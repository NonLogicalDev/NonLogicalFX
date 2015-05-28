//
// Created by Oleg Utkin on 5/27/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#include "RawTexture.h"

RawTexture::RawTexture() {
    id = 0;
    texUnit = GL_TEXTURE0;
    bound = false;
}

RawTexture::RawTexture(GLint internalFormat, int width, int height, GLint border, GLenum format, GLenum type, void const *data) {
    loadTexture(0, internalFormat, width, height, border, format, type, data);
}

void RawTexture::loadTexture(GLint level, GLint internalFormat, int width, int height, GLint border, GLenum format, GLenum type, void const *data) {
    GLuint textures[1];     // storage for one texture
    glGenTextures(1, &textures[0]);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, level, internalFormat, width, height, border, format, type, data);
    glBindTexture(GL_TEXTURE_2D, 0);
    id = textures[0];
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
