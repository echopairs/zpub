//
// Created by zsy on 1/4/17.
//

#ifndef ZPUB_ZMQ_PUB_IMPL_H
#define ZPUB_ZMQ_PUB_IMPL_H

#include <memory>
#include <zmq.hpp>
#include <src/pub/publish_interface.h>
#include "../publish_interface.h"

namespace nsky {
namespace client {
    class ZmqPublisher: public IPublisher
    {
    public:
        ZmqPublisher(const std::string &topic, const std::string &address, std::shared_ptr<zmq::socket_t> pub);
        void SetHandle(std::shared_ptr<zmq::socket_t> publisher);
        ~ZmqPublisher();
        bool PublishMessage(const std::string &message) override ;
    private:
        std::shared_ptr<zmq::socket_t> _publisher;
    };
}
}
#endif //ZPUB_ZMQ_PUB_IMPL_H
