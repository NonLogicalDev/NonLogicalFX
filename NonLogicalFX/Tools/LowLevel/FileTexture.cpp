//
// Created by Oleg Utkin on 5/27/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#include <FreeImage/FreeImage.h>
#include <OpenGL/OpenGL.h>
#include "FileTexture.h"

#define TEXTURE_DIR "/Users/olegutkin/Desktop/DeveloperLocal/NonLogicalFX/Resources/Textures/"

FileTexture::FileTexture() : RawTexture() {
    fname = "";
}

FileTexture::FileTexture(std::string fname) {
    std::stringstream name;

    name << TEXTURE_DIR;
    name << fname;

    this->fname = name.str();
    loadFromFile(this->fname.c_str());
}

void FileTexture::loadFromFile(const char * filename) {
    int mlWidth, mlHeight;
    
    FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename);
    FIBITMAP *imagen = FreeImage_Load(format, filename);
    if (!imagen)
    {
        printf( "Texture loading error[%s]\n", fname.c_str());
        return;
    }
    
    mlWidth = FreeImage_GetWidth(imagen);
    mlHeight = FreeImage_GetHeight(imagen);
    FIBITMAP *bitmap = FreeImage_ConvertTo32Bits(imagen);
    FreeImage_Unload(imagen);

    GLuint lid;     // storage for one texture
    glGenTextures(1, &lid);
    loadTexture(lid, 0, GL_RGBA, mlWidth, mlHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, (GLvoid*)FreeImage_GetBits(bitmap));
    id = lid;

    FreeImage_Unload(bitmap);
}

FileTexture::~FileTexture() {  }

void FileTexture::reload() {
    glDeleteTextures(1, &id);
    printf(">>>>>>> Reloading [%s]............\n", fname.c_str());
    loadFromFile(fname.c_str());
}
