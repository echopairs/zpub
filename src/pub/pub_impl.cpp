//
// Created by zsy on 1/4/17.
//

#include <nsky/pub/pub_impl.h>
#include <src/pub/pub_stub_factory.h>

namespace nsky {

namespace client {

    PubImpl::PubImpl(const std::string address):_address(address)
    {
        _context = std::make_shared<zmq::context_t>(1);
        _publisher = std::make_shared<zmq::socket_t>(*_context.get(), ZMQ_PUB);
        _publisher->bind(address.c_str());
    }

    PubImpl::~PubImpl() {

    }

    bool PubImpl::RegisterPublisher(const std::string &topic, const std::string &type)
    {
        if (HasTopic(topic))
        {
            //SSPD_LOG_WARNING << "the topic: " << topic << " has already add";
            return false;
        }
        bool success = CreaPublisher(topic,type);
        return success;
    }

    bool PubImpl::UnRegisterPublisher(const std::string &topic)
    {
        if (!HasTopic(topic))
        {
            //SSPD_LOG_INFO << "the topic " << topic << " was not in";
            return true;
        }
        else
        {
            bool success = RemovePublisher(topic);
            return success;
        }
    }

    bool PubImpl::RemovePublisher(const std::string &topic)
    {
        std::lock_guard<std::mutex> lk(_publishersMutex);
        _publishs.erase(topic);
    }

    bool PubImpl::CreaPublisher(const std::string &topic, const std::string &type)
    {
        std::lock_guard<std::mutex> lk(_publishersMutex);
        _publishs[topic] = nsky::client::PublisherSimpleFactory::CreatePublisher(type, topic, _address, _publisher);
        return false;
    }

    bool PubImpl::HasTopic(const std::string &topic)
    {
        std::lock_guard<std::mutex> lk(_publishersMutex);
        auto item = _publishs.find(topic);
        if (item != _publishs.end())
        {
            return true;
        }
        return false;
    }


}}

