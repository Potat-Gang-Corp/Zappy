/*
** EPITECH PROJECT, 2024
** Zappy_Graphic
** File description:
** Resource
*/

#pragma once

#ifndef RESOURCE_HPP
    #define RESOURCE_HPP

    #include "raylib.h"
    #include "../Interface/IRenderable.hpp"
    #include <string>

class Resource : public IRenderable {
    public:
        Resource(Model model, Vector3 position);
        ~Resource();

        void Render() override;
        Model getModel() override;

        void setPosition(Vector3 position);
        Vector3 getPosition() const;

        void setHover(bool hover);
        bool isHovered() const;

    private:
        Model model;
        Vector3 position;
        bool hover;
        float rotationAngle;
};

#endif // RESOURCE_HPP

