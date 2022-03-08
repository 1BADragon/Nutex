#pragma once

#include <mutex>
#include <optional>

#include "lockref.hpp"

namespace nu {

template <typename T>
class Lock {
public:
    using value_type = T;

    template<typename ...Args>
    Lock(Args ...args)
        : _val(args...), _mut()
    {
    }

    ~Lock()
    {
        auto ref = this->lock();
    }

    LockRef<Lock<T>> lock()
    {
        _mut.lock();

        return LockRef<Lock<T>>(this, &_val);
    }

    std::optional<LockRef<Lock<T>>> try_lock()
    {
        if (_mut.try_lock()) {
            return LockRef<Lock<T>>(this, &_val);
        }

        return std::nullopt;
    }


private:
    T _val;
    std::mutex _mut;

    friend class LockRef<Lock<T>>;

    void unlock() {
        _mut.unlock();
    }

};

}
