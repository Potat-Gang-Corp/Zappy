/*
** EPITECH PROJECT, 2024
** Zappy_Graphic
** File description:
** Server
*/

#ifndef SERVER_HPP_
    #define SERVER_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <atomic>
#include <deque>

using boost::asio::ip::tcp;

class Server {
public:
    Server();
    int connect_server(const std::string& port, const std::string& host);
    void stop();
    void send_data(const std::string& data);
    void start_receive();
    
    std::function<void(const std::string&)> on_receive;  // Callback for received data

private:
    void handle_connect(const boost::system::error_code& error);
    void handle_write(const boost::system::error_code& error, std::size_t bytes_transferred);
    void handle_read(const boost::system::error_code& error, std::size_t bytes_transferred);
    void do_write();

    boost::asio::io_context io_context;
    tcp::resolver resolver;
    tcp::socket socket;
    boost::asio::streambuf buffer;
    std::thread net_thread;
    std::deque<std::string> write_msgs_;
};

#endif // SERVER_HPP