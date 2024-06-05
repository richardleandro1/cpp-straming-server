//
//  VideoSession.cpp
//  Server
//
//  Created by Richard on 04/06/24.
//

#include "VideoSession.hpp"
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <vector>

extern "C" {
    #include <libavcodec/codec.h>
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libswscale/swscale.h>
}

using boost::asio::ip::tcp;

class video_session : public std::enable_shared_from_this<video_session> {
public:
    video_session(tcp::socket socket)
        : socket_(std::move(socket)), codec_context_(nullptr), av_format_context_(nullptr) {
        // Inicializar os componentes do FFmpeg para decodificação de vídeo
        //avcodec_register_all();

        // Encontre o decoder H.264
        //AVCodec* codec = avcodec_find_decoder(AV_CODEC_ID_H264);
        const AVCodec* codec = avcodec_find_decoder(AV_CODEC_ID_H264);
        
        if (!codec) {
            throw std::runtime_error("Codec not found.");
        }

        codec_context_ = avcodec_alloc_context3(codec);
        if (!codec_context_) {
            throw std::runtime_error("Could not allocate video codec context.");
        }

        // Abre o codec
        if (avcodec_open2(codec_context_, codec, nullptr) < 0) {
            throw std::runtime_error("Could not open codec.");
        }
    }

    ~video_session() {
        avcodec_free_context(&codec_context_);
    }

    void start() {
        do_read();
    }

private:
    void do_read() {
        auto self(shared_from_this());
        socket_.async_read_some(boost::asio::buffer(data_),
            [this, self](boost::system::error_code ec, std::size_t length) {
                if (!ec) {
                    decode_video(data_.data(), length);
                    do_read();
                }
            });
    }

    void decode_video(const char* data, size_t size) {
        AVPacket packet;
        av_init_packet(&packet);
        packet.data = (uint8_t*)data;
        packet.size = size;

        int response = avcodec_send_packet(codec_context_, &packet);
        if (response < 0) {
            std::cerr << "Error while sending packet to decoder: " << av_err2str(response) << std::endl;
            return;
        }

        while (response >= 0) {
            AVFrame* frame = av_frame_alloc();
            response = avcodec_receive_frame(codec_context_, frame);
            if (response == AVERROR(EAGAIN) || response == AVERROR_EOF) {
                av_frame_free(&frame);
                break;
            } else if (response < 0) {
                std::cerr << "Error while receiving frame from decoder: " << av_err2str(response) << std::endl;
                av_frame_free(&frame);
                break;
            }

            // Aqui você poderia processar o frame, por exemplo, exibindo ou salvando
            av_frame_free(&frame);
        }
    }

    tcp::socket socket_;
    std::vector<char> data_{static_cast<char>(4096)};
    AVCodecContext* codec_context_;
    AVFormatContext* av_format_context_;
};

// O restante do servidor permanece o mesmo...
