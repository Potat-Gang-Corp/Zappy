/*
** EPITECH PROJECT, 2024
** Zappy_Graphic
** File description:
** Raylib
*/

#include "Raylib.hpp"

Raylib::Raylib(int height, int width, const std::string &WindowName, const std::string &log) : _screenH(height), _screenW(width)
{
    this->setLogInfo(log);
    InitWindow(_screenH, _screenW, WindowName.c_str());
    SetTargetFPS(144);
}

Raylib::~Raylib() {}

void Raylib::setLogInfo(const std::string &log)
{
    static const std::unordered_map<std::string, int> logLevels = {
        {"LOG_ALL", LOG_ALL},
        {"LOG_TRACE", LOG_TRACE},
        {"LOG_DEBUG", LOG_DEBUG},
        {"LOG_INFO", LOG_INFO},
        {"LOG_WARNING", LOG_WARNING},
        {"LOG_ERROR", LOG_ERROR},
        {"LOG_FATAL", LOG_FATAL}
    };

    auto it = logLevels.find(log);
    if (it != logLevels.end()) {
        SetTraceLogLevel(it->second);
    } else {
        SetTraceLogLevel(LOG_NONE);
    }
    // LOG_ALL, LOG_TRACE, LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR, LOG_FATAL
}
