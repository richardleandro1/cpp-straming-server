//
//  VideoSession.hpp
//  Server
//
//  Created by Richard on 04/06/24.
//

#ifndef VideoSession_hpp
#define VideoSession_hpp

#include <iostream>
#include <boost/asio.hpp>
#include <memory>
#include <vector>

class AVCodecContext;
class AVFormatContext;

using boost::asio::ip::tcp;

class videoSession : public std::enable_shared_from_this<videoSession> {
public:
  videoSession(tcp::socket socket);
  ~videoSession();

  void start();

private:
  void do_read();
  void decode_video(const char* data, size_t size);

  tcp::socket socket_;
  std::vector<char> data_;
  AVCodecContext* codec_context_;
  AVFormatContext* av_format_context_; // Assuming this is not used
};


#endif /* VideoSession_hpp */
