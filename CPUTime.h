#ifndef CPUTIME_H
#define CPUTIME_H
#include "BoxInfo.h"

class CPUTime {
public:
    CPUTime();
    inline void Start();
    inline void Stop();
    inline double GetCPUTime();
    inline double GetCPU();
protected:
#if defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
    double start;
    double stop;
#else
    LARGE_INTEGER t1;
    LARGE_INTEGER t2;
    LARGE_INTEGER freq;
    double secs;
#endif
};

#if defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))

    CPUTime::CPUTime()
    {
        start = stop = null;
    }

    inline void CPUTime::Start()
    {
        start = clock();
    }

    inline void CPUTime::Stop()
    {
        stop = clock();
    }

    inline double CPUTime::GetCPUTime()
    {
        return (double)(stop - start) * 1000 / CLOCKS_PER_SEC;
    }

    inline double CPUTime::GetCPU()
    {
        return stop-start;
    }
#else

    CPUTime::CPUTime()
    {
        QueryPerformanceFrequency(&freq);
        secs = 0;
    }

    inline void CPUTime::Start()
    {
        QueryPerformanceCounter(&t1);
    }

    inline void CPUTime::Stop()
    {
        QueryPerformanceCounter(&t2);
        secs = (double)(t2.QuadPart - t1.QuadPart) * 1000 / (double)freq.QuadPart;
    }

    inline double CPUTime::GetCPU()
    {
        return (double)(t2.QuadPart - t1.QuadPart);
    }

    inline double CPUTime::GetCPUTime()
    {
        return secs;
    }
#endif
#endif
