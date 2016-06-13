#ifndef BOXVM_H
#define BOXVM_H
#include "BoxInfo.h"
#include "Data.h"
#include "ProgramMonitor.h"
#include "BoxProgram.h"
#include "CPUTime.h"
#include "BoxTrace.h"

void runBox(int argc, char *argv[])
{
    BoxProgram program;
    srand((unsigned)time(null));

#ifdef DEBUGmode
    boxTrace.open(argv[1]);
#endif

    programMonitor.setLogPath(argv[1]);
    program.invoke(argv[1]);

    if (EOK)
        program.initStack();

    if (EOK)
        program.initHeap();

    if (EOK)
        program.initInstructions();

    if (EOK)
    {
        for (int i = 2; i < argc; i++)
        {
            Data arg(BOX_STRING);
            arg.setVal(argv[i]);
            program.addArgument(&arg);
        }
    }

    if (EOK)
        program.execute();
}

void runBoxPartByPart(int argc, char *argv[])
{
    double fulltime = 0;
    CPUTime startTime;
    CPUTime invokeTime;
    CPUTime initStackTime;
    CPUTime initHeapTime;
    CPUTime addArgumentTime;
    CPUTime initInstructionsTime;
    CPUTime executeTime;

    srand((unsigned)time(null));

#ifdef DEBUGmode
    boxTrace.open(boxPath);
#endif

    startTime.start();
    BoxProgram program;
    programMonitor.setLogPath(argv[1]);
    startTime.stop();

    invokeTime.start();
    program.invoke(argv[1]);
    invokeTime.stop();

    if (EOK)
    {
        initStackTime.start();
        program.initStack();
        initStackTime.stop();
    }

    if (EOK)
    {
        initHeapTime.start();
        program.initHeap();
        initHeapTime.stop();
    }

    if (EOK)
    {
        addArgumentTime.start();

        for (int i = 2; i < argc; i++)
        {
            Data arg(BOX_STRING);
            arg.setVal(argv[i]);
            program.addArgument(&arg);
        }

        addArgumentTime.stop();
    }

    if (EOK)
    {
        initInstructionsTime.start();
        program.initInstructions();
        initInstructionsTime.stop();
    }

    if (EOK)
    {
        executeTime.start();
        program.execute();
        executeTime.stop();
    }

    if (EOK)
    {
        fulltime = startTime.getCpuTicks()
            + invokeTime.getCpuTicks()
            + initStackTime.getCpuTicks()
            + initHeapTime.getCpuTicks()
            + addArgumentTime.getCpuTicks()
            + initInstructionsTime.getCpuTicks()
            + executeTime.getCpuTicks();

        std::cout << "\n Create BOX program: ..... " << startTime.getCpuTicks() / fulltime * 100 << " %";
        std::cout << "\n Invoke BOX file: ........ " << invokeTime.getCpuTicks() / fulltime * 100 << " %";
        std::cout << "\n Init stack: ............. " << initStackTime.getCpuTicks() / fulltime * 100 << " %";
        std::cout << "\n Init heap: .............. " << initHeapTime.getCpuTicks() / fulltime * 100 << " %";
        std::cout << "\n Add argument time: ...... " << addArgumentTime.getCpuTicks() / fulltime * 100 << " %";
        std::cout << "\n Init instructions: ...... " << initInstructionsTime.getCpuTicks() / fulltime * 100 << " %";
        std::cout << "\n Execute program: ........ " << executeTime.getCpuTicks() / fulltime * 100 << " %\n";
    }
}

#endif
