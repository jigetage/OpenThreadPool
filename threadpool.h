#ifndef _THREAD_POOL_H
#define _THREAD_POOL_H

/*
实现思路：先完成所有任务的创建，并把任务加入到链表中保存。然后创建线程池，并把保存任务的链表放入线程池，线程池开始依次执行任务。
*/

#include <vector>
#include <string>
#include <pthread.h>

class CTask;

class CThreadPool
{
  public:
    CThreadPool() = default;
    virtual ~CThreadPool() = default;

    void setTaskList(CTask *task);
    void startThreadPool(const int &nThreadsCount);
    void stopAllTasks();
    int getRemainedTasksCount();

    static void* threadFunc(void*);
    void waitForThreadEnded();

  private:
    std::vector<pthread_t> m_vecThreads;
    static CTask *m_pCurTask;
    static bool m_bStopAllTasks;
    static pthread_mutex_t m_mutex;
    static pthread_cond_t m_cond;
};

#endif
