#ifndef EXECUTEMACRO_H
#define EXECUTEMACRO_H
#include "BoxInfo.h"
#include "OperationFormat.h"

void loop(bool loopCondition, ByteCode &byteCode, Loop &loopList, OperationFormat *programCounter)
{
	if (loopCondition)
	{
		if (loopList.first() != programCounter)
			loopList.push(programCounter);

		return;
	}

	byteCode.jump(programCounter->constant);

	if (loopList.first() == programCounter)
		loopList.pop();
}

void branch(bool branchCondition, ByteCode &byteCode, Size offset)
{
	if (!branchCondition)
		byteCode.jump(offset);
}
#endif // EXECUTEMACRO_H
