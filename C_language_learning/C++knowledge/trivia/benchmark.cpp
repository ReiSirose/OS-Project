#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <atomic>
#include <pthread.h>


struct CompactCounters {
    std::atomic<long> c1 {0};
    std::atomic<long> c2 {0};
    std::atomic<long> c3 {0};
    std::atomic<long> c4 {0};
};

struct PaddedCounters {
    alignas(64) std::atomic<long> c1 {0};
    alignas(64) std::atomic<long> c2 {0};
    alignas(64) std::atomic<long> c3 {0};
    alignas(64) std::atomic<long> c4 {0};
};


template <typename T>
void benchmark(const std::string& name) {
    T counters;
    const int num_threads = 4;
    const long iterations = 1'000'000'00;
    std::vector<std::thread> threads;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&counters, i, iterations]() {
            if (i == 0) counters.c1.fetch_add(1, std::memory_order_relaxed);
            else if (i == 1) counters.c2.fetch_add(1, std::memory_order_relaxed);
            else if (i == 2) counters.c3.fetch_add(1, std::memory_order_relaxed);
            else counters.c4.fetch_add(1, std::memory_order_relaxed);
        });
    }

    for (auto& t : threads) t.join();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << name << ": " << elapsed.count() << " ms" << std::endl;
}

int main() {
    benchmark<CompactCounters>("Compact (False Sharing)");
    benchmark<PaddedCounters>("Padded (No False Sharing)");
    return 0;
}