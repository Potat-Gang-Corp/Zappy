/*
** EPITECH PROJECT, 2024
** Zappy_Graphic
** File description:
** Player
*/

#include "Team.hpp"
#include <criterion/criterion.h>

Test(TeamTest, ConstructorTest) {
    std::string teamName = "Blue";
    Team team(teamName);

    cr_assert_str_eq(team.getName().c_str(), teamName.c_str(), "Expected teamName: %s, but got: %s", teamName.c_str(), team.getName().c_str());
}

Test(TeamTest, AddPlayerTest) {
    Team team("Blue");
    Player player(1, 0, 0, "Player1", Orientation::NORTH);

    team.addPlayer(player);

    cr_assert_eq(team.getPlayers().size(), 1, "Expected team size: 1, but got: %lu", team.getPlayers().size());
    cr_assert_eq(team.getPlayers()[0].getNumber(), player.getNumber(), "Expected player number: %d, but got: %d", player.getNumber(), team.getPlayers()[0].getNumber());
}

Test(TeamTest, RemovePlayerTest) {
    Team team("Blue");
    Player player1(1, 0, 0, "Player1", Orientation::NORTH);
    Player player2(2, 0, 0, "Player2", Orientation::NORTH);

    team.addPlayer(player1);
    team.addPlayer(player2);

    cr_assert_eq(team.getPlayers().size(), 2, "Expected team size: 2, but got: %lu", team.getPlayers().size());

    team.removePlayer(player1);

    cr_assert_eq(team.getPlayers().size(), 1, "Expected team size: 1, but got: %lu", team.getPlayers().size());
    cr_assert_eq(team.getPlayers()[0].getNumber(), player2.getNumber(), "Expected player number: %d, but got: %d", player2.getNumber(), team.getPlayers()[0].getNumber());
}
