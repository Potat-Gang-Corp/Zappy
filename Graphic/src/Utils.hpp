/*
** EPITECH PROJECT, 2024
** Zappy_Graphic
** File description:
** Utils
*/

#pragma once

#ifndef UTILS_HPP_
    #define UTILS_HPP_

    #include <iostream>
    #include <map>
    #include <string>
    #include <memory>

class Utils {
    public:
        static std::shared_ptr<Utils> &getInstance() {
            static std::shared_ptr<Utils> instance = std::make_shared<Utils>();
            return instance;
        }

        Utils(const Utils &cpy) = delete;
        Utils &operator=(const Utils &src) = delete;
        Utils() {}
        ~Utils() = default;
        std::string orientationToString(int orientation) {
            switch (orientation) {
                case 1:
                    return "North";
                    break;
                case 2:
                    return "East";
                    break;
                case 3:
                    return "South";
                    break;
                case 4:
                    return "West";
                    break;
            }
            return "Unknown";
        }

        std::string indexToString(int index) {
            std::map<int, std::string> indexToString = {
                {0, "food: "},
                {1, "linemate: "},
                {2, "deraumere: "},
                {3, "sibur: "},
                {4, "mendiane: "},
                {5, "phiras: "},
                {6, "thystame: "},
                {7, "egg: "}
            };

            for (const auto& [key, value] : indexToString) {
                if (key == index) {
                    return value;
                }
            }
            return "0";
        }
};

#endif /* !UTILS_HPP_ */
