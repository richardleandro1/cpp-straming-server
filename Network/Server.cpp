//
//  Server.cpp
//  Server
//
//  Created by richard on 03/06/24.
//

#include "../include/Server.hpp"

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

#include <string>
#include <locale>

using boost::asio::ip::tcp;

Server::Server(boost::asio::io_context& io_context, short port)
    : io_context_(io_context),
      acceptor_(io_context_, tcp::endpoint(tcp::v4(), port)) {
    start_accept();
}

void Server::start_accept() {
    tcp::socket* new_socket = new tcp::socket(io_context_);
     acceptor_.async_accept(*new_socket,
         boost::bind(&Server::handle_accept, this, new_socket, boost::asio::placeholders::error));
}

void Server::handle_accept(tcp::socket* new_socket, const boost::system::error_code& error) {
    if (!error) {
        std::cout << "Client connected!" << std::endl;
        // Handle received data from the client
    }
    start_accept();
}

std::string Server::get_local_ip() {
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::query query(boost::asio::ip::host_name(), "");
    boost::asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);
    boost::asio::ip::tcp::resolver::iterator end;
    while (iter != end) {
        boost::asio::ip::tcp::endpoint ep = *iter++;
        if (ep.address().is_v4()) {
            return ep.address().to_string();
        }
    }
    return "Unable to determine local IP";
}

std::string get_local_ip_formatted(boost::asio::io_service& io_service) {
    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::query query(boost::asio::ip::host_name(), "");
    boost::asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);
    boost::asio::ip::tcp::resolver::iterator end;

    while (iter != end) {
        boost::asio::ip::tcp::endpoint ep = *iter++;
        if (ep.address().is_v4()) {
            // Format the IPv4 address using std::to_string and std::locale
            std::string ip_address = ep.address().to_string();
            std::stringstream formatted_ip;
            formatted_ip.imbue(std::locale("")); // Set locale to "C" for consistent formatting
            for (size_t i = 0; i < ip_address.size(); ++i) {
                formatted_ip << ip_address[i];
                if (i > 0 && (i % 3) == 2 && i < ip_address.size() - 1) {
                    formatted_ip << '.'; // Insert separators after every 3 digits (except the last)
                }
            }

            // Ensure the formatted IP is UTF-8 encoded
            std::string utf8_ip = formatted_ip.str();
            return utf8_ip;
        }
    }

    return "Unable to determine local IP";
}


//int main() {
//    try {
//        boost::asio::io_context io_context;
//        Server server(io_context, 12345);
//        io_context.run();
//    } catch (std::exception& e) {
//        std::cerr << "Exception: " << e.what() << std::endl;
//    }
//    return 0;
//}

//#include "Server.hpp"
//
//#include <iostream>
//#include <boost/asio.hpp>
//#include <boost/bind/bind.hpp>
//
//using boost::asio::ip::tcp;
//
//class Server {
//public:
//    Server(boost::asio::io_context& io_context, short port)
//        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
//        start_accept();
//    }
//
//private:
//    void start_accept() {
//        tcp::socket* new_socket = new tcp::socket(acceptor_.get_executor().context());
//        acceptor_.async_accept(*new_socket,
//            boost::bind(&Server::handle_accept, this, new_socket, boost::asio::placeholders::error));
//    }
//
//    void handle_accept(tcp::socket* new_socket, const boost::system::error_code& error) {
//        if (!error) {
//            std::cout << "Client connected!" << std::endl;
//            // Handle received data from the client
//        }
//        start_accept();
//    }
//
//    tcp::acceptor acceptor_;
//};
//
//int main() {
//    try {
//        boost::asio::io_context io_context;
//        Server server(io_context, 12345);
//        io_context.run();
//    } catch (std::exception& e) {
//        std::cerr << "Exception: " << e.what() << std::endl;
//    }
//    return 0;
//}
//
