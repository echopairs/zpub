//
// Created by zsy on 12/29/16.
//

#include <iostream>
#include "helloworld.pb.h"
#include <nsky/sub/physical_sub_service.h>

using namespace nsky;
using namespace service;


int main()
{
    auto physicalNode = std::make_shared<PhysicalSub>();
    physicalNode->RegisterSubscriber("im.helloworld", "tcp://localhost:5563", [](google::protobuf::Message* msg){
        im::helloworld *msg_deal = dynamic_cast<im::helloworld*>(msg);
        std::cout << "deal with im.helloworld message " << std::endl;
        std::cout << msg_deal->GetTypeName() << std::endl;
        std::cout << msg_deal->usrname() << std::endl;
        std::cout << msg_deal->passwd() << std::endl;
        std::cout << msg_deal->email() << std::endl;
        delete msg_deal;
    });
    while(1){}
}
