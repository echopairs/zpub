//
// Created by zsy on 12/19/16.
//

#include <serialization.h>
#include "sub_server.h"

namespace nsky {
  namespace service {

    SubServer::SubServer(size_t thread_size):_threadPool(8)
    {

    }
    void SubServer::HandleMessage(const std::string data)
    {
        google::protobuf::Message *message = jrpc::decode(data);
        deal_message(message);
    }

    void SubServer::AddMessageProcessMode(const std::string &name, message_callback_t cb)
    {
        std::lock_guard<std::mutex> lk(_cbMutex);
        _message_call_backs[name] = std::make_shared<message_callback_t >(cb);
    }

    void SubServer::RemoveMessageProcessMode(const std::string &name)
    {
        std::lock_guard<std::mutex> lk(_cbMutex);
        _message_call_backs.erase(name);
    }

    void SubServer::deal_message(google::protobuf::Message* msg)
    {
        if (msg == nullptr) return;
        std::lock_guard<std::mutex> lk(_cbMutex);
        auto iter_map = _message_call_backs.find(msg->GetTypeName());
        if (iter_map != _message_call_backs.end())
        {
            (*(iter_map->second.get()))(msg);
            QueueTask(*(iter_map->second.get()), msg);
        }
        else
        {
            // TODO LOG NO THIS SERVICE
        }
    }

    SubServer::~SubServer()
    {
        std::lock_guard<std::mutex> lk(_cbMutex);
        _message_call_backs.clear();
    }

} // namespace service
} // namespace nsky
