#ifndef TESTBOX_H
#define TESTBOX_H
#include "BOXVM.h"
#include "CPUTime.h"
#include "BoxInfo.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <conio.h>
#endif

inline void BoxSleep()
{
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        Sleep(1000);
    #else
        sleep(1);
    #endif
}

void NativeC()
{
    double pi = 0;
    const double constant = 4;
    double i = 1, limit = 100000;

    while(i < limit)
    {
        pi += constant/i;
        i += 2;
        pi -= constant/i;
        i += 2;
    }
}

void Testing()
{
    char testpath[MAXPATHSIZE] = "/home/duje/BOXVM 0.5/BOXVM/ajde.box";
    CPUTime testspeed;
    double BOX_time = 0, C_time = 0, C_val = 0, BOX_val = 0;

    printf("\n\t\t[ Running test program ]\n");

    BoxSleep();

    RunProgramPercentage(testpath);

    testspeed.Start();
    RunProgram(testpath);
    testspeed.Stop();

    BOX_time = testspeed.GetCPUTime();
    BOX_val = testspeed.GetCPU();

    testspeed.Start();
    NativeC();
    testspeed.Stop();

    C_time = testspeed.GetCPUTime();
    C_val = testspeed.GetCPU();

    std::cout.precision(15);
    std::cout << "\n\tBOX program executing time:\t" << BOX_time << " ms";
    std::cout << "\n\tC program executing time:\t" << C_time << " ms";
    std::cout << "\n\t<BOX:C>:\t\t\t" << BOX_val / C_val << "\n\n";
}

#endif
