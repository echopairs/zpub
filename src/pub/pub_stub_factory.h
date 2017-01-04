//
// Created by zsy on 1/4/17.
//

#ifndef ZPUB_PUB_STUB_FACTORY_H
#define ZPUB_PUB_STUB_FACTORY_H

#include <memory>
#include "publish_interface.h"
#include "stub/zmq_pub_impl.h"

namespace nsky {
namespace client {
    class ZmqPublisher;
    class PublisherSimpleFactory
    {
    public:
        PublisherSimpleFactory(){}
        ~PublisherSimpleFactory(){}
        static std::shared_ptr<IPublisher>CreatePublisher(const std::string &mode,
                                                          const std::string &topic,
                                                          const std::string &address,
                                                          std::shared_ptr<zmq::socket_t> pub)
        {
            return std::make_shared<ZmqPublisher>(topic, address, pub);
        }
    };
}
}

#endif //ZPUB_PUB_STUB_FACTORY_H
