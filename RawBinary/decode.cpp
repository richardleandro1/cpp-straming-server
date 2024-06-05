//
//  decode.cpp
//  Server
//
//  Created by richard on 02/06/24.
//

#include "decode.hpp"

extern "C" {
#include <libavcodec/codec.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}


// FFmpeg initialization
void init_ffmpeg() {
    //av_register_all();
    //avcodec_register_all();
}

/**-----------------------------------------------------------------------------------------------------------------------
 **                               Decodificação de Vídeo com FFmpeg
 *-----------------------------------------------------------------------------------------------------------------------**/

void decode_video(const uint8_t* data, size_t size) {
    
    AVCodecContext *codecContext; // inicialize seu codec context
    AVSubtitle subtitle;
    int gotSubtitle;
    AVPacket packet; // inicialize seu pacote
    
    const AVCodec* codec = avcodec_find_decoder(AV_CODEC_ID_H264);
    
    // Initialize FFmpeg components
    //AVCodec* codec = avcodec_find_decoder(AV_CODEC_ID_H264);
    AVCodecContext* codec_ctx = avcodec_alloc_context3(codec);
    avcodec_open2(codec_ctx, codec, NULL);
    
    //AVPacket packet;
    av_init_packet(&packet);
    packet.data = const_cast<uint8_t*>(data);
    packet.size = size;
    
    AVFrame* frame = av_frame_alloc();
    int got_frame = 0;
    //avcodec_decode_subtitle2(codec_ctx, frame, &got_frame, &packet);
    int ret = avcodec_decode_subtitle2(codecContext, &subtitle, &gotSubtitle, &packet);
    
    if (got_frame) {
        // Process decoded frame
    }
    
    av_frame_free(&frame);
    avcodec_free_context(&codec_ctx);
}
