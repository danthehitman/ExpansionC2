#pragma once

#include <Windows.h>

namespace ec2{

    class Timer
    {
    private:
        LARGE_INTEGER _start;
        double _frequency;
    public:
        Timer()
        {
            LARGE_INTEGER frequency;
            QueryPerformanceFrequency(&frequency);
            _frequency = 1.0 / frequency.QuadPart;
            QueryPerformanceCounter(&_start);
        }

        void reset()
        {
            QueryPerformanceCounter(&_start);
        }

        float elapsed()
        {
            LARGE_INTEGER current;
            QueryPerformanceCounter(&current);
            unsigned _int64 cycles = current.QuadPart - _start.QuadPart;
            return (float)(cycles * _frequency);
        }
    };

}
