//
// Created by zsy on 12/19/16.
//

#ifndef ZPUB_SUB_SERVER_H
#define ZPUB_SUB_SERVER_H

/// deal with message

#include <functional>
#include <google/protobuf/message.h>
#include <map>
#include <mutex>
#include <nsky/utils/thread_pool.h>

namespace nsky {
namespace service {

/// just process any recv message on protobuf
using message_callback_t = std::function<void(google::protobuf::Message*)>;
class SubServer
{
public:
    SubServer(size_t thread_size);
    void HandleMessage(const std::string data);
    void AddMessageProcessMode(const std::string &name, message_callback_t cb);
    void RemoveMessageProcessMode(const std::string &name);
    ~SubServer();
private:
    template<typename TFunction, typename... TArgs>
    auto QueueTask(TFunction && function, TArgs&&... args)-> future<typename result_of<TFunction(TArgs...)>::type>
    {
        return _threadPool.QueueTask(forward<TFunction>(function), forward<TArgs>(args)...);
    }
    ThreadPool _threadPool;
    void deal_message(google::protobuf::Message *msg);
    std::mutex _cbMutex;
    std::map<std::string, std::shared_ptr<message_callback_t> > _message_call_backs;
};

}   // namespace service
}   // namespace nsky


#endif //ZPUB_SUB_SERVER_H
