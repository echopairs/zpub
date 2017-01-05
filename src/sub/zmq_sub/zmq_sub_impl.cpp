//
// Created by zsy on 1/5/17.
//

#include <src/common/zeromq_help.h>
#include "zmq_sub_impl.h"

namespace nsky {
namespace service {

    ZmqSubImpl::ZmqSubImpl(std::shared_ptr<SubServer> subhandle)
                                :SubImpl(subhandle),
                                 _stop(false),
                                 _running(false)
    {
        _context = std::make_shared<zmq::context_t>(1);
        _subscriber = std::make_shared<zmq::socket_t>(*_context.get(), ZMQ_SUB);
    }

    ZmqSubImpl::~ZmqSubImpl() {

    }

    bool ZmqSubImpl::Start()
    {
        if (_running)
        {
            // TODO LOG
            return true;
        }
        else
        {
            _recvThread = std::make_shared<std::thread>(&ZmqSubImpl::RecvMessage, this);
            _running = true;
        }
        return true;
    }

    bool ZmqSubImpl::Stop()
    {
        _stop = true;
        _running = false;
        return true;
    }

    bool ZmqSubImpl::_Subscriber(const std::string &topic, const std::string &address, bool isconnect)
    {
        /// have already connect, just sub
        if (!isconnect)
        {
            _subscriber->connect(address.c_str());
        }
        _subscriber->setsockopt(ZMQ_SUBSCRIBE, topic.c_str(), topic.size());
        Start();
        return true;
    }

    bool ZmqSubImpl::_UnSubscriber(const std::string &topic) {
        return false;
    }

    void ZmqSubImpl::RecvMessage()
    {
        while(!_stop)
        {
            std::string header;
            std::string message;
            // blocking waiting publish data
            header = zeromq::ZmqHelp::s_recv(*(_subscriber.get()));
            message = zeromq::ZmqHelp::s_recv(*(_subscriber.get()));
            _serviceHandle->HandleMessage(message);
        }
    }


}
}

