/*
** EPITECH PROJECT, 2023
** Zappy_Graphic
** File description:
** ModelsLoader.cpp
*/

#include "ModelsLoader.hpp"

Model LoadModelSafely(const char* fileName)
{
    Model model = LoadModel(fileName);
    if (model.meshCount == 0) {
        std::cerr << "Failed to load model: " << fileName << "\n";
        throw std::runtime_error("Failed to load model: " + std::string(fileName));
    }
    return model;
}

std::shared_ptr<ModelAnimation> LoadModelAnimationsSafely(const char* fileName)
{
    int animsCount = 0;
    ModelAnimation* anims = LoadModelAnimations(fileName, &animsCount);
    if (animsCount == 0) {
        std::cerr << "Failed to load animations: " << fileName << "\n";
        throw std::runtime_error("Failed to load animations: " + std::string(fileName));
    }
    return std::shared_ptr<ModelAnimation>(anims);
}

ModelsLoader::ModelsLoader()
{
    try {
        _models = {
            {"Island_farm", LoadModelSafely("assets/island_farm.glb")},
            {"Island_tree", LoadModelSafely("assets/island_tree.glb")},
            {"Island", LoadModelSafely("assets/island.glb")},
            {"FOOD", LoadModelSafely("assets/potato.glb")},
            {"LINEMATE", LoadModelSafely("assets/mine1.glb")},
            {"DERAUMERE", LoadModelSafely("assets/mine2.glb")},
            {"SIBUR", LoadModelSafely("assets/mine3.glb")},
            {"MENDIANE", LoadModelSafely("assets/mine4.glb")},
            {"PHIRAS", LoadModelSafely("assets/mine5.glb")},
            {"THYSTAME", LoadModelSafely("assets/mine6.glb")},
            {"EGG", LoadModelSafely("assets/Egg.glb")},
            {"PlayerModel", LoadModelSafely("assets/player.glb")}
        };

        _anims = {
            {"Player", LoadModelAnimationsSafely("assets/player.glb")},
            {"Dying", LoadModelAnimationsSafely("assets/animation/dying.glb")},
            {"Dropping", LoadModelAnimationsSafely("assets/animation/dropping.glb")},
            {"LevelUp", LoadModelAnimationsSafely("assets/animation/level_up.glb")},
            {"Hands", LoadModelAnimationsSafely("assets/animation/hands.glb")}
        };

        _music = {
            {"Ambient", LoadMusicStream("assets/sounds/ambient_music.mp3")},
            {"EndGame", LoadMusicStream("assets/sounds/endgame.mp3")},
        };

        _sounds = {
            {"BroadCast", LoadSound("assets/sounds/broadcast.mp3")},
            {"Youpi", LoadSound("assets/sounds/youpi.mp3")},
            {"Connection", LoadSound("assets/sounds/connection.mp3")},
            {"Death", LoadSound("assets/sounds/death.mp3")},
        };
    } catch (const std::exception &e) {
        std::cerr << "Error in ModelsLoader: " << e.what() << std::endl;
        throw;
    }
}

Model ModelsLoader::getModel(std::string filename)
{
    for (auto it: _models) {
        if (it.first == filename)
            return it.second;
    }
    std::cout << "Model not found" << std::endl;
    return _models["Island"];
}

std::shared_ptr<ModelAnimation> ModelsLoader::getAnim(std::string filename)
{
    for (auto it: _anims) {
        if (it.first == filename)
            return it.second;
    }
    std::cout << "Animation not found" << std::endl;
    return _anims["Player"];
}

Music ModelsLoader::getMusic(std::string filename)
{
    for (auto it: _music) {
        if (it.first == filename)
            return it.second;
    }
    std::cout << "Music not found" << std::endl;
    return _music["Ambient"];
}

Sound ModelsLoader::getSound(std::string filename)
{
    for (auto it: _sounds) {
        if (it.first == filename)
            return it.second;
    }
    std::cout << "Sound not found" << std::endl;
    return _sounds["BroadCast"];
}
