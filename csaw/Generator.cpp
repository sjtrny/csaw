//
//  Generator.cpp
//  csaw
//
//  Created by Steve on 24/12/2016.
//  Copyright © 2016 Stephen Tierney. All rights reserved.
//

#include "Generator.hpp"


void Generator::gen_loop() {
    while (!shutdown_requested) {
        struct timespec tim_in, tim_out;
        tim_in.tv_sec = 0L;
        tim_in.tv_nsec = 5000000L;
        
        nanosleep(&tim_in, &tim_out);
        
        req_handler->DoRequest(task_count);
        task_count += 1;
    }
}


Generator::Generator(IRequestHandler *rq) {
    shutdown_requested = false;
    task_count = 0;
    req_handler = rq;
    
    cur_thread = std::thread (&Generator::gen_loop, this);
}

void Generator::wait_finish() {
    std::cout << "Generator Stopping!\n";
    shutdown_requested = true;
    cur_thread.join();
    std::cout << "Generator Stopped!\n";
}
