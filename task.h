#ifndef _TASK_H
#define _TASK_H

//! 任务类
typedef void (*taskFunc)(void*);
class CTask
{
  public:
    CTask() = default;
    virtual ~CTask() = default;

    void setFunc(taskFunc func);
    void setData(void* data); //设置任务数据
    void setNextTask(CTask *task);
    int getTasksRemained();
    CTask *getNextTask();
    void run();

  private:
    taskFunc m_pFunc = nullptr;
    void* m_pData = nullptr; //要执行的任务的具体数据
    CTask* m_nextTask = nullptr;
};

#endif
