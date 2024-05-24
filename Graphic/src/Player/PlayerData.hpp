/*
** EPITECH PROJECT, 2024
** Zappy_Graphic
** File description:
** PlayerData
*/

#pragma once

#ifndef PLAYERDATA_HPP_
    #define PLAYERDATA_HPP_

#include <string>

enum Orientation {
    NORTH = 1,  
    EAST = 2,
    SOUTH = 3,
    WEST = 4
};

struct PlayerData {
    int _number;
    int _level;
    int _posX, _posY;
    Orientation _orientation;
    std::string _teamName;
};

#endif /* !PLAYERDATA_HPP_ */
