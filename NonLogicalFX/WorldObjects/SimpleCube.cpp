//
// Created by Oleg Utkin on 5/27/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#include "SimpleCube.h"
#include "ShaderLibrary.h"

SimpleCube::SimpleCube() {
    shader = ShaderLibrary::get(SL_UV_TEST);
    texture = new FileTexture("UVTEST.png");
    constructGeometry();
}

void SimpleCube::updateUniforms(glm::mat4 M, glm::mat4 V, glm::mat4 P) {
    SGIndexedGeometry::updateUniforms(M, V, P);
    glUniform1i(shader->uniform("uvTexture"), 0);
}


void SimpleCube::bindTextures() {
    texture->bind(GL_TEXTURE0);
}

void SimpleCube::unbindTextures() {
    texture->unbind();
}

void SimpleCube::constructGeometry() {
    float s = 10.0;

    float u0 = 0;
    float u1 = 1.0/3.0;
    float u2 = 2.0/3.0;
    float u3 = 1;

    startDrawMode(GL_TRIANGLES);

    // Draw front face:
    addNormal(0.0, 0.0, 1.0);
    addTexCoord(u0, u2);
    addVertex(-s, -s,  s);
    addTexCoord(u1, u2);
    addVertex( s, -s,  s);
    addTexCoord(u1, u3);
    addVertex( s,  s,  s);
    addTexCoord(u0, u3);
    addVertex(-s,  s,  s);
    emitQuad();

    // Draw left side:
    addNormal(-1.0, 0.0, 0.0);
    addTexCoord(u0, u2);
    addVertex(-s,  s,  s);
    addTexCoord(u1, u2);
    addVertex(-s,  s, -s);
    addTexCoord(u1, u1);
    addVertex(-s, -s, -s);
    addTexCoord(u0, u1);
    addVertex(-s, -s,  s);
    emitQuad();


    // Draw right side:
    addNormal(1.0, 0.0, 0.0);
    addTexCoord(u3, u1);
    addVertex( s, -s,  s);
    addTexCoord(u2, u1);
    addVertex( s, -s, -s);
    addTexCoord(u2, u2);
    addVertex( s,  s, -s);
    addTexCoord(u3, u2);
    addVertex( s,  s,  s);
    emitQuad();

    // Draw back face:
    addNormal(0.0, 0.0, -1.0);
    addTexCoord(u1, u2);
    addVertex(-s,  s, -s);
    addTexCoord(u2, u2);
    addVertex( s,  s, -s);
    addTexCoord(u2, u1);
    addVertex( s, -s, -s);
    addTexCoord(u1, u1);
    addVertex(-s, -s, -s);
    emitQuad();

    // Draw top side:
    addNormal(0.0, 1.0, 0.0);
    addTexCoord(u1, u3);
    addVertex(-s,  s,  s);
    addTexCoord(u2, u3);
    addVertex( s,  s,  s);
    addTexCoord(u2, u2);
    addVertex( s,  s, -s);
    addTexCoord(u1, u2);
    addVertex(-s,  s, -s);
    emitQuad();

    // Draw bottom side:
    addNormal(0.0, -1.0, 0.0);
    addTexCoord(u1, u1);
    addVertex(-s, -s, -s);
    addTexCoord(u2, u1);
    addVertex( s, -s, -s);
    addTexCoord(u2, u0);
    addVertex( s, -s,  s);
    addTexCoord(u1, u0);
    addVertex(-s, -s,  s);
    emitQuad();


    SGIndexedGeometry::constructGeometry();
}

void SimpleCube::finalizeGeometry() {

}


void SimpleCube::update() {

}
