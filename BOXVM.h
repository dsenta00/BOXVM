#ifndef BOXVM_H
#define BOXVM_H
#include "BoxInfo.h"
#include "BoxProgram.h"
#include "WriteLogFileReport.h"

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

#endif
