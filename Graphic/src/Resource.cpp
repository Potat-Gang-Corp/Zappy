/*
** EPITECH PROJECT, 2024
** Zappy_Graphic
** File description:
** Resource
*/

#include "Resource.hpp"
#include <iostream>
#include "Light.hpp"

Resource::Resource(Model model, Vector3 position)
    : model(model), position(position), hover(false), rotationAngle(0.0f) {}

Resource::~Resource() {}

void Resource::Render() {
    if (hover) {
        rotationAngle += 1.0f;
        if (rotationAngle > 360.0f) rotationAngle -= 360.0f;
    }
    
    Color color = WHITE;
    if (hover) {
        color = GREEN;
    }

    for (int i = 0; i < model.materialCount; i++)
        model.materials[i].shader = LightWrapper::getInstance()->getShader();

    DrawModelEx(model, position, (Vector3){0, 1, 0}, rotationAngle, (Vector3){0.09f, 0.09f, 0.09f}, color);
}

Model Resource::getModel() {
    return model;
}

void Resource::setPosition(Vector3 position) {
    this->position = position;
}

Vector3 Resource::getPosition() const {
    return position;
}

void Resource::setHover(bool hover) {
    this->hover = hover;
}

bool Resource::isHovered() const {
    return hover;
}
