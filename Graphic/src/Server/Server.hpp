/*
** EPITECH PROJECT, 2024
** Zappy_Graphic
** File description:
** Server
*/

//doxygen documentation

#pragma once

/**
 * @file Server.hpp
 * @brief Contains the declaration of the Server class
*/

#ifndef SERVER_HPP_
    #define SERVER_HPP_

    #include <iostream>
    #include <string>
    #include <boost/asio.hpp>
    #include <mutex>
    #include <condition_variable>

using boost::asio::ip::tcp;

/**
 * @class Server
 * @brief Class that represents all the server's methods to connect, send and receive data
*/

class Server {
    public:
        static std::shared_ptr<Server> &getInstance() {
            static std::shared_ptr<Server> instance = std::make_shared<Server>();
            return instance;
        }
        /**
         * @brief Construct a new Server object
         * 
         * Initializes the resolver and socket with the io_service.
        */
        Server();
        /**
         * @brief Connect to the server
         * @param port The port to connect to
         * @param host The host to connect to
         * @return int 0 if the connection is successful, 1 otherwise
        */
        int connect_server(const std::string &port, const std::string &host);
        /**
         * @brief Stop the server
        */
        void stop();
        /**
         * @brief Send data to the server
         * @param data The data to send
        */
        void send_data(const std::string &data);
        /**
         * @brief Receives data from the socket until a newline character is found.
         * 
         * This function reads data from the socket using Boost.Asio until a newline ('\n') character is encountered.
         * 
         * @return std::string The received data as a string. Returns an empty string on failure.
        */
        std::string receive_data();
        /**
         * @brief Continuously listens for data from the server.
         * 
         * This function enters an infinite loop, continuously receiving data from the server using the `receive_data` method.
         * It prints the received data to the standard output and, if the data is not one of the predefined control messages
         * ("ko\n", "WELCOME\n", "Connected\n"), it executes a command using the `CommandFactory`.
        */
        void listening();
        /**
         * @brief Callback function to be called when data is received from the server.
         * 
         * This function is a callback function that is called when data is received from the server.
         * It takes a string as an argument, which is the received data.
         * 
         * @param on_receive The function to be called when data is received.
        */
        std::function<void(const std::string&)> on_receive;

    private:
        boost::asio::io_service io_service;
        tcp::resolver resolver;
        tcp::socket socket;
        boost::asio::streambuf buffer;
        bool _connected = false;
        std::mutex socket_mutex;
        int _freq = 10;
        bool send_freq = false;
};

typedef std::shared_ptr<Server> ServerPtr;

#endif // SERVER_HPP