/*
** EPITECH PROJECT, 2024
** Zappy_Graphic
** File description:
** Factory
*/

#pragma once

/**
 * @file Factory.hpp
 * @brief Contains the declaration of the CommandFactory class
*/

#ifndef FACTORY_HPP_
    #define FACTORY_HPP_

    #include "Commands.hpp"
    #include <unordered_map>
    #include <memory>

/**
 * @class CommandFactory
 * @brief Class that represents the factory's method to execute commands
*/

class CommandFactory {
    public:
        /**
         * @brief Get the instance of the CommandFactory
         * @return CommandFactory* The instance of the CommandFactory
        */
        static std::shared_ptr<CommandFactory> &getInstance() {
            static std::shared_ptr<CommandFactory> instance = std::make_shared<CommandFactory>();
            return instance;
        }

        CommandFactory(const CommandFactory &cpy) = delete;
        CommandFactory &operator=(const CommandFactory &src) = delete;
        
        /**
         * @brief Construct a new CommandFactory object.
         * 
         * Initializes a map that associates command strings with their corresponding command functions.
        */
        CommandFactory()
        {
            std::shared_ptr<Commands> &command = Commands::getInstance();
            // use lambda functions to bind the command functions to the command strings
            commands = {
                {"msz", [&command](const std::string &data) { command->msz(data); }},
                {"bct", [&command](const std::string &data) { command->bct(data); }},
                {"pdr", [&command](const std::string &data) { command->pdr(data); }},
                {"pgt", [&command](const std::string &data) { command->pgt(data); }},
                {"pin", [&command](const std::string &data) { command->pin(data); }},
                {"plv", [&command](const std::string &data) { command->plv(data); }},
                {"ppo", [&command](const std::string &data) { command->ppo(data); }},
                {"tna", [&command](const std::string &data) { command->tna(data); }},
                {"pnw", [&command](const std::string &data) { command->pnw(data); }},
                {"pex", [&command](const std::string &data) { command->pex(data); }},
                {"pbc", [&command](const std::string &data) { command->pbc(data); }},
                {"pic", [&command](const std::string &data) { command->pic(data); }},
                {"pie", [&command](const std::string &data) { command->pie(data); }},
                {"pfk", [&command](const std::string &data) { command->pfk(data); }},
                {"pdi", [&command](const std::string &data) { command->pdi(data); }},
                {"smg", [&command](const std::string &data) { command->smg(data); }},
                {"enw", [&command](const std::string &data) { command->enw(data); }},
                {"ebo", [&command](const std::string &data) { command->ebo(data); }},
                {"edi", [&command](const std::string &data) { command->edi(data); }},
                {"sgt", [&command](const std::string &data) { command->sgt(data); }},
                {"sst", [&command](const std::string &data) { command->sst(data); }},
                {"seg", [&command](const std::string &data) { command->seg(data); }},
                {"suc", [&command](const std::string &data) { command->suc(data); }},
                {"sbp", [&command](const std::string &data) { command->sbp(data); }}
            };
        }

        /**
         * @brief Get the commands map
         * @return std::map<std::string, std::function<void(const std::string&)>> The commands map
        */
        std::map<std::string, std::function<void(const std::string&)>> getCommands()
        {
            return commands;
        }

        /**
         * @brief Executes a command based on the command type.
         * 
         * This function extracts the command prefix from the first three characters of the command type.
         * It then looks up the command in the `commands` map and executes the corresponding function if found.
         * If the command type is empty or the command is not found, an error message is printed.
         * 
         * @param commandType The full command string that includes the command type and its arguments.
        */
        void execCommand(const std::string &commandType)
        {
            std::string prefix = commandType.substr(0, 3);
            if (prefix.empty()) {
                std::cerr << "Error: Command type is empty." << std::endl;
                return;
            }
            auto it = commands.find(prefix);
            if (it != commands.end()) {
                return it->second(commandType);
            } else {
                std::cerr << "Command not found: " << prefix << std::endl;
                return;
            }
        }

    private:
        std::map<std::string, std::function<void(const std::string&)>> commands;
};



#endif /* !FACTORY_HPP_ */