#ifndef _WORKER_H_
#define _WORKER_H_

#include "watcher.h"
#include "zookeeper.h"
#include "common.h"
#include <map>

#include "alenka.h"

using namespace std;

class Worker : public Watcher{
public:
    Worker(ZooKeeper *zk) : Watcher(zk) {
    	alenka::init(NULL);
    }

    ~Worker(){
    	alenka::close();
    }

    bool createWorkspace();
    bool createWorker();
    bool getTasks();
    bool setLoad(int load);
    Task* getTaskInfo(const string& task);

    void RunTask(const string& taskNode);

private:
    void childChange(const std::string& path);

private:
    string m_assign_dir;
    string m_worker_node;
    map<string, Task*> m_tasks;
};

#endif
