#ifndef BOXVM_H
#define BOXVM_H
#include "BoxInfo.h"
#include "ProgramMonitor.h"
#include "BoxProgram.h"
#include "CPUTime.h"

void RunProgram(char *_execpath)
{
    ProgramMonitor monitor;
    BoxProgram program(&monitor);
	srand((unsigned)time(NULL));

    monitor.SetPath(_execpath);
    program.ReadSourceCode(_execpath);

    if (monitor.OK())
    {
        program.SetStack();

        if (monitor.OK())
        {
            program.SetPool();

            if (monitor.OK())
            {
                program.SetHeap();

                if (monitor.OK())
                {
                    program.ExecuteProgram();
                }
            }
        }
    }
}

void RunProgramPercentage(char *_execpath)
{
    double fulltime = 0;
    CPUTime startTime;
    CPUTime invokingProgramTime;
    CPUTime settingStackData;
    CPUTime settingPool;
    CPUTime settingHeapData;
    CPUTime executingProgram;

    startTime.Start();
    ProgramMonitor monitor;
    BoxProgram program(&monitor);
    srand((unsigned)time(NULL));

    monitor.SetPath(_execpath);
    startTime.Stop();

    invokingProgramTime.Start();
    program.ReadSourceCode(_execpath);
    invokingProgramTime.Stop();

    if (monitor.OK())
    {
        settingStackData.Start();
        program.SetStack();
        settingStackData.Stop();

        if (monitor.OK())
        {
            settingPool.Start();
            program.SetPool();
            settingPool.Stop();

            if (monitor.OK())
            {
                settingHeapData.Start();
                program.SetHeap();
                settingHeapData.Stop();

                if (monitor.OK())
                {
                    executingProgram.Start();
                    program.ExecuteProgram();
                    executingProgram.Stop();
                }
            }
        }
    }

    if(monitor.OK())
    {
        fulltime = startTime.GetCPU() + invokingProgramTime.GetCPU() + settingStackData.GetCPU() \
                    + settingPool.GetCPU() + settingHeapData.GetCPU() + executingProgram.GetCPU();

        std::cout << "\n\tVirtual machines setting data:\t" <<  startTime.GetCPU() / fulltime * 100 << " %";
        std::cout << "\n\tInvoking program:\t\t" << invokingProgramTime.GetCPU() / fulltime * 100 << " %";
        std::cout << "\n\tSetting stack data:\t\t" << settingStackData.GetCPU() / fulltime * 100 << " %";
        std::cout << "\n\tInitializing memory pool:\t" << settingPool.GetCPU() / fulltime * 100 << " %";
        std::cout << "\n\tSetting heap data:\t\t" << settingHeapData.GetCPU() / fulltime * 100 << " %";
        std::cout << "\n\tProgram executing:\t\t" << executingProgram.GetCPU() / fulltime * 100 << " %\n";
    }
}

#endif
