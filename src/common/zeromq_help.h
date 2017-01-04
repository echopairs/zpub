//
// Created by zsy on 12/29/16.
//

#ifndef ZPUB_ZEROMQ_HELP_H
#define ZPUB_ZEROMQ_HELP_H

#include <zmq.hpp>

namespace nsky {
namespace zeromq {
    using namespace zmq;
    class ZmqHelp
    {
    public:
        /// from zhelpers.cpp
        static bool s_send(zmq::socket_t &socket, const std::string &msg)
        {
            zmq::message_t message(msg.size());
            memcpy(message.data(), msg.data(), msg.size());
            return socket.send(message);
        }

        static bool  s_sendmore(zmq::socket_t &socket,  const std::string &msg)
        {
            zmq::message_t message(msg.size());
            memcpy(message.data(), msg.data(), msg.size());
            return socket.send(message, ZMQ_SNDMORE);
        }

        static std::string s_recv(zmq::socket_t & socket)
        {
            zmq::message_t message;
            socket.recv(&message);
            return std::string(static_cast<char*>(message.data()), message.size());
        }
    };
}   // namespace zeromq
}   // namespace nsky

#endif //ZPUB_ZEROMQ_HELP_H
