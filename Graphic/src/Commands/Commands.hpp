/*
** EPITECH PROJECT, 2023
** Zappy_Graphic
** File description:
** Commands.hpp
*/

/*
** EPITECH PROJECT, 2024
** Zappy_Graphic
** File description:
** Commands
*/

#pragma once

#ifndef COMMANDS_HPP_
    #define COMMANDS_HPP_

    #include <iostream>
    #include <map>
    #include <unordered_map>
    #include <sstream>
    #include <memory>
    #include <string>
    #include <vector>

class Commands {
    public:
        static std::shared_ptr<Commands> &getInstance() {
            static std::shared_ptr<Commands> instance = std::make_shared<Commands>();
            return instance;
        }

        Commands(const Commands &cpy) = delete;
        Commands &operator=(const Commands &src) = delete;

        // Commands(const Commands &cpy) = delete;
        // Commands &operator=(const Commands &src) = delete;

        Commands() {}

        /**
         * @brief Handle the msz command (map size)
         * @param data The data to handle
         * @param x The x size of the map
         * @param y The y size of the map
         */
        void msz(const std::string &data);


        /**
         * @brief Handle the bct command (tile content) add the resources to the map
         * @param data The data to handle
         * @param x The x position of the tile
         * @param y The y position of the tile
         * @param food The food quantity on the tile
         * @param linemate The linemate quantity on the tile
         * @param deraumere The deraumere quantity on the tile
         * @param sibur The sibur quantity on the tile
         * @param mendiane The mendiane quantity on the tile
         * @param phiras The phiras quantity on the tile
         * @param thystame The thystame quantity on the tile
         */
        void bct(const std::string &data);

        /**
         * @brief Handle the pbc command (broadcast)
         * @param data The data to handle
         * @param player_id The id of the player who broadcasted
         * @param message The message broadcasted
         */
        void pbc(const std::string &data);


        /**
         * @brief Handle the pdr command (player drop ressource)
         * @param data The data to handle
         * @param player_id The id of the player who dropped
         * @param ressource_number The ressource number dropped
         */
        void pdr(const std::string &data);

        /**
         * @brief Handle the pex command (player expulsion)
         * @param data The data to handle
         * @param player_id The id of the player who got expelled
         */
        void pex(const std::string &data);

        /**
         * @brief Handle the pfk command (egg layed by player)
         * @param data The data to handle
         * @param player_id The id of the player who forked
         */
        void pfk(const std::string &data);

        /**
         * @brief Handle the pgt command (player get ressource)
         * @param data The data to handle
         * @param player_id The id of the player who got the ressource
         * @param ressource_number The ressource number got
         */
        void pgt(const std::string &data);

        /**
         * @brief Handle the pic command (start incantation)
         * @param data The data to handle
         * @param player_id The id of the player who started the incantation
         * @param x The x position of the player
         * @param y The y position of the player
         * @param level The level of the incantation
         */
        void pic(const std::string &data);

        /**
         * @brief Handle the pie command (end incantation)
         * @param data The data to handle
         * @param x The x position of the incantation
         * @param y The y position of the incantation
         * @param result The result of the incantation
         */
        void pie(const std::string &data);

        
        /**
         * @brief Handle the pin command (player inventory)
         * @param data The data to handle
         * @param player_id The id of the player
         * @param x The x position of the player
         * @param y The y position of the player
         * @param food The food quantity of the player
         * @param linemate The linemate quantity of the player
         * @param deraumere The deraumere quantity of the player
         * @param sibur The sibur quantity of the player
         * @param mendiane The mendiane quantity of the player
         * @param phiras The phiras quantity of the player
         * @param thystame The thystame quantity of the player
         */
        void pin(const std::string &data);

        /**
         * @brief Handle the plv command (player level)
         * @param data The data to handle
         * @param player_id The id of the player
         * @param level The level of the player
         */
        void plv(const std::string &data);

        /**
         * @brief Handle the pnw command (new player)
         * @param data The data to handle
         * @param player_id The id of the player
         * @param x The x position of the player
         * @param y The y position of the player
         * @param orientation The orientation of the player
         * @param level The level of the player
         * @param team_name The team name of the player
         */
        void pnw(const std::string &data);

        /**
         * @brief Handle the ppo command (player position)
         * @param data The data to handle
         * @param player_id The id of the player
         * @param x The x position of the player
         * @param y The y position of the player
         * @param orientation The orientation of the player
         */
        void ppo(const std::string &data);

        /**
         * @brief Handle the tna command (name of all teams)
         * @param data The data to handle
         * @param team_name The name of the team
         */
        void tna(const std::string &data);

        /**
         * @brief Handle the pdi command (player died)
         * @param data The data to handle
         * @param player_id The id of the player who died
         */
        void pdi(const std::string &data);

        /**
         * @brief Handle the enw command (egg layed by player)
         * @param data The data to handle
         * @param egg_id The id of the egg
         * @param player_id The id of the player who layed the egg
         * @param x The x position of the egg
         * @param y The y position of the egg
         */
        void enw(const std::string &data);

        /**
         * @brief Handle the ebo command (egg hatched)
         * @param data The data to handle
         * @param egg_id The id of the egg
         */
        void ebo(const std::string &data);

        /**
         * @brief Handle the edi command (egg died)
         * @param data The data to handle
         * @param egg_id The id of the egg
         */
        void edi(const std::string &data);

        /**
         * @brief Handle the sgt command (time unit)
         * @param data The data to handle
         * @param time_unit The time unit
         */
        void sgt(const std::string &data);

        /**
         * @brief Handle the sst command (time unit modification)
         * @param data The data to handle
         * @param time_unit The time unit
         */
        void sst(const std::string &data);

        /**
         * @brief Handle the seg command (end of the game)
         * @param data The data to handle
         * @param team_name The name of the team who won
         */
        void seg(const std::string &data);

        /**
         * @brief Handle the smg command (server message)
         * @param data The data to handle
         * @param message The message
         */
        void smg(const std::string &data);

        /**
         * @brief Handle the suc command (unknown command)
         * @param data The data to handle
         */
        void suc(const std::string &data);

        /**
         * @brief Handle the sbp command (bad parameter)
         * @param data The data to handle
         */
        void sbp(const std::string &data);

    private:
        std::vector<std::string> currentPlayers;
        bool _sleeped = false;
};

#endif /* !COMMANDS_HPP_ */