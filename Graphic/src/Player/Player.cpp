/*
** EPITECH PROJECT, 2024
** Zappy_Graphic
** File description:
** Player
*/

#include "Player.hpp"

Player::Player(int number, int posX, int posY, std::string teamName, Orientation orientation, int lvl)
{
    _playerData._number = number;
    _playerData._posX = posX;
    _playerData._posY = posY;
    _playerData._level = lvl;
    _playerData._teamName = teamName;
    _playerData._orientation = orientation;
}

Player::~Player() {}

int Player::getNumber() const
{
    return _playerData._number;
}

int Player::getPosX() const
{
    return _playerData._posX;
}

int Player::getPosY() const
{
    return _playerData._posY;
}

int Player::getLevel() const
{
    return _playerData._level;
}

std::string Player::getTeamName()
{
    return _playerData._teamName;
}

Orientation Player::getOrientation()
{
    return _playerData._orientation;
}

PlayerData Player::getPlayerData()
{
    return _playerData;
}

