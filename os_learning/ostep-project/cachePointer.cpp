#define _GNU_SOURCE 
#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>
#include <algorithm>
#include <random> 
#include <sched.h>   
#include <pthread.h>  
#include <unistd.h>   
#include <thread>

const size_t CACHE_LINE_SIZE = 64; // Common for x86 CPUs
const size_t INT_SIZE_BYTES = sizeof(int);
// Helper function to prevent compiler optimizations
void consume_value(volatile int& val) {
    // This function does nothing, but ensures 'val' is used
    // and prevents compiler from optimizing away the access
}

// Function to fill array with shuffled indices for pointer chasing
void fill_random_indices(std::vector<int>& arr) {
    std::iota(arr.begin(), arr.end(), 0);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(arr.begin(), arr.end(), g);
}

// Function to flush caches between tests (best effort, not guaranteed)
void flush_caches(size_t ram_size_bytes) {
    std::vector<char> large_array(ram_size_bytes, 0); // Initialize to ensure pages are allocated

    for (size_t i = 0; i < large_array.size(); i += CACHE_LINE_SIZE) {
        large_array[i] = (char)(i % 256);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}


int main() {
    // --- CPU Pinning ---
    const int core_to_pin = 0;
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_to_pin, &cpuset);

    if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) != 0) {
        std::cerr << "Warning: Could not set CPU affinity to core " << core_to_pin << std::endl;
        perror("pthread_setaffinity_np");
    } else {
        std::cout << "Successfully pinned process to core " << core_to_pin << std::endl;
    }

    // --- Cache Size Estimates
    const size_t L1_D_CACHE_SIZE_BYTES = 32 * 1024;  // L1 Data Cache
    const size_t L2_CACHE_SIZE_BYTES   = 256 * 1024; // L2 Unified Cache (per core)
    const size_t L3_CACHE_SIZE_BYTES   = 6 * 1024 * 1024; // L3 Shared Cache (for i7-8550U)


    // --- Test Parameters ---
    const long long NUM_ACCESSES_L1  = 50000000;
    const long long NUM_ACCESSES_L2  = 20000000;
    const long long NUM_ACCESSES_L3  = 5000000;
    const long long NUM_ACCESSES_RAM = 1000000;  

    // Array sizes for pointer chasing. Elements are 'int' (4 bytes).
    // Ensure array is slightly *smaller* than the cache level to guarantee hits.
    // Use prime numbers or sizes that are not powers of 2 for better cache distribution
    // within sets if associativity is a concern.
    const size_t L1_ARRAY_ELEMENTS = (L1_D_CACHE_SIZE_BYTES / INT_SIZE_BYTES) * 0.8; // ~80% of L1
    const size_t L2_ARRAY_ELEMENTS = (L2_CACHE_SIZE_BYTES / INT_SIZE_BYTES) * 0.8;   // ~80% of L2
    const size_t L3_ARRAY_ELEMENTS = (L3_CACHE_SIZE_BYTES / INT_SIZE_BYTES) * 0.8;   // ~80% of L3
    const size_t RAM_ARRAY_ELEMENTS = (L3_CACHE_SIZE_BYTES * 2 / INT_SIZE_BYTES);   // Larger than L3

    // Vectors to hold the "pointer chasing" indices
    std::vector<int> data_l1(L1_ARRAY_ELEMENTS);
    std::vector<int> data_l2(L2_ARRAY_ELEMENTS);
    std::vector<int> data_l3(L3_ARRAY_ELEMENTS);
    std::vector<int> data_ram(RAM_ARRAY_ELEMENTS);

    
    fill_random_indices(data_l1);
    fill_random_indices(data_l2);
    fill_random_indices(data_l3);
    fill_random_indices(data_ram);

    int current_index = 0; 

    // --- Run Tests ---
    const double BYTES_TO_GB = 1.0 / (1024.0 * 1024.0 * 1024.0);

    // 1. L1 Hit Latency & Throughput
    flush_caches(L3_CACHE_SIZE_BYTES * 2);
    current_index = 0;
    auto start_l1 = std::chrono::high_resolution_clock::now();

    for (long long i = 0; i < NUM_ACCESSES_L1; ++i) {
        current_index = data_l1[current_index % L1_ARRAY_ELEMENTS]; // Use modulo for safety/wrap-around
    }

    auto end_l1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> duration_l1 = end_l1 - start_l1;
    double l1_latency_ns = duration_l1.count() / NUM_ACCESSES_L1;
    // ns to s, then convert bytes to GB
    double l1_throughput_gbps = (NUM_ACCESSES_L1 * INT_SIZE_BYTES) / duration_l1.count() * 1000.0;
    std::cout << "L1 Hit Latency (per int, pointer chase): " << l1_latency_ns << " ns" << std::endl;
    std::cout << "L1 Throughput: " << l1_throughput_gbps << " GB/s" << std::endl;
    consume_value(current_index);

    // 2. L2 Hit Latency & Throughput
    flush_caches(L3_CACHE_SIZE_BYTES * 2);
    current_index = 0;
    auto start_l2 = std::chrono::high_resolution_clock::now();

    for (long long i = 0; i < NUM_ACCESSES_L2; ++i) {
        current_index = data_l2[current_index % L2_ARRAY_ELEMENTS];
    }

    auto end_l2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> duration_l2 = end_l2 - start_l2;
    double l2_latency_ns = duration_l2.count() / NUM_ACCESSES_L2;
    double l2_throughput_gbps = (NUM_ACCESSES_L2 * INT_SIZE_BYTES) / duration_l2.count() * 1000.0;
    std::cout << "L2 Hit Latency (per int, pointer chase): " << l2_latency_ns << " ns" << std::endl;
    std::cout << "L2 Throughput: " << l2_throughput_gbps << " GB/s" << std::endl;
    consume_value(current_index);

    // 3. L3 Hit Latency & Throughput
    flush_caches(L3_CACHE_SIZE_BYTES * 2);
    current_index = 0;
    auto start_l3 = std::chrono::high_resolution_clock::now();

    for (long long i = 0; i < NUM_ACCESSES_L3; ++i) {
        current_index = data_l3[current_index % L3_ARRAY_ELEMENTS];
    }

    auto end_l3 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> duration_l3 = end_l3 - start_l3;
    double l3_latency_ns = duration_l3.count() / NUM_ACCESSES_L3;
    double l3_throughput_gbps = (NUM_ACCESSES_L3 * INT_SIZE_BYTES) / duration_l3.count() * 1000.0;
    std::cout << "L3 Hit Latency (per int, pointer chase): " << l3_latency_ns << " ns" << std::endl;
    std::cout << "L3 Throughput: " << l3_throughput_gbps << " GB/s" << std::endl;
    consume_value(current_index);

    // 4. RAM Latency & Throughput
    flush_caches(L3_CACHE_SIZE_BYTES * 2);
    current_index = 0;
    auto start_ram = std::chrono::high_resolution_clock::now();

    for (long long i = 0; i < NUM_ACCESSES_RAM; ++i) {
        current_index = data_ram[current_index % RAM_ARRAY_ELEMENTS];
    }

    auto end_ram = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> duration_ram = end_ram - start_ram;
    double ram_latency_ns = duration_ram.count() / NUM_ACCESSES_RAM;
    double ram_throughput_gbps = (NUM_ACCESSES_RAM * INT_SIZE_BYTES) / duration_ram.count() * 1000.0;
    std::cout << "RAM Latency (per int, pointer chase): " << ram_latency_ns << " ns" << std::endl;
    std::cout << "RAM Throughput: " << ram_throughput_gbps << " GB/s" << std::endl;
    consume_value(current_index);

    return 0;
}