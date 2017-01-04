//
// Created by zsy on 12/28/16.
//

#ifndef ZPUB_SERIALIZATION_H
#define ZPUB_SERIALIZATION_H

#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#include <algorithm>
#include <string>
#include <iostream>
#include <netinet/in.h>
#include <mutex>
//#include <sspdlog/sspdlog.h>

namespace nsky {
namespace utils {

    static google::protobuf::Message* create_message(const std::string type_name)
    {
        google::protobuf::Message* message = nullptr;
        const google::protobuf::Descriptor* descriptor =  \
                google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(type_name);
        if (descriptor)
        {
            const google::protobuf::Message* prototype =
                    google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
            if (prototype)
            {
                message = prototype->New();
            }

        }
        return message;
    }

    /// encode messsage before send
    static std::string encode(const google::protobuf::Message &message)
    {
        std::string res;
        const std::string &type_name = message.GetTypeName();
        size_t type_len = type_name.length();
        size_t net_len = htonl(type_len);
        res.resize(sizeof(size_t));
        /// add type's length
        res.append(reinterpret_cast<char*>(&net_len), sizeof(size_t));
        /// add type's type
        res.append(type_name.c_str(), type_len);
        bool success = message.AppendToString(&res);
        if (success)
        {
            size_t len = htonl(res.length());
            std::copy(reinterpret_cast<char*>(&len), reinterpret_cast<char*>(&len) + sizeof(len),
                      res.begin());
        }
        else
        {
            /// TOLOG
            res.clear();
        }
        return res;
    }

    /// decode Message
    static google::protobuf::Message* decode(const std::string& buf)
    {
        if (buf.empty()) return nullptr;
        const char* ptr = buf.data();
        size_t packet_len = ntohl(*((size_t*)ptr));
        if (buf.length() != packet_len)
        {
            /// TODO log receved error buf
           // SSPD_LOG_WARNING << "received error buf";
            return nullptr;
        }

        size_t type_name_len = ntohl(*(size_t*)(ptr + sizeof(size_t)));
        const char* type_begin = ptr + 2 * sizeof(size_t);
        const char* type_end = type_begin + type_name_len;

        /// Get the typename
        std::string type_name(type_begin, type_end);
        /// Create the protobuf message
        google::protobuf::Message* result = create_message(type_name);
        if(!result)
        {
            // TODO log
           // SSPD_LOG_WARNING << "create_message failed, the typename is " << type_name;
            return result;
        }
        std::string packet(type_end, buf.length() - 2 * sizeof(size_t) - type_name_len);
        /// serialized from string
        if (!result->ParseFromString(packet))
        {
            delete result;
            return nullptr;
        }
        return result;
    }

}   // namespace utils
}   // namespace nsky
#endif //ZPUB_SERIALIZATION_H
