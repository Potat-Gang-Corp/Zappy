/*
** EPITECH PROJECT, 2023
** Zappy_Graphic
** File description:
** Commands.cpp
*/

/**
 * @file Commands.cpp
 * @brief Contains the implementation of the commands functions
 */

#include <iostream>
#include <sstream>
#include <ostream>
#include "Player.hpp"
#include "Commands.hpp"
#include "GameEngine.hpp"
#include <unistd.h>

void Commands::msz(const std::string &data)
{
    std::istringstream iss(data);
    std::string command;
    std::string x;
    std::string y;
    iss >> command >> x >> y;
    GameEngine::getInstance()->setMapSize(std::stof(x), std::stof(y));
}

void Commands::bct(const std::string &data)
{
    std::istringstream iss(data);
    std::string command;
    int x, y;
    int food, linemate, deraumere, sibur, mendiane, phiras, thystame;
    GameEnginePtr &gameMap = GameEngine::getInstance();

    iss >> command >> x >> y >> food >> linemate >> deraumere >> sibur >> mendiane >> phiras >> thystame;

    gameMap->UpdateTileResources(x, y, {food, linemate, deraumere, sibur, mendiane, phiras, thystame, 0});
}

void Commands::pbc(const std::string &data)
{
    std::istringstream iss(data);
    std::string command;
    std::string player_id;
    std::string message;
    iss >> command >> player_id >> message;

    if (broadcastStatus[player_id]) {
        std::cout << "Player " << player_id << " has already broadcasted." << std::endl;
        return;
    }
    broadcastStatus[player_id] = true;
    SoundWrap::getInstance()->playSoundWithVolumeAdjustment(ModelsLoader::getInstance()->getSound("BroadCast"));
}

void Commands::pdr(const std::string &data)
{
    std::istringstream iss(data);
    std::string command;
    std::string player_id;
    std::string ressource_number;
    iss >> command >> player_id >> ressource_number;
    player_id = player_id.substr(1);

    GameEnginePtr PlayerManager = GameEngine::getInstance();
    auto player = PlayerManager->getPlayers();
    for (auto &p : player) {
        if (p->getId() == std::stoi(player_id)) {
            p->removeInventory(std::stoi(ressource_number), 1);
            break;
        }
    }
}

void Commands::pgt(const std::string &data)
{
    std::istringstream iss(data);
    std::string command;
    std::string player_id;
    std::string ressource_number;
    iss >> command >> player_id >> ressource_number;
    player_id = player_id.substr(1);

    GameEnginePtr PlayerManager = GameEngine::getInstance();
    auto player = PlayerManager->getPlayers();
    for (auto &p : player) {
        if (p->getId() == std::stoi(player_id)) {
            p->addInventory(std::stoi(ressource_number), 1);
            break;
        }
    }
}

void Commands::pex(const std::string &data)
{
    std::istringstream iss(data);
    std::string command;
    std::string player_id;
    iss >> command;
    iss >> player_id;

    SoundWrap::getInstance()->playSoundWithVolumeAdjustment(ModelsLoader::getInstance()->getSound("Eject"));
}

void Commands::pfk(const std::string &data)
{
    std::istringstream iss(data);
    std::string command;
    std::string player_id;
    iss >> command;
    iss >> player_id;
    player_id = player_id.substr(1);
}

void Commands::pic(const std::string &data)
{
    std::istringstream iss(data);
    std::string command;
    int x, y;
    std::string level;
    std::string player_id;
    if (!(iss >> command >> x >> y >> level)) {
        std::cerr << "Failed to parse command, x, y, and level\n";
        return;
    }

    auto &playersAtPos = currentPlayers[{x, y}];
    playersAtPos.clear();
    while (iss >> player_id) {
        std::cout << "Player_id = " << player_id << std::endl;
        playersAtPos.push_back(player_id);
    }
}

void Commands::pie(const std::string &data)
{
    std::istringstream iss(data);
    std::string command;
    int x, y;
    std::string result;

    iss >> command >> x >> y >> result;
    if (result == "ok") {
        GameEnginePtr PlayerManager = GameEngine::getInstance();
        auto player = PlayerManager->getPlayers();
        auto &playersAtPos = currentPlayers[{x, y}];
        for (auto &id : playersAtPos) {
            std::cout << "Id = " << id << std::endl;
            id = id.substr(1);
            std::cout << "Id = " << id << std::endl;
            for (auto &p : player) {
                if (p->getId() == std::stoi(id)) {
                    p->setPlayerLevel(p->getLevel() + 1);
                }
            }
            broadcastStatus[id] = false;
        }
        SoundWrap::getInstance()->playSoundWithVolumeAdjustment(ModelsLoader::getInstance()->getSound("Youpi"));
    }
    currentPlayers.erase({x, y});
}

void Commands::pin(const std::string &data)
{
    std::istringstream iss(data);
    std::string command;
    std::string player_id;
    std::string x;
    std::string y;
    std::string linemate;
    std::string deraumere;
    std::string sibur;
    std::string mendiane;
    std::string phiras;
    std::string thystame;
    std::string food;
    iss >> command >> player_id >> x >> y >> food >> linemate >> deraumere >> sibur >> mendiane >> phiras >> thystame;
    player_id = player_id.substr(1);

    GameEnginePtr PlayerManager = GameEngine::getInstance();
    auto player = PlayerManager->getPlayers();
    for (auto &p : player) {
        if (p->getId() == std::stoi(player_id)) {
            p->setInventory({std::stoi(food), std::stoi(linemate), std::stoi(deraumere), std::stoi(sibur), std::stoi(mendiane), std::stoi(phiras), std::stoi(thystame), 0});
            break;
        }
    }
}

