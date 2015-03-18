#ifndef TESTBOX_H
#define TESTBOX_H
#include "BOXVM.h"
#include "CPUTime.h"
#include "BoxInfo.h"

Status NativeC();
Status Testing();

Status Testing()
{
    Status status = 0;
	char testpath[MAXPATHSIZE] = "/home/duje/Desktop/BOX-UBUNTU-64/TRANSLATOR-AND-LINKER-UBUNTU-64/ajde.box";
	CPUTime obj;
	double BOX_time = 0, C_time = 0;

	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
		Sleep(1000);
	#else
		sleep(1);
	#endif

	obj.Start();
	status = RunProgram(testpath);
	obj.Stop();

	BOX_time = obj.GetCPUTime();

	if (status < 0)
		WriteLogErrorReport(testpath, status);
	else
	{
		obj.Start();
		NativeC();
		obj.Stop();

		C_time = obj.GetCPUTime();

		printf("\n\tVrijeme izvrsavanja BOX programa je:\t%lf", BOX_time);
		printf("\n\tVrijeme izvrsavanja C programa je:\t%lf", C_time);
		printf("\n\tSveukupni omjer brzina <BOX:C>:\t\t%lf\n\n", BOX_time / C_time);
	}
	
	return status;
}

Status NativeC()
{
    Status status = 0;
	FILE *fp = NULL;
	int i = 0;
    int limit = 100000;

	fp = fopen("test2.txt", "w+");

	if (fp != NULL)
	{
		while (i < limit)
		{
            printf("%d", i);
            fprintf(fp, "%d", i);
			i++;
		}

		fclose(fp);
	}
	else
		status = -1;

	return status;
}

#endif
