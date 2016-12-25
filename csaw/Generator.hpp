//
//  Generator.hpp
//  csaw
//
//  Created by Steve on 24/12/2016.
//  Copyright © 2016 Stephen Tierney. All rights reserved.
//

#ifndef Generator_hpp
#define Generator_hpp

#include <stdio.h>
#include <iostream>
#include <thread>
#include <atomic>

#include "IRequestHandler.hpp"

#endif /* Generator_hpp */

class Generator {
private:
    std::thread cur_thread;
    
    std::atomic<bool> shutdown_requested;

    IRequestHandler *req_handler;
    int task_count;
    
    void gen_loop();
    
public:
    Generator(IRequestHandler *rq);
    void wait_finish();
};
