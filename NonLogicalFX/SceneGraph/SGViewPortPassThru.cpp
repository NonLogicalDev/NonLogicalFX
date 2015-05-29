//
// Created by Oleg Utkin on 5/29/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#include <OpenGL/OpenGL.h>
#include "SGViewPortPassThru.h"
#include "ShaderLibrary.h"
#include "FileTexture.h"

SGViewPortPassThru::SGViewPortPassThru() {
//    material = new BaseMaterial(
//            ShaderLibrary::get(SL_UV_TEST), {
//            MaterialTextureUnit("uvTexture", 0, new FileTexture("UVTEST.png"))
//    });
    passThroughShader = nullptr;
    material = new BaseMaterial();
    makePassThru();
    constructGeometry();
}

void SGViewPortPassThru::makePassThru() {
    if(passThroughShader == nullptr) {
        FXShader *shader = new FXShader(false, GLSL(
                in vec2 fragCoord;

                uniform sampler2D passThrough;

                void main() {
                    ex_fragColor = texture(passThrough, fragCoord);
                }
        ), "DefaultPicturePass");
        passThroughShader = shader;
    }
    setFXShader(passThroughShader);
    setUpdateUniformCallback([](RawShader *s) {
        glUniform1i(s->uniform("passThrough"), 0);
    });
}

void SGViewPortPassThru::render() {
    glm::mat4 I(1.0);
    SGGeometry::render(I, I, I);
}

void SGViewPortPassThru::constructGeometry() {
    drawMode = GL_TRIANGLES;

    verticies = {
            +1.0, +1.0, 0.0, +1.0, +1.0,
            -1.0, +1.0, 0.0, +0.0, +1.0,
            -1.0, -1.0, 0.0, +0.0, +0.0,

            +1.0, -1.0, 0.0, +1.0, +0.0,
            +1.0, +1.0, 0.0, +1.0, +1.0,
            -1.0, -1.0, 0.0, +0.0, +0.0
    };

    generateVertexArray();
    bindVertexArray();

    GLuint positions, pLoc = 0, pTex = 2;
//    generateAndBindBufferWithData(&positions,
//            verticies.size() * sizeof(float), &verticies[0], GL_STATIC_DRAW
//    );
    generateAndBindBuffer(&positions);
    glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(float), &verticies[0], GL_STATIC_DRAW);

    int stride = 5 * sizeof(float);

    bindVertexAttribute(pLoc, GL_FLOAT, 3, stride, 0, GL_FALSE);
    bindVertexAttribute(pTex, GL_FLOAT, 2, stride, 3 * sizeof(float), GL_FALSE);

    verticyCount = verticies.size() / 5;
}

void SGViewPortPassThru::updateUniforms() {
    SGGeometry::updateUniforms();
}

void SGViewPortPassThru::update() {
    SGGeometry::update();
}

void SGViewPortPassThru::reload() {
    SGGeometry::reload();
}

void SGViewPortPassThru::setFXShader(FXShader *shader) {
    material->setShader(shader);
    updateUniformsCB = nullptr;
}

void SGViewPortPassThru::addTextures(std::list<MaterialTextureUnit> newTextures) {

}

void SGViewPortPassThru::clearTexures() {
    //material->clearTextures();
}

