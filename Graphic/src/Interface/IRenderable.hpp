/*
** EPITECH PROJECT, 2024
** Zappy_Mathis
** File description:
** IRenderable
*/

#pragma once

#ifndef IRENDERABLE_HPP
    #define IRENDERABLE_HPP

    #include "raylib.h"

class IRenderable {
    public:
        virtual void Render() = 0;
        virtual Model getModel() = 0;
        virtual ~IRenderable() = default;
};

#endif // IRENDERABLE_HPP

