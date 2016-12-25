//
//  Server.cpp
//  csaw
//
//  Created by Steve on 24/12/2016.
//  Copyright © 2016 Stephen Tierney. All rights reserved.
//

#include "Server.hpp"

Server::Server() {
    shutdown_requested = false;
    
    max_threads = 5;
    thread_vec.reserve(max_threads);
    
    for (int i = 0; i < max_threads; i++)
    {
        thread_vec.emplace_back(&Server::worker_loop, this);
    }
}

void Server::wait_finish() {
    std::cout << "Server Shutting Down!\n";
    
    shutdown_requested = true;
    
    task_q_cv.notify_all();
    
    for (int i = 0; i < thread_vec.size(); i++)
    {
        
        if (thread_vec[i].joinable())
        {
            thread_vec[i].join();
        }
        std::cout << "Server Thread " << i << " Ended!\n";
    }
    
    std::cout << "Server Stopped!\n";
}

void Server::DoRequest(int id) {
    
    std::lock_guard<std::mutex> lock(task_q_mutex);
    task_q.push(id);
    task_q_cv.notify_all();
    
    std::cout << "Task added to queue!\n";
}

void Server::worker_loop() {
    
    for (;;) {
        // Check if we should shutdown
        if (task_q.empty() && shutdown_requested)
        {
            break;
        }
        else
        {
            std::unique_lock<std::mutex> lock(task_q_mutex);
            
            // Shutdown clause used to break loop when woken due to shutdown message
            while (task_q.empty() && !shutdown_requested)
            {
                task_q_cv.wait(lock);
            }
            
            if (!task_q.empty())
            {
                int id = task_q.front();
                task_q.pop();
                lock.unlock();
                
                process_task(id);
            }
        }
    }
}


void Server::process_task(int id) {
    // Do work
    struct timespec tim_in, tim_out;
    tim_in.tv_sec = 0L;
    tim_in.tv_nsec = 55000000L;
    
    nanosleep(&tim_in, &tim_out);
    
    std::cout << "Task " << id << " complete!\n";
}

