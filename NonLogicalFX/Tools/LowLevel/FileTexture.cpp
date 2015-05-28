//
// Created by Oleg Utkin on 5/27/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#include <FreeImage/FreeImage.h>
#include <OpenGL/OpenGL.h>
#include "FileTexture.h"

#define TEXTURE_DIR "/Users/olegutkin/Desktop/DeveloperLocal/NonLogicalFX/Resources/Textures/"

FileTexture *FileTexture::emptyTexture = new FileTexture();

FileTexture::FileTexture() {
    id = 0;
    texUnit = GL_TEXTURE0;
    bound = false;
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


    GLuint textures[1];     // storage for one texture
    glGenTextures(1, &textures[0]);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mlWidth, mlHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, (GLvoid*)FreeImage_GetBits(bitmap));
    glBindTexture(GL_TEXTURE_2D, 0);

    FreeImage_Unload(bitmap);
    
    id = textures[0];
}

FileTexture::~FileTexture() {

}

void FileTexture::bind(GLenum texUnit) {
    if (bound) unbind();

    this->texUnit = texUnit;
    glActiveTexture(texUnit);
    glBindTexture(GL_TEXTURE_2D, id);
    bound = true;
}

void FileTexture::unbind() {
    glActiveTexture(texUnit);
    glBindTexture(GL_TEXTURE_2D, 0);
    bound = false;
}

void FileTexture::reload() {
    glDeleteTextures(1, &id);
    printf(">>>>>>> Reloading [%s]............\n", fname.c_str());
    loadFromFile(fname.c_str());
}
