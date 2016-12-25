//
//  RandomLoadBalancer.hpp
//  csaw
//
//  Created by Steve on 25/12/2016.
//  Copyright © 2016 Stephen Tierney. All rights reserved.
//

#ifndef RandomLoadBalancer_hpp
#define RandomLoadBalancer_hpp

#include <stdio.h>
#include <iostream>
#include <queue>
#include <vector>
#include <thread>

#include "IRequestHandler.hpp"
#include "Server.hpp"

class RandomLoadBalancer : public IRequestHandler {
    
private:
    std::thread cur_thread;
    
    std::atomic<bool> shutdown_requested;
    
    std::queue<int> task_q;
    std::mutex task_q_mutex;
    std::condition_variable task_q_cv;
    
    std::vector<Server *> server_vec;
    std::mutex server_v_mutex;
    std::condition_variable server_v_cv;
    
    void worker_loop();
    void process_task(int id);
    
public:
    RandomLoadBalancer();
    virtual void DoRequest(int id);
    void wait_finish();
    void add_server(Server *new_server);
    void start();
};

#endif /* RandomLoadBalancer_hpp */
