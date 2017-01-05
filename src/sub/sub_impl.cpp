//
// Created by zsy on 1/5/17.
//

#include "sub_impl.h"

namespace nsky {
namespace service {

    SubImpl::SubImpl(std::shared_ptr<SubServer> subhandle):_serviceHandle(subhandle){

    }

    SubImpl::~SubImpl() {

    }

    bool SubImpl::AddSubscriber(const std::string &topic, const std::string &address, std::function<void(google::protobuf::Message*)> cb)
    {
        _serviceHandle->AddMessageProcessMode(topic, cb);
        if (HasAddress(address))
        {
            //SSPD_LOG_WARNING << "the address: " << address << " was alreadly used ";
            _Subscriber(topic, address, true);
            return false;
        }

        {
            std::lock_guard<std::mutex> lk(_mappingMutex);
            _mappingTopic[address] = 1;
        }

        std::lock_guard<std::mutex> lk(_sublistsMutex);
        auto it = _sublists.find(topic);
        if (it == _sublists.end())
        {
            _sublists[topic] = address;
            _Subscriber(topic, address, false);
        }
        return true;
    }

    bool SubImpl::RemoveSubscriber(const std::string &topic)
    {
        std::lock_guard<std::mutex> lk(_sublistsMutex);
        _sublists.erase(topic);
        _UnSubscriber(topic);
        return false;
    }

    bool SubImpl::HasAddress(const std::string &address)
    {
        std::lock_guard<std::mutex> lk(_mappingMutex);
        auto it = _mappingTopic.find(address);
        if (it != _mappingTopic.end())
        {
            return true;
        }
        return false;
    }


}
}

