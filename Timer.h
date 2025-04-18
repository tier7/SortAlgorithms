#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer {
public:
    void start() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    double end() {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
        return duration / 1000.0;
    }

private:
    std::chrono::high_resolution_clock::time_point start_time;
};

#endif // TIMER_H
