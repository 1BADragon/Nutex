#pragma once

#include <optional>
#include <atomic>

#include "lockref.hpp"

namespace nu {

class SpinLock
{
public:
    SpinLock();

    void lock();

    bool try_lock();

    void unlock();

private:
    std::atomic<bool> _lock;

    void lock_impl();
};

}
