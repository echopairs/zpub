//
// Created by zsy on 12/28/16.
//

#ifndef ZPUB_PHYSICAL_SUB_CLIENT_H
#define ZPUB_PHYSICAL_SUB_CLIENT_H


#include <memory>

namespace nsky {
namespace service {

    class SubImpl;

    class PhysicalSub
    {
    public:
    private:
        std::shared_ptr<SubImpl> _subImpl;
    };
}   // namespace service
}   // namespace nsky
#endif //ZPUB_PHYSICAL_SUB_CLIENT_H
