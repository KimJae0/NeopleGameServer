#include "TaskQueue.h"
#include <iostream>
#include <thread>

void WorkerFunction(TaskQueue& queue)
{

    Task task;
    while (queue.Pop(task))
{
    std::cout << task.id << " "
              << task.x << " "
              << task.y << std::endl;
}
}

int main()
{
    TaskQueue queue;

    std::thread worker(WorkerFunction, std::ref(queue));

    Task task1;
    task1.id = 101;
    task1.x = 100;
    task1.y = 250;
    task1.HP = 50;
    task1.State = PlayerState::Alive;

    Task task2;
    task2.id = 102;
    task2.x = 200;
    task2.y = 350;
    task2.HP = 40;
    task2.State = PlayerState::Alive;

    Task task3;
    task3.id = 103;
    task3.x = 300;
    task3.y = 450;
    task3.HP = 30;
    task3.State = PlayerState::Alive;

    queue.Push(task1);
    queue.Push(task2);
    queue.Push(task3);

    queue.Stop();

    worker.join();

    return 0;
}