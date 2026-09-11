#include <iostream>
#include <vector>
#include <new>
#include <chrono>

auto MeasureL1CacheLatency(){
    using byte = uint8_t;
    constexpr auto CacheLineSize = std::hardware_destructive_interference_size;
    constexpr auto EvictCacheLineSize = CacheLineSize * (2 << 12);
    constexpr auto Trial = 20'000;
    std::vector<byte>CacheLineData (CacheLineSize), CacheLineEvictedData(EvictCacheLineSize);
    volatile uint64_t sink {0}; 

    using namespace std::chrono;
    auto floodTime {0.0};

    const auto startTrialing = steady_clock::now();


    for(auto trials {0uz}; trials < Trial; trials++){
        auto floodStart = steady_clock::now();

        for(auto i {0uz}; i < CacheLineEvictedData.size(); i+= CacheLineSize){
            sink += CacheLineEvictedData[i];
        }
        auto floodEnd = steady_clock::now();
        const auto iterationFloodTime = duration_cast<nanoseconds>(floodEnd - floodStart).count();
        floodTime += static_cast<double>(iterationFloodTime);

        sink += CacheLineData[0];
    }

    const auto endTrialing = steady_clock::now();

    const auto totalTrialTime = duration_cast<nanoseconds>(endTrialing- startTrialing).count();
    const auto totalTrial = static_cast<double>(totalTrialTime);
    const auto totalReadLatency = totalTrial - floodTime;

    return totalReadLatency / Trial;
}

int main () {
    std::cout << MeasureL1CacheLatency() << std::endl;
    return 0;
}