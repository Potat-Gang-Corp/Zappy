/*
** EPITECH PROJECT, 2024
** Zappy_Graphic
** File description:
** main
*/

// #include "Raylib.hpp"
#include "Team.hpp"
#include "PlayerData.hpp"
#include "Server.hpp"
#include <raylib.h>

int main(int argc, char **argv) 
{
    // Raylib raylib(800, 800, "Zappy", "LOG_NONE");
    if (argc != 5) {
        std::cerr << "USAGE: " << argv[0] << " -p port -h machine" << std::endl;
        return 1;
    }
    std::string port = argv[2];
    std::string host = argv[4];

    InitWindow(800, 600, "Zappy GUI");
    SetTargetFPS(60);
    
    Server server;
    if (server.connect_server(port, host) != 0) {
        std::cerr << "Failed to connect to server" << std::endl;
        return 1;
    }

    server.on_receive = [](const std::string& data) {
        std::cout << "Data received from server: " << data << std::endl;
    };

    server.send_data("msz\n");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        EndDrawing();
    }

    server.stop();

    CloseWindow();

    return 0;
}
