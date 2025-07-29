
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <mutex>
#include <stdexcept>

// Enum for process states (OSTEP Chapter 13)
enum class ProcessState { READY, RUNNING, BLOCKED, TERMINATED };

// Process class: Represents a process with PCB (OSTEP Chapter 13)
class Process {
public:
    int pid;                    // Unique process ID
    ProcessState state;         // Current state
    int burst_time;             // Total CPU time needed (ms)
    int remaining_time;         // Remaining CPU time
    uint32_t pc;                // Program counter (simulated)
    uint32_t base, bound;       // Base/bound registers (Chapter 16)
    int arrival_time;           // Time process enters system
    int completion_time;        // Time process finishes
    int waiting_time;           // Time spent in ready queue

    // Constructor: Initialize with PID and random burst time
    Process(int id, int burst, int arrival)
        : pid(id), state(ProcessState::READY), burst_time(burst),
          remaining_time(burst), pc(0), base(0), bound(2048), // Example: 2 KB bound
          arrival_time(arrival), completion_time(0), waiting_time(0) {
        // Set random base address (e.g., 28,672 for stack-like segment)
        base = 16384 + (rand() % 16384); // Random base in 16 KB range
    }

    // Execute process for given time (simulates CPU burst)
    void execute(int time_slice) {
        if (state != ProcessState::RUNNING) throw std::runtime_error("Not running");
        remaining_time -= time_slice;
        pc += time_slice * 10; // Simulate PC increment
        if (remaining_time <= 0) {
            state = ProcessState::TERMINATED;
            remaining_time = 0;
        }
    }

    // Rule of Three: Destructor, copy constructor, assignment operator
    ~Process() = default;
    Process(const Process&) = default;
    Process& operator=(const Process&) = default;
};

// MMU class: Simulates address translation (OSTEP Chapters 15–16)
class MMU {
public:
    // Translate virtual address to physical (simulates segmentation)
    uint32_t translate(const Process& proc, uint16_t virt_addr) {
        // Extract segment ID and offset (e.g., 14-bit address, 2-bit ID)
        uint8_t seg_id = (virt_addr >> 12) & 0x3; // 2-bit segment ID
        uint16_t offset = virt_addr & 0xFFF;      // 12-bit offset
        if (offset >= proc.bound) throw std::runtime_error("Segmentation fault");
        // Simulate downward-growing stack for segment ID 2 (your stack example)
        bool grows_down = (seg_id == 2);
        return grows_down ? proc.base - offset : proc.base + offset;
    }

    // Save process state (context switch)
    void save_state(Process& proc) {
        // Save PC and base/bound (placeholder)
    }

    // Restore process state
    void restore_state(const Process& proc) {
        // Restore PC and base/bound (placeholder)
    }
};

// Scheduler class: Manages process scheduling (OSTEP Chapters 6–7)
class Scheduler {
    std::vector<Process> ready_queue; // Ready processes
    int time_quantum;                 // Round-robin quantum (ms)
    int current_time;                 // Simulation time
    MMU mmu;                          // MMU for address translation
    std::mutex queue_mutex;           // Thread safety

public:
    Scheduler(int quantum) : time_quantum(quantum), current_time(0) {}

    // Add process to ready queue
    void add_process(Process p) {
        std::lock_guard<std::mutex> lock(queue_mutex);
        ready_queue.push_back(p);
    }

    // Run round-robin scheduling
    void run_round_robin() {
        while (!ready_queue.empty()) {
            std::lock_guard<std::mutex> lock(queue_mutex);
            if (ready_queue.empty()) break;

            Process& proc = ready_queue.front();
            ready_queue.erase(ready_queue.begin());

            // Context switch: Restore state
            mmu.restore_state(proc);
            proc.state = ProcessState::RUNNING;

            // Run for quantum or until done
            int run_time = std::min(time_quantum, proc.remaining_time);
            proc.execute(run_time);
            current_time += run_time;

            // Update metrics
            if (proc.state == ProcessState::TERMINATED) {
                proc.completion_time = current_time;
                std::cout << "Process " << proc.pid << " finished at "
                          << current_time << " ms\n";
            } else {
                // Preempt: Save state, back to ready queue
                mmu.save_state(proc);
                proc.state = ProcessState::READY;
                ready_queue.push_back(proc);
            }

            // Simulate waiting time for others
            for (auto& p : ready_queue) {
                if (p.state == ProcessState::READY) {
                    p.waiting_time += run_time;
                }
            }

            // Simulate CPU tick
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    // Print scheduling metrics
    void print_metrics(const std::vector<Process>& processes) {
        double avg_turnaround = 0, avg_waiting = 0;
        for (const auto& p : processes) {
            int turnaround = p.completion_time - p.arrival_time;
            avg_turnaround += turnaround;
            avg_waiting += p.waiting_time;
            std::cout << "Process " << p.pid << ": Turnaround = " << turnaround
                      << " ms, Waiting = " << p.waiting_time << " ms\n";
        }
        avg_turnaround /= processes.size();
        avg_waiting /= processes.size();
        std::cout << "Average Turnaround: " << avg_turnaround << " ms\n";
        std::cout << "Average Waiting: " << avg_waiting << " ms\n";
    }
};

// Main simulation driver
int main() {
    // Seed random number generator
    srand(static_cast<unsigned>(time(nullptr)));

    // Create scheduler with 10 ms quantum
    Scheduler scheduler(10);

    // Create 5 processes with random burst times (10–100 ms)
    std::vector<Process> processes;
    for (int i = 0; i < 5; ++i) {
        int burst = 10 + (rand() % 91); // 10–100 ms
        Process p(i, burst, 0); // Arrival time = 0
        processes.push_back(p);
        scheduler.add_process(p);
    }

    // Run simulation
    std::cout << "Starting simulation...\n";
    scheduler.run_round_robin();

    // Print metrics
    std::cout << "\nSimulation complete.\n";
    scheduler.print_metrics(processes);

    return 0;
}