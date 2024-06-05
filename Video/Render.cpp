//
//  Render.cpp
//  Server
//
//  Created by richard on 03/06/24.
//

#include "Render.hpp"
#include <SFML/Graphics.hpp>
#include <libavcodec/avcodec.h>

/**-----------------------------------------------------------------------------------------------------------------------
 **                                Renderização de Vídeo com SFML
 *-----------------------------------------------------------------------------------------------------------------------**/

// Function to convert AVFrame to sf::Texture
sf::Texture frame_to_texture(AVFrame* frame) {
    sf::Texture texture;
    texture.create(frame->width, frame->height);
    sf::Uint8* pixels = new sf::Uint8[frame->width * frame->height * 4]; // RGBA

    for (int y = 0; y < frame->height; y++) {
        for (int x = 0; x < frame->width; x++) {
            int i = y * frame->linesize[0] + x * 3;
            pixels[(y * frame->width + x) * 4 + 0] = frame->data[0][i + 0]; // R
            pixels[(y * frame->width + x) * 4 + 1] = frame->data[0][i + 1]; // G
            pixels[(y * frame->width + x) * 4 + 2] = frame->data[0][i + 2]; // B
            pixels[(y * frame->width + x) * 4 + 3] = 255;                   // A
        }
    }
    texture.update(pixels);
    delete[] pixels;
    return texture;
}


//int main() {
//    sf::RenderWindow window(sf::VideoMode(800, 600), "Video Player");
//
//    // Initialize FFmpeg
//    init_ffmpeg();
//
//    // Main loop
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        // Simulate receiving data from socket and decoding it
//        // uint8_t* data; size_t size;
//        // decode_video(data, size);
//
//        // Render frame
//        // sf::Texture texture = frame_to_texture(frame);
//
//        window.clear();
//        // sf::Sprite sprite(texture);
//        // window.draw(sprite);
//        window.display();
//    }
//
//    return 0;
//}
