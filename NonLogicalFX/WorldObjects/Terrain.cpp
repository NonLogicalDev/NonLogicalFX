//
// Created by Oleg Utkin on 5/27/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#include "Terrain.h"

Terrain::Terrain() {
    constructGeometry();
}

void Terrain::constructGeometry() {
    SGIndexedGeometry::constructGeometry();
}

void Terrain::finalizeGeometry() {
    SGIndexedGeometry::finalizeGeometry();
}

void Terrain::updateUniforms() {
    SGIndexedGeometry::updateUniforms();
}
