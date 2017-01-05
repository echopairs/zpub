//
// Created by zsy on 1/5/17.
//

#ifndef ZPUB_ZMQ_SUB_IMPL_H
#define ZPUB_ZMQ_SUB_IMPL_H

#include <src/sub/sub_impl.h>
#include <zmq.hpp>

namespace nsky {
namespace service {

class ZmqSubImpl : public SubImpl
{
public:
    ZmqSubImpl(std::shared_ptr<SubServer> subhandle);
    virtual ~ZmqSubImpl();

protected:
    bool _Subscriber(const std::string &topic, const std::string &address, bool isconnect) override ;
    bool _UnSubscriber(const std::string &topic) override;
    bool Start() override ;
    bool Stop() override ;

private:
    void RecvMessage();
    std::shared_ptr<std::thread> _recvThread;
    std::shared_ptr<zmq::context_t> _context;
    std::shared_ptr<zmq::socket_t> _subscriber;
    std::atomic<bool> _running;
    std::atomic<bool> _stop;


};

}
}
#endif //ZPUB_ZMQ_SUB_IMPL_H
