#include "TaskQueue.h"
#include <iostream>

void TaskQueue::Push(const Task &task)
{
    {
        std::lock_guard<std::mutex> lock(mtx);

        tasks.push(task);
    }
    cv.notify_one();
}

bool TaskQueue::Pop(Task &task)
{
    std::unique_lock<std::mutex> lock(mtx);

    cv.wait(lock, [this]
            { return (!tasks.empty() || isStop); });

    if (tasks.empty())
    {
        return false;
    }

    task = tasks.front();

    tasks.pop();

    return true;
}

void TaskQueue::Stop()
{
    {
        std::lock_guard<std::mutex> lock(mtx);
        isStop = true;
    }
    cv.notify_all();
}
