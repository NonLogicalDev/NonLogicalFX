//
// Created by Oleg Utkin on 5/31/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#include "TextureFramebuffer.h"

TextureFramebuffer::TextureFramebuffer() : RawFrameBuffer() {
    texture = nullptr;
}

TextureFramebuffer::~TextureFramebuffer() {
    destroyTexture();
}

void TextureFramebuffer::updateTexture(RawTexture *texture) {
    destroyTexture();
    this->texture = texture;
}

void TextureFramebuffer::destroyTexture() {
    if(texture != nullptr) {
        delete texture;
        texture = nullptr;
    }
}

void TextureFramebuffer::attachTo(GLenum attachment) {
    attachToTexture2D(attachment, GL_TEXTURE_2D, this->texture);
}
