/*
** EPITECH PROJECT, 2024
** Zappy_Graphic
** File description:
** HUD
*/

#pragma once

#ifndef HUD_HPP
    #define HUD_HPP

    #include "raylib.h"
    #include <string>
    #include <vector>
    #include <memory>

class HUD {
    public:
        static std::shared_ptr<HUD> &getInstance() {
            static std::shared_ptr<HUD> instance = std::make_shared<HUD>();
            return instance;
        }
        HUD();
        ~HUD();

        void AddMessage(const std::string& message);
        void ClearMessages();
        void Render();

    private:
        std::vector<std::string> messages;
        int maxMessages;
};

#endif // HUD_HPP

