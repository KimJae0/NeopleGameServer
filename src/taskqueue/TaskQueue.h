#pragma once

#include "Player.h"
#include <queue>
#include <mutex>
#include <condition_variable>

struct Task{
    int id;
    int x;
    int y;
    int HP;
    PlayerState State;
};


class TaskQueue{

    public:
        void Push(const Task& task);
        bool Pop(Task& task);
        void Stop();



    private:
        std::queue<Task> tasks;
        std::mutex mtx;
        std::condition_variable cv;
        bool isStop = false;



};