void Commands::plv(const std::string &data)
{
    std::istringstream iss(data);
    std::string command;
    std::string player_id;
    std::string level;
    iss >> command >> player_id >> level;
    player_id = player_id.substr(1);
    GameEnginePtr playerManager = GameEngine::getInstance();
    auto &player = playerManager->getPlayers()[std::stoi(player_id)];
    player->setPlayerLevel(std::stoi(level));
}

void Commands::pnw(const std::string &data)
{
    std::istringstream iss(data);
    std::string command;
    std::string player_id;
    std::string x;
    std::string y;
    std::string orientation;
    std::string level;
    std::string team_name;
    iss >> command >> player_id >> x >> y >> orientation >> level >> team_name;

    player_id = player_id.substr(1);
    Player player(std::stoi(player_id), (Vector3){std::stof(x) * 10.0f, 0.0f, std::stof(y) * 10.0f}, std::stoi(orientation), team_name, std::stoi(level));
    GameEngine::getInstance()->addFullPlayer(player);
    SoundWrap::getInstance()->playSoundWithVolumeAdjustment(ModelsLoader::getInstance()->getSound("Connection"));
}

void Commands::ppo(const std::string &data)
{
    std::istringstream iss(data);
    std::string command;
    std::string player_id;
    std::string x;
    std::string y;
    std::string orientation;
    iss >> command >> player_id >> x >> y >> orientation;
    player_id = player_id.substr(1);

    GameEnginePtr PlayerManager = GameEngine::getInstance();
    auto player = PlayerManager->getPlayers();
    for (auto &p : player) {
        if (p->getId() == std::stoi(player_id)) {
            p->setPosition((Vector3){std::stof(x) * 10.0f, 0.0f, std::stof(y) * 10.0f});
            p->setOrientation(std::stoi(orientation));
            break;
        }
    }
}

void Commands::tna(const std::string &data)
{
    std::istringstream iss(data);
    std::string command;
    std::string team_name;
    iss >> command;
    iss >> team_name;
}

void Commands::pdi(const std::string &data)
{
    std::istringstream iss(data);
    std::string command;
    std::string player_id;
    iss >> command;
    iss >> player_id;
    player_id = player_id.substr(1);

    GameEnginePtr PlayerManager = GameEngine::getInstance();
    auto player = PlayerManager->getPlayers();
    for (auto &p : player) {
        std::cout << "Id = " << std::stoi(player_id) << std::endl;
        if (p->getId() == std::stoi(player_id)) {
            PlayerManager->RemovePlayer(std::stoi(player_id));
            SoundWrap::getInstance()->playSoundWithVolumeAdjustment(ModelsLoader::getInstance()->getSound("Death"));
            break;
        }
    }
}

void Commands::enw(const std::string &data)
{
    std::istringstream iss(data);
    std::string command;
    std::string egg_id;
    std::string player_id;
    std::string x;
    std::string y;
    iss >> command >> egg_id >> player_id >> x >> y;
    player_id = player_id.substr(1);
    egg_id = egg_id.substr(1);

    GameEnginePtr PlayerManager = GameEngine::getInstance();
    auto player = PlayerManager->getPlayers();
    PlayerManager->addEgg(std::stoi(egg_id), std::stoi(x), std::stoi(y), 7);
}

void Commands::ebo(const std::string &data)
{
    std::istringstream iss(data);
    std::string command;
    std::string egg_id;
    iss >> command >> egg_id;
    egg_id = egg_id.substr(1);

    GameEnginePtr PlayerManager = GameEngine::getInstance();
    PlayerManager->RemoveEgg(stoi(egg_id));
}

void Commands::edi(const std::string &data)
{
    std::istringstream iss(data);
    std::string command;
    std::string egg_id;
    iss >> command >> egg_id;
    egg_id = egg_id.substr(1);

    GameEnginePtr PlayerManager = GameEngine::getInstance();
    PlayerManager->RemoveEgg(stoi(egg_id));
}

void Commands::sgt(const std::string &data)
{
    std::istringstream iss(data);
    std::string command;
    std::string time_unit;
    iss >> command >> time_unit;
    GameEngine::getInstance()->setFreq(std::stoi(time_unit));
}

void Commands::sst(const std::string &data)
{
    std::istringstream iss(data);
    std::string command;
    std::string time_unit;
    iss >> command;
    iss >> time_unit;
}

void Commands::seg(const std::string &data)
{
    std::istringstream iss(data);
    std::string command;
    std::string team_name;
    iss >> command;
    iss >> team_name;
    SoundWrap::getInstance()->changeMusic(ModelsLoader::getInstance()->getMusic("EndGame"));
}

void Commands::smg(const std::string &data)
{
    std::istringstream iss(data);
    std::string command;
    std::string message;
    iss >> command;
    iss >> message;

    if (message == "egg") {
        if (_sleeped == false) {
            sleep(1);
            _sleeped = true;
        }
        std::string id, x, y;
        iss >> id >> x >> y;
        id = id.substr(1);
        GameEngine::getInstance()->addEgg(std::stoi(id), std::stoi(x), std::stoi(y), 7);
    }
}

void Commands::suc(const std::string &data)
{
    std::cout << "Handling suc: " << data << std::endl;
}

void Commands::sbp(const std::string &data)
{
    std::cout << "Handling sbp: " << data << std::endl;
}