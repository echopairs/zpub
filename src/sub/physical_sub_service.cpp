//
// Created by zsy on 1/5/17.
//

#include <nsky/sub/physical_sub_service.h>
#include <src/sub/sub_server.h>
#include <src/sub/zmq_sub/zmq_sub_impl.h>


namespace nsky {
namespace service {

    bool PhysicalSub::UnRegisterSubscriber(const std::string &topic)
    {
        _subImpl->RemoveSubscriber(topic);
        return true;
    }

    PhysicalSub::PhysicalSub()
    {
        auto serviceHandle = std::make_shared<SubServer>(8);
        _subImpl = std::make_shared<nsky::service::ZmqSubImpl>(serviceHandle);
    }

    PhysicalSub::~PhysicalSub()
    {

    }

    bool PhysicalSub::RegisterSubscriber(const std::string &topic, const std::string &address,
                                         std::function<void(google::protobuf::Message *)> cb)
    {
        _subImpl->AddSubscriber(topic, address, cb);
        return true;
    }


}
}


