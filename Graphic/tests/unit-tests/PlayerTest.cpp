/*
** EPITECH PROJECT, 2024
** Zappy_Graphic
** File description:
** Player
*/

#include "Player.hpp"
#include <criterion/criterion.h>

Test(PlayerTest, ConstructorTest) {
    int number = 10;
    int posX = 5;
    int posY = 15;
    std::string teamName = "Red";
    Orientation orientation = Orientation::NORTH;
    int level = 2;

    Player player(number, posX, posY, teamName, orientation, level);
    PlayerData data = player.getPlayerData();

    cr_assert_eq(data._number, number, "Expected number: %d, but got: %d", number, data._number);
    cr_assert_eq(data._posX, posX, "Expected posX: %d, but got: %d", posX, data._posX);
    cr_assert_eq(data._posY, posY, "Expected posY: %d, but got: %d", posY, data._posY);
    cr_assert_eq(data._level, level, "Expected level: %d, but got: %d", level, data._level);
    cr_assert_str_eq(data._teamName.c_str(), teamName.c_str(), "Expected teamName: %s, but got: %s", teamName.c_str(), data._teamName.c_str());
    cr_assert_eq(data._orientation, orientation, "Expected orientation: %d, but got: %d", static_cast<int>(orientation), static_cast<int>(data._orientation));
}

Test(PlayerTest, GettersTest) {
    int number = 10;
    int posX = 5;
    int posY = 15;
    std::string teamName = "Red";
    Orientation orientation = Orientation::NORTH;
    int level = 2;

    Player player(number, posX, posY, teamName, orientation, level);
    PlayerData data = player.getPlayerData();

    cr_assert_eq(player.getNumber(), number, "Expected number: %d, but got: %d", number, player.getNumber());
    cr_assert_eq(player.getPosX(), posX, "Expected posX: %d, but got: %d", posX, player.getPosX());
    cr_assert_eq(player.getPosY(), posY, "Expected posY: %d, but got: %d", posY, player.getPosY());
    cr_assert_eq(player.getLevel(), level, "Expected level: %d, but got: %d", level, player.getLevel());
    cr_assert_str_eq(player.getTeamName().c_str(), teamName.c_str(), "Expected teamName: %s, but got: %s", teamName.c_str(), player.getTeamName().c_str());
    cr_assert_eq(player.getOrientation(), orientation, "Expected orientation: %d, but got: %d", static_cast<int>(orientation), static_cast<int>(player.getOrientation()));
}
