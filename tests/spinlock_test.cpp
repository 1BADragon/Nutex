#include <assert.h>
#include <vector>
#include <thread>

#include <nutex.hpp>

nu::SpinLock<int> val(0);

void thread_entry() {
    auto locked = val.lock();

    (*locked)++;
}

int main() {
    std::vector<std::thread> threads;

    for (size_t i = 0; i < 10; ++i) {
        threads.emplace_back(thread_entry);
    }

    for (auto &t : threads) {
        t.join();
    }

    {
        auto locked = val.lock();

        assert(*locked == 10);
    }

    return 0;
}
