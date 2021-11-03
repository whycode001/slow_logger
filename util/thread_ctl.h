#ifndef SLOWLOGGER_THREADCTL_H
#define SLOWLOGGER_THREADCTL_H

#include <mutex>

namespace slow_logger{

class ThreadMtx
{
public:
    void Lock();
private:
    std::mutex _mtx;
};

class LockGuard
{
public:
    LockGuard(const ThreadMtx& mtx);
    ~LockGuard();

    LockGuard(const LockGuard&) = delete;
    LockGuard& operator=(const LockGuard&) = delete;
};

}

#endif