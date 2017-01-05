//
// Created by zsy on 1/4/17.
//

#ifndef ZPUB_PUBLISH_INTERFACE_H
#define ZPUB_PUBLISH_INTERFACE_H

#include <string>
namespace nsky {
    namespace client {

        class IPublisher
        {
        public:
            IPublisher(const std::string &_topic, const std::string &_address) : _topic(_topic), _address(_address) { }
            virtual ~IPublisher(){}
            virtual bool PublishMessage(const std::string & messge) = 0;
        protected:
            const std::string &get_topic() const
            {
                return _topic;
            }

            void set_topic(const std::string &_topic)
            {
                IPublisher::_topic = _topic;
            }

            const std::string &get_address() const
            {
                return _address;
            }

            void set_address(const std::string &_address)
            {
                IPublisher::_address = _address;
            }

        private:
            std::string _topic;
            std::string _address;
        };
    }   // namespace client
}   // namespace msky

#endif //ZPUB_PUBLISH_INTERFACE_H
