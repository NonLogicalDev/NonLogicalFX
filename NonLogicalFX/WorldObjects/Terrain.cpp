//
// Created by Oleg Utkin on 5/27/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#include "Terrain.h"

Terrain::Terrain() {
    constructGeometry();
}

void Terrain::constructGeometry() {
    // Preparing the terrain

    startDrawMode(GL_TRIANGLES);

    SGIndexedGeometry::constructGeometry();
}

void Terrain::finalizeGeometry() {

}

void Terrain::bindTextures() {

}

void Terrain::unbindTextures() {

}

void Terrain::updateUniforms(glm::mat4 M, glm::mat4 V, glm::mat4 P) {
    SGIndexedGeometry::updateUniforms(M, V, P);
}

void Terrain::update() {

}

