//
//  Server.hpp
//  csaw
//
//  Created by Steve on 24/12/2016.
//  Copyright © 2016 Stephen Tierney. All rights reserved.
//

#ifndef Server_hpp
#define Server_hpp

#include <stdio.h>
#include <iostream>
#include <queue>
#include <vector>
#include <thread>

#include "IRequestHandler.hpp"

class Server : public IRequestHandler {
    
private:
    bool shutdown_requested;
    
    std::queue<int> task_q;
    std::mutex task_q_mutex;
    std::condition_variable task_q_cv;
    
    std::vector<std::thread> thread_vec;
    int max_threads;
    
    void worker_loop();
    void process_task(int id);
    
public:
    Server();
    virtual void DoRequest(int id);
    void wait_finish();
};

#endif /* Server_hpp */
