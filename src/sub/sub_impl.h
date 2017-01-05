//
// Created by zsy on 1/5/17.
//

#ifndef ZPUB_SUB_IMPL_H
#define ZPUB_SUB_IMPL_H

#include <memory>
#include "sub_server.h"


namespace nsky {
namespace service {

    /// base class
    class SubImpl
    {
    public:
        SubImpl(std::shared_ptr<SubServer> subhandle);
        virtual ~SubImpl();
        bool AddSubscriber(const std::string & topic, const std::string &address, std::function<void(google::protobuf::Message*)> cb);
        bool RemoveSubscriber(const std::string &topic);
        virtual bool Start() = 0;
        virtual bool Stop() = 0;

    protected:
        virtual bool _Subscriber(const std::string &topic, const std::string &address, bool isconnct) = 0;
        virtual bool _UnSubscriber(const std::string &topic) = 0;

        bool HasAddress(const std::string &address);
        std::mutex _sublistsMutex;
        std::map<std::string, std::string> _sublists;       // key:topic, value address

        std::mutex _mappingMutex;
        std::map<std::string, int> _mappingTopic;                // key: address, value: 1 (not use)
        /// deal with recv message handle
        std::shared_ptr<SubServer> _serviceHandle;
    };
}
}



#endif //ZPUB_SUB_IMPL_H
