#include <nutex/spinlock.hpp>

namespace nu {

static void busy_wait();

SpinLock::SpinLock()
    : _lock(false)
{
}

void SpinLock::lock()
{
    lock_impl();
}

bool SpinLock::try_lock()
{
    return !_lock.exchange(true, std::memory_order_acquire);
}

void SpinLock::unlock()
{
    _lock.store(false, std::memory_order_release);
}

void SpinLock::lock_impl()
{
    for (;;) {
        if (!_lock.exchange(true, std::memory_order_acquire)) {
            break;
        }
        while (_lock.load(std::memory_order_relaxed)) {
            busy_wait();
        }
    }
}

static inline void busy_wait()
{
#if defined __i386__ || defined __x86_64__
  __builtin_ia32_pause();
#elif defined __ia64__
  __asm volatile("hint @pause" : : : "memory");
#elif defined __sparc__ && (defined __arch64__ || defined __sparc_v9__)
  __asm volatile("membar #LoadLoad" : : : "memory");
#else
  __asm volatile("" : : : "memory");
#endif
}
}
