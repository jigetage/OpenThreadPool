#include "task.h"

void CTask::setFunc(taskFunc func)
{
    m_pFunc = func;
}

void CTask::setData(void *data)
{
    m_pData = data;
}

void CTask::setNextTask(CTask *task)
{
    m_nextTask = task;
}

int CTask::getTasksRemained()
{
    CTask* pTask = m_nextTask;
    int count = 1;
    while (nullptr != pTask) {
        ++count;
        pTask = pTask->getNextTask();
    }
    return count;
}

CTask* CTask::getNextTask()
{
    return m_nextTask;
}

void CTask::run()
{
    m_pFunc(m_pData);
}
