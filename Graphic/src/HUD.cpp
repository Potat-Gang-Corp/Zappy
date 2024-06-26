/*
** EPITECH PROJECT, 2024
** Zappy_Graphic
** File description:
** HUD
*/

#include "HUD.hpp"

HUD::HUD() {}

HUD::~HUD() {}

void HUD::ClearMessages()
{
    messages.clear();
}

void HUD::AddMessage(const std::string& message)
{
    messages.push_back(message);
}

void HUD::Render()
{
    int yOffset = 10;
    int padding = 5;
    int textHeight = 20;
    int boxHeight = (textHeight + 2 * padding + 10) * messages.size();
    int boxWidth = 300;
    int posX = 1910 - boxWidth;
    DrawRectangle(posX, yOffset - padding, boxWidth, boxHeight, Fade(WHITE, 0.8f));
    DrawRectangleLines(posX, yOffset - padding, boxWidth, boxHeight, WHITE);
    
    for (const auto& message : messages) {
        DrawText(message.c_str(), posX + 10, yOffset, 20, BLACK);
        yOffset += textHeight + 2 * padding + 10;
    }
}
