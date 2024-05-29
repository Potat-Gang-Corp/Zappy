/*
** EPITECH PROJECT, 2024
** Zappy_Graphic
** File description:
** Raylib
*/

#pragma once

#ifndef RAYLIB_HPP_
    #define RAYLIB_HPP_

#include <iostream>
#include <raylib.h>
#include <unordered_map>
#include <string>

class Raylib {
    public:
        Raylib(int height, int width, const std::string &WindowName, const std::string &log);
        ~Raylib();
        void setLogInfo(const std::string &log);

    private:
        int _screenH;
        int _screenW;
};

#endif /* !RAYLIB_HPP_ */
