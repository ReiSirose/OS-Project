#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>
#include <numeric>
#include <iomanip>
#include <boost/circular_buffer.hpp>
#include <boost/lockfree/spsc_queue.hpp>

constexpr size_t CAPACITY = 1024;
constexpr int TOTAL_ITEMS = 10'000'000;
constexpr int NUM_RUNS = 10;

class MutexRingBuffer {
    boost::circular_buffer<int> buf_{CAPACITY};
    std::mutex mtx_;
public:
    bool push(int val) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (buf_.full()) return false;
        buf_.push_back(val);
        return true;
    }

    bool pop(int& val) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (buf_.empty()) return false;
        val = buf_.front();
        buf_.pop_front();
        return true;
    }
};

double run_mutex_once() {
    MutexRingBuffer queue;
    auto start = std::chrono::high_resolution_clock::now();

    std::thread producer([&]() {
        for (int i = 0; i < TOTAL_ITEMS; ++i) {
            while (!queue.push(i)) { std::this_thread::yield(); }
        }
    });

    std::thread consumer([&]() {
        int val = 0;
        for (int i = 0; i < TOTAL_ITEMS; ++i) {
            while (!queue.pop(val)) { std::this_thread::yield(); }
        }
    });

    producer.join();
    consumer.join();

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}


double run_lockfree_once() {
    boost::lockfree::spsc_queue<int, boost::lockfree::capacity<CAPACITY>> queue;
    auto start = std::chrono::high_resolution_clock::now();

    std::thread producer([&]() {
        for (int i = 0; i < TOTAL_ITEMS; ++i) {
            while (!queue.push(i)) {std::this_thread::yield(); }
        }
    });

    std::thread consumer([&]() {
        int val = 0;
        for (int i = 0; i < TOTAL_ITEMS; ++i) {
            while (!queue.pop(val)) {std::this_thread::yield(); }
        }
    });

    producer.join();
    consumer.join();

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}

int main () {
    std::cout << std::fixed << std::setprecision(2);
    
    std::vector<double> mutex_times;
    std::vector<double> lockfree_times;
    mutex_times.reserve(NUM_RUNS);
    lockfree_times.reserve(NUM_RUNS);

    std::cout << "--- Testing Mutex Ring Buffer (" << NUM_RUNS << " runs) ---\n";
    for (int i = 0; i < NUM_RUNS; ++i) {
        double elapsed = run_mutex_once();
        mutex_times.push_back(elapsed);
        std::cout << "Run " << (i + 1) << ": " << elapsed << " ms\n";
    }

    std::cout << "\n--- Testing Lock-Free SPSC Queue (" << NUM_RUNS << " runs) ---\n";
    for (int i = 0; i < NUM_RUNS; ++i) {
        double elapsed = run_lockfree_once();
        lockfree_times.push_back(elapsed);
        std::cout << "Run " << (i + 1) << ": " << elapsed << " ms\n";
    }

    // Calculating averages using std::accumulate
    double mutex_avg = std::accumulate(mutex_times.begin(), mutex_times.end(), 0.0) / NUM_RUNS;
    double lockfree_avg = std::accumulate(lockfree_times.begin(), lockfree_times.end(), 0.0) / NUM_RUNS;

    std::cout << "\n================ Benchmark Results ================\n";
    std::cout << "Average Mutex Runtime    : " << mutex_avg << " ms\n";
    std::cout << "Average Lock-Free Runtime: " << lockfree_avg << " ms\n";
    std::cout << "Average Speedup Factor   : " << (mutex_avg / lockfree_avg) << "x faster\n";
    std::cout << "===================================================\n";
}