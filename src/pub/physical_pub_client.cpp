//
// Created by zsy on 1/4/17.
//

#include <nsky/pub/physical_pub_client.h>


namespace nsky {
namespace client {

    bool PhysicalPub::UnRegisterPublisher(const std::string &topic)
    {
        return _pubImpl->UnRegisterPublisher(topic);
    }

    bool PhysicalPub::RegisterPublisher(const std::string &topic, const std::string &type)
    {
        return _pubImpl->RegisterPublisher(topic, type);
    }

//    template<typename T>
//    void PhysicalPub::PublisherMessage(T &message, int timeout)
//    {
//        _pubImpl->PublishMessage(message);
//    }

    PhysicalPub::PhysicalPub(const std::string address) {
        _pubImpl = std::make_shared<PubImpl>(address);
    }


}
}