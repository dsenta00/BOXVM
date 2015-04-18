#ifndef BOXVM_H
#define BOXVM_H
#include "BoxInfo.h"
#include "BoxProgram.h"
#include "CPUTime.h"
#include "WriteLogFileReport.h"

CPUTime startTime;
CPUTime invokingProgramTime;
CPUTime settingStackData;
CPUTime settingPool;
CPUTime settingHeapData;
CPUTime executingProgram;

Status RunProgram(char *_execpath)
{
	Status status = EVERYTHING_OK;
	BoxProgram program;

	srand((unsigned)time(NULL));

	status = program.ReadSourceCode(_execpath);

	if (!status)
	{
		status = program.SetStack();

		if (!status)
		{
			status = program.SetPool();

			if (!status)
			{
				status = program.SetHeap();

				if (!status)
				{
                    status = program.ExecuteProgram();
				}
			}
		}
	}

	return status;
}

Status RunProgramPercentage(char *_execpath)
{
    Status status = EVERYTHING_OK;
    double fulltime = 0;

    startTime.Start();
    BoxProgram program;
    srand((unsigned)time(NULL));
    startTime.Stop();

    invokingProgramTime.Start();
    status = program.ReadSourceCode(_execpath);
    invokingProgramTime.Stop();

    if (!status)
    {
        settingStackData.Start();
        status = program.SetStack();
        settingStackData.Stop();

        if (!status)
        {
            settingPool.Start();
            status = program.SetPool();
            settingPool.Stop();

            if (!status)
            {
                settingHeapData.Start();
                status = program.SetHeap();
                settingHeapData.Stop();

                if (!status)
                {
                    executingProgram.Start();
                    status = program.ExecuteProgram();
                    executingProgram.Stop();
                }
            }
        }
    }

    fulltime = startTime.GetCPU() + invokingProgramTime.GetCPU() + settingStackData.GetCPU() \
                + settingPool.GetCPU() + settingHeapData.GetCPU() + executingProgram.GetCPU();

    std::cout << "\n\tVirtual machines setting data:\t" << startTime.GetCPUTime();
    std::cout << "\t" << startTime.GetCPU() / fulltime * 100 << " %";
    std::cout << "\n\tInvoking program:\t\t" << invokingProgramTime.GetCPUTime();
    std::cout << "\t" << invokingProgramTime.GetCPU() / fulltime * 100 << " %";
    std::cout << "\n\tSetting stack data:\t\t" << settingStackData.GetCPUTime();
    std::cout << "\t" << settingStackData.GetCPU() / fulltime * 100 << " %";
    std::cout << "\n\tInitializing memory pool:\t" << settingPool.GetCPUTime();
    std::cout << "\t" << settingPool.GetCPU() / fulltime * 100 << " %";
    std::cout << "\n\tSetting heap data:\t\t" << settingHeapData.GetCPUTime();
    std::cout << "\t" << settingHeapData.GetCPU() / fulltime * 100 << " %";
    std::cout << "\n\tProgram executing:\t\t" << executingProgram.GetCPUTime();
    std::cout << "\t" << executingProgram.GetCPU() / fulltime * 100 << " %\n";

    return status;
}

#endif
