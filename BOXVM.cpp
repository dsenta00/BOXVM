/*****************************************************************************************************************
 *	PROGRAM DESCRIPTION
 *
 *	@program	BOX programming language virutal machine
 *	@file		BOXVM.cpp
 *	@purpose	An abstract virtual machine that interprets programs written in an executable .box file format.
 *
 *	@author		Duje Senta 
 *	@company	Faculty of Electrical Engineering, Mechanical Engineering and Naval Architecture, Split
 *	@version	0.3	15/03/2015
 *
 *****************************************************************************************************************/

#include "BOXVM.h"
#include "TestBox.h"

int main(int argc, char *argv[])
{
    Status status = EVERYTHING_OK;

	if (argc == 1)
	{
		printf("\n\tRunning test program...\n");
		status = Testing();
	}
	else
	{
		status = RunProgram(argv[1]);
		if (status < 0)
			WriteLogErrorReport(argv[1], status);
	}

	return status;
}
