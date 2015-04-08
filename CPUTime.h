#ifndef CPUTIME_H
#define CPUTIME_H
#include "BoxInfo.h"

#if defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
class CPUTime {
public:
	CPUTime()
	{
		start = stop = 0;
	}

	inline void Start()
	{
		start = clock();
	}

	inline void Stop()
	{
		stop = clock();
	}

	double GetCPUTime()
	{
		return (double)(stop - start) * 1000 / CLOCKS_PER_SEC;
	}

	double GetCPU()
	{
		return stop-start;
	}
private:
    double start;
    double stop;
};
#else
#include <iomanip>

class CPUTime {
public:
    CPUTime()
    {
        QueryPerformanceFrequency(&freq);
        secs = 0;
    }

    inline void Start()
    {
        QueryPerformanceCounter(&t1);
    }

    inline void Stop()
    {
        QueryPerformanceCounter(&t2);
        secs = (double)(t2.QuadPart - t1.QuadPart) * 1000 / (double)freq.QuadPart;
    }

    inline double GetCPU()
    {
        return (double)(t2.QuadPart - t1.QuadPart);
    }

    double GetCPUTime()
    {
        return secs;
    }
private:
    LARGE_INTEGER t1;
    LARGE_INTEGER t2;
    LARGE_INTEGER freq;
    double secs;
};
#endif
#endif
