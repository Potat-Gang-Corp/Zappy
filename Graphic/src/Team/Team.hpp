/*
** EPITECH PROJECT, 2024
** Zappy_Graphic
** File description:
** Team
*/

#pragma once

#ifndef TEAM_HPP_
    #define TEAM_HPP_

#include "Player.hpp"
#include <iostream>
#include <string>
#include <vector>

class Team {
    public:
        Team(const std::string &name);
        ~Team();
        void addPlayer(const Player &player);
        void removePlayer(const Player &player);
        std::string getName() const;
        std::vector<Player> getPlayers() const;
        
    private:
        std::string _name;
        std::vector<Player> _players;
};

#endif /* !TEAM_HPP_ */
