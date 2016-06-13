#ifndef TESTBOX_H
#define TESTBOX_H
#include "BOXVM.h"
#include "CPUTime.h"
#include "BoxInfo.h"

void NativeC()
{
    double pi = 0;
    const double constant = 4;
    double i = 1, limit = 100000;

    while (i < limit)
    {
        pi += constant / i;
        i += 2;
        pi -= constant / i;
        i += 2;
    }
}

void Testing()
{
    int argc = 2;
    char *argv[32] = { "", "D:\\DUJE\\Materijali zavrsni rad\\Programi za testiranje\\Pi\\Pi.box" };
    CPUTime testspeed;
    double BOX_time = 0, C_time = 0, C_val = 0, BOX_val = 0;

    printf("\n\t\t[ Running test program ]\n");

    runBoxPartByPart(argc, argv);

    testspeed.start();
    runBox(argc, argv);
    testspeed.stop();

    BOX_time = testspeed.getCpuTime();
    BOX_val = testspeed.getCpuTicks();

    testspeed.start();
    NativeC();
    testspeed.stop();

    C_time = testspeed.getCpuTime();
    C_val = testspeed.getCpuTicks();

    std::cout.precision(15);
    std::cout << "\n BOX program time: .... " << BOX_time << " ms";
    std::cout << "\n C program time: ...... " << C_time << " ms";
    std::cout << "\n <BOX:C> .............. " << BOX_val / C_val << "\n\n";
}

#endif
