//
// Created by zsy on 12/20/16.
//

#ifndef ZPUB_SUB_PROXY_H
#define ZPUB_SUB_PROXY_H

#include <mutex>
#include <map>
#include <memory>
#include "sub_server.h"

namespace nsky {
namespace service {

class ISubscriber;

class SubProxy
{
public:
    SubProxy(std::shared_ptr<SubServer>sh);
    virtual ~SubProxy();
    bool AddPublisher(const std::string &topic, const std::string &address);
    bool RemovePublisher(const std::string &topic);
private:
    bool HasAddress(const std::string &address);
    /// each address to recv only the special message
    std::mutex _mappingMutex;
    std::map<std::string , std::string> _mappingTopic;  // key: address, value: message topic

    std::mutex _sublistsMutex;
    std::map<std::string, std::shared_ptr<ISubscriber> > _sublists; // key: topic, value: sub handle

    /// deal with recv message handle
    std::shared_ptr<SubServer> _serviceHandle;
};
} // namespace service
} // namespace nsky 

#endif //NTON_SUB_PROXY_H
