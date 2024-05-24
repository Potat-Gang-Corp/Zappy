/*
** EPITECH PROJECT, 2024
** Zappy_Graphic
** File description:
** main
*/

#include "Team.hpp"
#include "PlayerData.hpp"

int main(void)
{
    Team team("Dragon Sword");
    Player player(1, 0, 0, "Dragon Sword", Orientation::NORTH);

    std::cout << "The player is number #" << player.getNumber() << std::endl;
    std::cout << "The player is at position " << player.getPosX() << "," << player.getPosY() << std::endl;
    std::cout << "The player is at level " << player.getLevel() << std::endl;
    std::cout << "The player is in team " << player.getTeamName() << std::endl;
    std::cout << "The player is facing " << player.getOrientation() << std::endl;
    // std::cout << "The team is " << team.getName() << std::endl;
    return 0;
}