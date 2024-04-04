#pragma once
#include <iostream>
#include <chrono>
#include <random>


namespace lowlevelsys {
    uint64_t generate_unique_id() {
      
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = now.time_since_epoch();
        auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();

     
        std::random_device rd;
        std::mt19937_64 gen(rd());
        std::uniform_int_distribution<uint64_t> dis(0, std::numeric_limits<uint64_t>::max());
        uint64_t random_number = dis(gen);

      
        uint64_t unique_id = (nanoseconds << 32) | random_number;

        return unique_id;
    }
}


