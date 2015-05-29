//
// Created by Oleg Utkin on 5/29/15.
// Copyright (c) 2015 NonLogicalDev. All rights reserved.
//

#include "SGViewPortHUD.h"

SGViewPortHUD::SGViewPortHUD() {
    material = new BaseMaterial();
    FXShader *shader = new FXShader(GLSL(
        in vec2 fragCoord;

        //uniform sampler2D passThrough;

        void main() {
            ex_fragColor = vec4(0.0, 1.0, 0.0, 1.0);
        }
    ), "DefaultPicturePass", false);
    setFXShader(shader);
}

void SGViewPortHUD::render() {
    glm::mat4 I(1.0);
    SGGeometry::render(I, I, I);
}

void SGViewPortHUD::constructGeometry() {
    std::vector<float> verticies = {
            -1.0, -1.0, 0.0, +0.0, +0.0,
            -1.0, +1.0, 0.0, +0.0, +1.0,
            +1.0, +1.0, 0.0, +1.0, +1.0,

            -1.0, -1.0, 0.0, +0.0, +0.0,
            +1.0, +1.0, 0.0, +1.0, +1.0,
            +1.0, -1.0, 0.0, +1.0, +0.0
    };

    generateVertexArray();
    bindVertexArray();

    GLuint positions, pLoc = 0, pTex = 2;
    generateAndBindBufferWithData(&positions,
            verticies.size() * sizeof(float), &verticies[0], GL_DRAW_BUFFER
    );
    bindVertexAttribute(pLoc, GL_FLOAT, 3, 5, 0, GL_FALSE);
    bindVertexAttribute(pTex, GL_FLOAT, 2, 5, 3, GL_FALSE);
}

void SGViewPortHUD::updateUniforms() {
    SGGeometry::updateUniforms();
}

void SGViewPortHUD::update() {
    SGGeometry::update();
}

void SGViewPortHUD::reload() {
    SGGeometry::reload();
}

void SGViewPortHUD::setFXShader(FXShader *shader) {
    material->setShader(shader);
    updateUniformsCB = nullptr;
}

void SGViewPortHUD::addTextures(std::list<MaterialTextureUnit> newTextures) {

}

void SGViewPortHUD::clearTexures() {
    //material->clearTextures();
}

