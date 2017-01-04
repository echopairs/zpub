//
// Created by zsy on 12/28/16.
//

#ifndef ZPUB_PHYSICAL_PUB_CLIENT_H
#define ZPUB_PHYSICAL_PUB_CLIENT_H


#include <memory>
#include <src/pub/pub_impl.h>  // bad design

namespace nsky {
    /// pub belong to client
namespace client {

    class PhysicalPub
    {
    public:
        PhysicalPub(const std::string address);
        template <typename T>
        void PublisherMessage(T &message, int timeout = -1)
        {
            _pubImpl->PublishMessage(message);
        }
        bool UnRegisterPublisher(const std::string &topic);
        bool RegisterPublisher(const std::string &topic, const std::string &type = "default");
    private:
        std::shared_ptr<PubImpl> _pubImpl;
    };
}
}

#endif //ZPUB_PHYSICAL_PUB_CLIENT_H
