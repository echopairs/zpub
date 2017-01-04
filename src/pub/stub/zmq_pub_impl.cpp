//
// Created by zsy on 1/4/17.
//


//#include <sspdlog/sspdlog.h>
#include "zmq_pub_impl.h"
#include "../../common/zeromq_help.h"
#include <iostream>

namespace nsky {
namespace client {

void nsky::client::ZmqPublisher::SetHandle(std::shared_ptr<zmq::socket_t> publisher) {
    _publisher = publisher;
}

    ZmqPublisher::ZmqPublisher(const std::string &topic, const std::string &address, std::shared_ptr<zmq::socket_t> pub)
                                :IPublisher(topic, address),
                                 _publisher(pub)
    {
    }

    ZmqPublisher::~ZmqPublisher() {

    }

    bool ZmqPublisher::PublishMessage(const std::string &message)
    {
        try
        {
            std::cout << "++++topic is ++++ " << get_topic() << std::endl;
            std::cout << "++++message is ++++" << message << std::endl;
            nsky::zeromq::ZmqHelp::s_sendmore(*_publisher.get(), get_topic());
            nsky::zeromq::ZmqHelp::s_send(*_publisher.get(), message);
            return true;
        }
        catch(...)
        {
            //SSPD_LOG_ERROR << "send message failed: the message is " << message;
            return false;
        }
    }

}
}
