#ifndef TESTBOX_H
#define TESTBOX_H
#include "BOXVM.h"
#include "CPUTime.h"
#include "BoxInfo.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <conio.h>
#else
    #include <curses.h>
#endif

inline void ClearScreen()
{
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        system("cls");
    #else
        clear();
    #endif
}

inline void BoxSleep()
{
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        Sleep(1000);
    #else
        sleep(1);
    #endif
}

Status NativeC()
{
    Status status = 0;
    int i = 0, limit = 100000;
    FILE *fp = NULL;

    fp = fopen("TestNativeC.txt", "w+");

    if(fp)
    {
        do
        {
            printf("%d", i);
            fprintf(fp, "%d", i);
            i++;
        }
        while (i < limit);

        fclose(fp);
    }
    else
    {
        status = -1;
        printf("\n\tC program fail.\n");
    }

    return status;
}

Status Testing()
{
    Status status = 0;
    char testpath[MAXPATHSIZE] = "C:\\Users\\Danijela\\Desktop\\BOXVM-master\\ajde.box";
    CPUTime testspeed;
    double BOX_time = 0, C_time = 0, C_val = 0, BOX_val = 0;

    printf("\n\tRunning test program...\n");

    BoxSleep();

    testspeed.Start();
    status = RunProgram(testpath);
    testspeed.Stop();

    BOX_time += testspeed.GetCPUTime();
    BOX_val += testspeed.GetCPU();

    if (status)
    {
        WriteLogErrorReport(testpath, status);
    }
    else
    {
        testspeed.Start();
        NativeC();
        testspeed.Stop();

        C_time += testspeed.GetCPUTime();
        C_val += testspeed.GetCPU();
    }

    ClearScreen();

    if(!status)
    {
        std::cout.precision(15);

        std::cout << "\n\tBOX program executing time:\t" << BOX_time << " ms";
        std::cout << "\n\tC program executing time:\t" << C_time << " ms";
        std::cout << "\n\t<BOX:C>:\t\t\t" << BOX_val / C_val << "\n\n";
    }
	return status;
}
#endif

