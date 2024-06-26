/*
** EPITECH PROJECT, 2023
** Zappy_Graphic
** File description:
** ModelsLoader.hpp
*/

#pragma once

#ifndef MODELSLOADER_HPP_
    #define MODELSLOADER_HPP_

    #include <iostream>
    #include <raylib.h>
    #include <vector>
    #include <memory>
    #include <map>

class ModelsLoader {
    public:
        ModelsLoader();
        ~ModelsLoader() = default;
        Model getModel(std::string filename);
        std::shared_ptr<ModelAnimation> getAnim(std::string filename);
        Music getMusic(std::string filename);
        Sound getSound(std::string filename);
        int &getAnimsCount() { return _animsCount; }
        static std::shared_ptr<ModelsLoader> &getInstance() {
            static std::shared_ptr<ModelsLoader> instance = std::make_shared<ModelsLoader>();
            return instance;
        }

        ModelsLoader(const ModelsLoader &cpy) = delete;
        ModelsLoader &operator=(const ModelsLoader &src) = delete;

    private:
        std::map<std::string, Model> _models;
        std::map<std::string, std::shared_ptr<ModelAnimation>> _anims;
        std::map<std::string, Music> _music;
        std::map<std::string, Sound> _sounds;
        int _animsCount = 0;
};

typedef std::shared_ptr<ModelsLoader> ModelsLoaderPtr;

#endif /* !MODELSLOADER_HPP_ */