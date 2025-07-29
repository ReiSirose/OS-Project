#define _GNU_SOURCE // Required for CPU_SET and related macros on some systems
#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>
#include <algorithm>
#include <sched.h>
#include <pthread.h> 

void consume_value(volatile long long& val) {
    // This function does nothing, but ensures 'val' is used
    // and prevents compiler from optimizing away the access
}

int main() {
    const size_t L1_SIZE_BYTES = 32 * 1024;  // e.g., 32KB
    const size_t L2_SIZE_BYTES = 256 * 1024; // e.g., 256KB
    const size_t L3_SIZE_BYTES = 6 * 1024 * 1024; // e.g., 8MB
    const size_t CACHE_LINE_SIZE = 64; // Typical for x86

    const size_t TEST_SIZE_L1_HIT = L1_SIZE_BYTES / sizeof(long long);
    const size_t TEST_SIZE_L2_HIT = L2_SIZE_BYTES / sizeof(long long);
    const size_t TEST_SIZE_L3_HIT = L3_SIZE_BYTES / sizeof(long long);
    const size_t TEST_SIZE_RAM = L3_SIZE_BYTES * 2 / sizeof(long long);

    std::vector<long long> data_l1(TEST_SIZE_L1_HIT);
    std::vector<long long> data_l2(TEST_SIZE_L2_HIT);
    std::vector<long long> data_l3(TEST_SIZE_L3_HIT);
    std::vector<long long> data_ram(TEST_SIZE_RAM);

    std::iota(data_l1.begin(), data_l1.end(), 0);
    std::iota(data_l2.begin(), data_l2.end(), 0);
    std::iota(data_l3.begin(), data_l3.end(), 0);
    std::iota(data_ram.begin(), data_ram.end(), 0);

    // --- CPU Pinning ---
    int core_to_pin = 0; // Pin to CPU core 0 (or choose another)
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_to_pin, &cpuset);

    // Pin the current process (or just the main thread)
    // For a multi-threaded application, you'd call this for each relevant pthread.
    if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) != 0) {
        std::cerr << "Warning: Could not set CPU affinity to core " << core_to_pin << std::endl;
        perror("pthread_setaffinity_np");
    } else {
        std::cout << "Successfully pinned process to core " << core_to_pin << std::endl;
    }

    // ... Test L1 Hit Latency ...
    long long dummy_sum_l1 = 0;
    const int REPEAT_L1 = 10000;
    auto start_l1 = std::chrono::high_resolution_clock::now();
    for (int r = 0; r < REPEAT_L1; ++r) {
        for (size_t i = 0; i < TEST_SIZE_L1_HIT; ++i) {
            dummy_sum_l1 += data_l1[i];
        }
    }
    auto end_l1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> duration_l1 = end_l1 - start_l1;
    std::cout << "L1 Hit Latency (per long long): " << duration_l1.count() / (TEST_SIZE_L1_HIT * REPEAT_L1) << " ns" << std::endl;

    // Repeat for L2, L3, RAM tests
    long long dummy_sum_l2 = 0;
    const size_t L1_STRIDE_ELEMENTS = CACHE_LINE_SIZE / sizeof(long long);
    const int REPEAT_L2 = 1000;
    auto start_l2 = std::chrono::high_resolution_clock::now();
    for (int r = 0; r < REPEAT_L2; ++r) {
        for (size_t i = 0; i < TEST_SIZE_L2_HIT; i += L1_STRIDE_ELEMENTS) {
            dummy_sum_l2 += data_l2[i];
        }
    }
    auto end_l2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> duration_l2 = end_l2 - start_l2;
    std::cout << "L2 Hit Latency (per long long, L1 miss): " << duration_l2.count() / (TEST_SIZE_L2_HIT / L1_STRIDE_ELEMENTS * REPEAT_L2) << " ns" << std::endl;

    long long dummy_sum_l3 = 0;
    const size_t L2_STRIDE_ELEMENTS = (L2_SIZE_BYTES + CACHE_LINE_SIZE) / sizeof(long long);
    const int REPEAT_L3 = 100;
    auto start_l3 = std::chrono::high_resolution_clock::now();
    for (int r = 0; r < REPEAT_L3; ++r) {
        for (size_t i = 0; i < TEST_SIZE_L3_HIT; i += L2_STRIDE_ELEMENTS) {
            dummy_sum_l3 += data_l3[i];
        }
    }
    auto end_l3 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> duration_l3 = end_l3 - start_l3;
    std::cout << "L3 Hit Latency (per long long, L2 miss): " << duration_l3.count() / (TEST_SIZE_L3_HIT / L2_STRIDE_ELEMENTS * REPEAT_L3) << " ns" << std::endl;

    long long dummy_sum_ram = 0;
    const size_t L3_STRIDE_ELEMENTS = (L3_SIZE_BYTES + CACHE_LINE_SIZE) / sizeof(long long);
    const int REPEAT_RAM = 10;
    auto start_ram = std::chrono::high_resolution_clock::now();
    for (int r = 0; r < REPEAT_RAM; ++r) {
        for (size_t i = 0; i < TEST_SIZE_RAM; i += L3_STRIDE_ELEMENTS) {
            dummy_sum_ram += data_ram[i];
        }
    }
    auto end_ram = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> duration_ram = end_ram - start_ram;
    std::cout << "RAM Latency (per long long, L3 miss): " << duration_ram.count() / (TEST_SIZE_RAM / L3_STRIDE_ELEMENTS * REPEAT_RAM) << " ns" << std::endl;

    return 0;
}