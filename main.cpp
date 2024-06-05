//
//  main.cpp
//  Server
//
//  Created by richard on 02/06/24.
//
//
#include <iostream>
#include <boost/asio.hpp>
#include <SFML/Graphics.hpp>

#include "include/Server.hpp"
#include <decode.hpp>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

using boost::asio::ip::tcp;


int main() {
    try {
        //sf::String result = Server::get_local_ip();
        // Initialize components
        boost::asio::io_context io_context;
        Server server(io_context, 12345);
        
        boost::asio::io_service io_service;
//        std::string local_ip = server.get_local_ip_formatted(io_service);
//        std::cout << "Local IP: " << local_ip << std::endl;
        
        sf::String result = server.get_local_ip();
        
        sf::RenderWindow window(sf::VideoMode(800, 600), "Video Player");
        init_ffmpeg();
        
        // Main loop
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            
            // Simulate receiving data from socket and decoding it
            // uint8_t* data; size_t size;
            // decode_video(data, size);
            
            // Render frame
            // sf::Texture texture = frame_to_texture(frame);
            
            window.clear();
            // sf::Sprite sprite(texture);
            // window.draw(sprite);
            window.display();
            
            io_context.poll();
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
