//
//  decode.hpp
//  Server
//
//  Created by richard on 02/06/24.
//

#ifndef decode_hpp
#define decode_hpp

#include <stdio.h>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

void init_ffmpeg();

void decode_video(const uint8_t* data, size_t size);

#endif /* decode_hpp */
