#ifndef CPUTIME_H
#define CPUTIME_H
#include "BoxInfo.h"

class CPUTime {
public:
    CPUTime();
    void start();
    void stop();
    double getCpuTime();
    double getCpuTicks();
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

void CPUTime::start()
{
    start = clock();
}

void CPUTime::stop()
{
    stop = clock();
}

double CPUTime::getCpuTime()
{
    return (double)(stop - start) * 1000 / CLOCKS_PER_SEC;
}

double CPUTime::getCpuTicks()
{
    return stop - start;
}
#else

CPUTime::CPUTime()
{
    QueryPerformanceFrequency(&freq);
    secs = 0;
}

void CPUTime::start()
{
    QueryPerformanceCounter(&t1);
}

void CPUTime::stop()
{
    QueryPerformanceCounter(&t2);
    secs = (double)(t2.QuadPart - t1.QuadPart) * 1000 / (double)freq.QuadPart;
}

double CPUTime::getCpuTicks()
{
    return (double)(t2.QuadPart - t1.QuadPart);
}

double CPUTime::getCpuTime()
{
    return secs;
}
#endif
#endif
