#include "task.h"
#include "threadpool.h"
#include <iostream>
#include <unistd.h>
#include <memory.h>
#include <time.h>

#define TIME_SLEEPED_IN_MILLISECONDS 1000
#define THREADS_COUNT_IN_POOL 20
#define TASKS_COUNT 100

void func(void* param)
{
    int taskData = *((int*)param);
    std::cout << "task " << taskData << " starts." << std::endl;
    usleep(TIME_SLEEPED_IN_MILLISECONDS * 1000);
    std::cout << "task " << taskData << " ends." << std::endl;
}

int main()
{
    time_t time1 = time((time_t*)nullptr);
    std::cout << "start threading pool" << std::endl;
    
    //! generate tasks
    CTask* firstTask = new CTask;
    int num = 0;
    firstTask->setData((void*)&num);
    firstTask->setFunc(func);
    
    CTask* curTask = new CTask;
    for (int i = 1; i < TASKS_COUNT; i++) {
        CTask* task = new CTask;
        int* num = new int(i);
        task->setData((void*)num);
        task->setFunc(func);
        if (1 == i) {
            firstTask->setNextTask(task);
        }
        else {
            curTask->setNextTask(task);
            if ((TASKS_COUNT - 1) == i) {
                task->setNextTask(nullptr);
            }
        }
        curTask = task;
    }
    std::cout << firstTask->getTasksRemained() << std::endl;
    
    //! create threadpool
    std::shared_ptr<CThreadPool> threadpool = std::make_shared<CThreadPool>();
    threadpool->setTaskList(firstTask);
    threadpool->startThreadPool(THREADS_COUNT_IN_POOL);
    threadpool->waitForThreadEnded();
    time_t time2 = time((time_t*)nullptr);
    std::cout << "time elapsed: " << time2 - time1 << " seconds." << std::endl;
    return 0;
}
