//
// Created by zsy on 1/5/17.
//

#include <src/sub/sub_server.h>
#include <nsky/utils/serialization.h>

namespace nsky {
namespace service {

    void SubServer::HandleMessage(const std::string data)
    {
        google::protobuf::Message *message = nsky::utils::decode(data);
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

    void test(google::protobuf::Message *msg)
    {}
    void SubServer::deal_message(google::protobuf::Message *msg)
    {
        if (msg == nullptr) return;
        std::lock_guard<std::mutex> lk(_cbMutex);
        auto iter_map = _message_call_backs.find(msg->GetTypeName());
        if (iter_map != _message_call_backs.end())
        {
            /// QueueTask to taskQueue
            QueueTask(*(iter_map->second.get()), msg);
        }
        else
        {
            // TODO LOG NO THIS SERVICE
        }
    }

    SubServer::SubServer(size_t threadNum):_threadPool(threadNum)
    {
    }

    SubServer::~SubServer()
    {
        std::lock_guard<std::mutex> lk(_cbMutex);
        _message_call_backs.clear();
    }

}
}

