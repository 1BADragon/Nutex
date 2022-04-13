#pragma once

#include <mutex>
#include <optional>

#include "lockref.hpp"

namespace nu {

template <typename T, typename MutexType = std::mutex>
class Lock {
public:
    using value_type = T;
    using ref_type = LockRef<Lock<T, MutexType>>;

    template<typename ...Args>
    Lock(Args ...args)
        : _val(args...), _mut()
    {
    }

    ~Lock()
    {
        auto ref = this->lock();
    }

    ref_type lock()
    {
        _mut.lock();

        return ref_type(this, &_val);
    }

    std::optional<ref_type> try_lock()
    {
        if (_mut.try_lock()) {
            return ref_type(this, &_val);
        }

        return std::nullopt;
    }


private:
    T _val;
    MutexType _mut;

    friend ref_type;

    void unlock() {
        _mut.unlock();
    }

};

}
