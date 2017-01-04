//
// Created by zsy on 12/29/16.
//

#include <nsky/pub/physical_pub_client.h>
#include "helloworld.pb.h"

#include <iostream>
using namespace nsky;
using namespace client;

int main()
{
    PhysicalPub pub("tcp://*:5563");
    pub.RegisterPublisher("im.helloworld");

    while(1)
    {
        im::helloworld msg;
        msg.set_usrname("zsy");
        msg.set_passwd("12345");
        msg.set_email("736418319@qq.com");
        pub.PublisherMessage(msg, -1);
    }
}
