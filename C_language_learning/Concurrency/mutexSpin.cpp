#include <iostream>
#include <atomic>
#include <mutex>
#include <thread>
#include <chrono>

// SpinLock implementation
class SpinLock {
private:
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
public:
    void lock() {
        while (flag.test_and_set(std::memory_order_acquire)) {
            // optional: std::this_thread::yield();
        }
    }
    void unlock() {
        flag.clear(std::memory_order_release);
    }
};

// Shared variables
const int N = 1'000'000;

int counter1 = 0;
int counter2 = 0;

SpinLock spin;
std::mutex mtx;

void increment_spinlock() {
    for (int i = 0; i < N; ++i) {
        spin.lock();
        ++counter1;
        spin.unlock();
    }
}

void increment_mutex() {
    for (int i = 0; i < N; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        ++counter2;
    }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    std::thread t1(increment_spinlock);
    std::thread t2(increment_spinlock);
    t1.join();
    t2.join();

    auto mid = std::chrono::high_resolution_clock::now();

    std::thread t3(increment_mutex);
    std::thread t4(increment_mutex);
    t3.join();
    t4.join();

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> spin_time = mid - start;
    std::chrono::duration<double> mutex_time = end - mid;

    std::cout << "SpinLock counter: " << counter1 << ", Time: " << spin_time.count() << "s\n";
    std::cout << "Mutex counter: "   << counter2 << ", Time: " << mutex_time.count() << "s\n";

    return 0;
}
