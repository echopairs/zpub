//
// Created by zsy on 1/4/17.
//

#ifndef ZPUB_PUB_IMPL_H
#define ZPUB_PUB_IMPL_H

#include <map>
#include <type_traits>
#include <google/protobuf/message.h>
#include <nsky/utils/serialization.h>
#include <zmq.hpp>
#include "publish_interface.h"


namespace nsky {
namespace client {

    class PubImpl
    {
    public:
        /// message is protobuf data, first we get message type, then encode message to string, lastly we
        /// send message by the IPublisher
        template <typename T>
        void PublishMessage(T & message, int timeout = -1)
        {
            /// check message, the message need protobuf
            static_assert(std::is_base_of<::google::protobuf::Message, T>::value, "Unsupported type");

            /// encode message
            std::string encode_message = nsky::utils::encode(message);

            /// check topic
            const std::string &type_name = message.GetTypeName();
            if(HasTopic(type_name))
            {
                /// the socket_t not thread safety
                std::lock_guard<std::mutex>lk(_sendMutex);
                _publishs[message.GetTypeName()]->PublishMessage(encode_message);
            }

        }
        PubImpl(const std::string address);
        virtual ~PubImpl();
        bool RegisterPublisher(const std::string &topic, const std::string &type);
        bool UnRegisterPublisher(const std::string &topic);

    private:
        bool RemovePublisher(const std::string &topic);
        bool CreaPublisher(const std::string &topic, const std::string &type);
        std::string _address;   /// all message send by this address
        std::mutex _publishersMutex;
        bool HasTopic(const std::string &topic);
        /// key:topic, value:IPublisher
        std::map<std::string, std::shared_ptr<IPublisher>> _publishs;

        std::mutex _sendMutex;

    private:
        /// just for zmq
        std::shared_ptr<zmq::context_t> _context;
        std::shared_ptr<zmq::socket_t> _publisher;
    };
}
}
#endif //ZPUB_PUB_IMPL_H
