//
// Created by Oleg Utkin on 5/31/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#pragma once


#include "RawFrameBuffer.h"

class TextureFramebuffer : public RawFrameBuffer {
public:
    TextureFramebuffer();
    ~TextureFramebuffer();

    void updateTexture(RawTexture *texture);
    void destroyTexture();
    void attachTo(GLenum attachment);
};


