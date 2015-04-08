#ifndef CPUTIME_H
#define CPUTIME_H
#include "BoxInfo.h"

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
        	return (double)(stop - start)/CLOCKS_PER_SEC;
	}
private:
    double start;
    double stop;
};
#endif
