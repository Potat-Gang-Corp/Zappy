/*
** EPITECH PROJECT, 2024
** Zappy_Graphic
** File description:
** Server
*/

#include "Server.hpp"
#include "../Factory/Factory.hpp"
#include "GameEngine.hpp"

Server::Server() : resolver(io_service), socket(io_service) {}

int Server::connect_server(const std::string &port, const std::string &host)
{
    try {
        tcp::resolver::query query(host, port);
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        boost::asio::connect(socket, endpoint_iterator);
        std::cout << "Connecté au serveur!" << std::endl;
        send_data("GRAPHIC\n");
        _connected = true;
    } catch (const boost::system::system_error &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

void Server::stop()
{
    io_service.stop();
}

void Server::send_data(const std::string &data)
{
    try {
        boost::asio::write(socket, boost::asio::buffer(data));
    } catch (const boost::system::system_error &e) {
        std::cerr << "Send failed: " << e.what() << std::endl;
    }
}

std::string Server::receive_data()
{
    try {
        size_t bytes_transferred = boost::asio::read_until(socket, buffer, '\n');
        
        std::string response(
            boost::asio::buffers_begin(buffer.data()),
            boost::asio::buffers_begin(buffer.data()) + bytes_transferred
        );
        
        buffer.consume(bytes_transferred);
        
        return response;
    } catch (const boost::system::system_error &e) {
        if (e.code() == boost::asio::error::eof) {
            std::cerr << "Connection closed by peer" << std::endl;
            exit(84);
            return "";
        } else {
            std::cerr << "Receive failed: " << e.what() << std::endl;
            exit(84);
            return "";
        }
    }
}

void Server::listening() 
{
    while (true) {
        std::string response = receive_data();
        if (response != "ko\n" && response != "WELCOME\n" && response != "Connected\n") {
            CommandFactory::getInstance()->execCommand(response);
        }
    }
}
