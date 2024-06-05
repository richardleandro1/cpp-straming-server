//
//  Server.hpp
//  Server
//
//  Created by richard on 03/06/24.
//

#ifndef Server_hpp
#define Server_hpp

#include <stdio.h>
#include <string>
#include <locale>

#include <boost/asio.hpp>

class Server {
public:
    Server(boost::asio::io_context& io_context, short port);
    
    std::string get_local_ip();
    
    std::string get_local_ip_formatted(boost::asio::io_service& io_service);
private:
    boost::asio::io_context& io_context_; // Declarar antes de acceptor_
    boost::asio::ip::tcp::acceptor acceptor_;
    
    void start_accept();
    void handle_accept(boost::asio::ip::tcp::socket* new_socket, const boost::system::error_code& error);
    
    
};

#endif /* Server_hpp */
