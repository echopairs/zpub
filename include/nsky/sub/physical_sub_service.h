//
// Created by zsy on 12/28/16.
//

#ifndef ZPUB_PHYSICAL_SUB_SERVICE_H
#define ZPUB_PHYSICAL_SUB_SERVICE_H


#include <memory>
#include <google/protobuf/message.h>

namespace nsky {
namespace service {

    class SubImpl;

    class PhysicalSub
    {
    public:
        PhysicalSub();
        ~PhysicalSub();
        bool UnRegisterSubscriber(const std::string &topic);
        bool RegisterSubscriber(const std::string &topic, const std::string &address, std::function<void(google::protobuf::Message*)> cb);
    private:
        std::shared_ptr<SubImpl> _subImpl;
    };
}   // namespace service
}   // namespace nsky
#endif //ZPUB_PHYSICAL_SUB_CLIENT_H
