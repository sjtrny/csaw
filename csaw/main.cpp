//
//  main.cpp
//  csaw
//
//  Created by Steve on 23/12/2016.
//  Copyright © 2016 Stephen Tierney. All rights reserved.
//

#include <iostream>

#include "Generator.hpp"
#include "Server.hpp"
#include "RandomLoadBalancer.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Program Started!\n";

    // Startup order:
    //  1. Servers
    //  2. Load Balancer
    //  3. Request Generator

    Server *sv = new Server();
    
    RandomLoadBalancer *lb = new RandomLoadBalancer();
    lb->add_server(sv);
    lb->start();
    
    Generator *gen = new Generator(lb);
    
    // Generate requests for 4 seconds
    struct timespec tim_in, tim_out;
    tim_in.tv_sec = 4L;
    tim_in.tv_nsec = 0;
    
    nanosleep(&tim_in, &tim_out);
    
    
    // Shutdown order:
    //  1. Request Generator
    //  2. Load Balancer
    //  3. Servers
    
    gen->wait_finish();
    
    lb->wait_finish();
    
    sv->wait_finish();
    
    return 0;
}
