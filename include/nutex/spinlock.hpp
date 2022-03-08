#pragma once

#include <optional>
#include <atomic>

#include "lockref.hpp"

namespace nu {

template <typename T>
class SpinLock
{
public:
    using value_type = T;

    template<typename ...Args>
    SpinLock(Args ...args)
        : _val(args...), _lock(false)
    {}

    LockRef<SpinLock<T>> lock()
    {
        lock_impl();

        return LockRef<SpinLock<T>>(this, &_val);
    }

    std::optional<SpinLock<T>> try_lock()
    {
        if (!_lock.exchange(true, std::memory_order_acquire)) {
            return LockRef<SpinLock<T>>(this, &_val);
        }

        return std::nullopt;
    }

private:
    T _val;
    std::atomic<bool> _lock;

    friend class LockRef<SpinLock<T>>;

    void lock_impl() {
      for (;;) {
        if (!_lock.exchange(true, std::memory_order_acquire)) {
          break;
        }
        while (_lock.load(std::memory_order_relaxed)) {
          __builtin_ia32_pause();
        }
      }
    }

    void unlock() {
        _lock.store(false, std::memory_order_release);
    }

};

}
