#ifndef EXECUTE_H
#define EXECUTE_H
#include "BoxInfo.h"
#include "Stack.h"
#include "Heap.h"
#include "FileList.h"
#include "OperationFormat.h"
#include "BoxInstructionSet.h"

void makeInstrunctionSet(BoxInstructionSet &boxInstructionSet, Bcode &byteCode, Heap &heap, Stack &stack)
{
	OperationFormat *programCounter = (OperationFormat *)byteCode;

	do
	{
		programCounter++;
		boxInstructionSet.add(programCounter, heap, stack);
	} while (programCounter->opCode != ESTART);
}

void performProgram(Stack &stack, Heap &heap, Bcode cs)
{
	BoxInstructionSet boxInstructionSet;
	makeInstrunctionSet(boxInstructionSet, cs, heap, stack);
	boxInstructionSet.execute(heap);
}

#endif
