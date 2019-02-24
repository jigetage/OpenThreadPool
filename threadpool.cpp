#include "threadpool.h"
#include "task.h"

bool CThreadPool::m_bStopAllTasks = false;
CTask* CThreadPool::m_pCurTask = nullptr;
pthread_mutex_t CThreadPool::m_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t CThreadPool::m_cond = PTHREAD_COND_INITIALIZER;

void CThreadPool::setTaskList(CTask *task)
{
    m_pCurTask = task;
}

void CThreadPool::startThreadPool(const int &nThreadsCount)
{
    for(int i = 0; i < nThreadsCount; i++)
    {
        pthread_t pTid;
        pthread_create(&pTid, NULL, threadFunc, NULL);
        m_vecThreads.push_back(pTid);
    }
}

void CThreadPool::stopAllTasks()
{
    m_bStopAllTasks = true;
}

int CThreadPool::getRemainedTasksCount()
{
    if (nullptr == m_pCurTask) {
        return 0;
    }
    return m_pCurTask->getTasksRemained();
}

void* CThreadPool::threadFunc(void*)
{
    while (!m_bStopAllTasks) {
        //! get current task
        pthread_mutex_lock(&m_mutex);
        if (nullptr == m_pCurTask) {
            pthread_mutex_unlock(&m_mutex);
            break;
        }
        CTask* pTask = m_pCurTask;
        m_pCurTask = m_pCurTask->getNextTask();
        pthread_mutex_unlock(&m_mutex);

        pTask->run();
    }
    return 0;
}

void CThreadPool::waitForThreadEnded()
{
    for (auto i : m_vecThreads) {
        pthread_join(i, nullptr);
    }
}
