

#include "Team.hpp"

Team::Team(const std::string &name)
{
    _name = name;
}

Team::~Team()
{
    _players.clear();
}

void Team::addPlayer(const Player &player)
{
    _players.push_back(player);
}

void Team::removePlayer(const Player &player)
{
    for (int i = 0; i < _players.size(); i++) {
        if (_players[i].getNumber() == player.getNumber()) {
            _players.erase(_players.begin() + i);
            return;
        }
    }
}

std::string Team::getName() const
{
    return _name;
}

std::vector<Player> Team::getPlayers() const
{
    return _players;
}

