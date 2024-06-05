//
//  Render.hpp
//  Server
//
//  Created by richard on 03/06/24.
//

#ifndef Render_hpp
#define Render_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <libavcodec/avcodec.h>

sf::Texture frame_to_texture(AVFrame* frame);

#endif /* Render_hpp */
