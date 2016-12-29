//
// Created by zsy on 12/28/16.
//

#ifndef ZPUB_PHYSICAL_PUB_CLIENT_H
#define ZPUB_PHYSICAL_PUB_CLIENT_H


#include <memory>

namespace nsky {
    /// pub belong to client
namespace client {

    class PubImpl;
    enum class PubType unsigned int;

    class PhysicalPub
    {
    public:
    private:
        std::shared_ptr<PubImpl> _pubImpl;
    };
}
}

#endif //ZPUB_PHYSICAL_PUB_CLIENT_H
