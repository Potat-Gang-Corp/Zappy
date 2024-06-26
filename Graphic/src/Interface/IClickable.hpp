/*
** EPITECH PROJECT, 2024
** Zappy_Mathis
** File description:
** IClickable
*/

#pragma once

#ifndef ICLICKABLE_HPP
    #define ICLICKABLE_HPP

class IClickable {
    public:
        virtual void OnClick() = 0;
        virtual void setHover(bool status) = 0;
        virtual BoundingBox getBoundingBox() const = 0;
        virtual ~IClickable() = default;
};

#endif // ICLICKABLE_HPP

