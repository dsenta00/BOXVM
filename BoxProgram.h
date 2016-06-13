#ifndef BOXPROGRAM_H
#define BOXPROGRAM_H
#include "BoxInfo.h"
#include "ProgramMonitor.h"
#include "InvokeBox.h"
#include "Execute.h"
#include "OperationFormat.h"
#include "BoxInstruction.h"
#include "BoxInstructionSet.h"
#include "BoxTrace.h"

#define DATA_TYPE_END '@'

class BoxProgram {
public:
    void invoke(char *);
    void initStack();
    void initHeap();
    void addArgument(Data *data);
    void initInstructions();
    void execute();
protected:
    InvokeBox boxfile;
    Stack stack;
    Heap heap;
    BoxInstructionSet boxInstructionSet;
};

void BoxProgram::invoke(char *boxFilePath)
{
    TRACE("BOX_PROGRAM", "invoke(\"%s\")", boxFilePath);
    boxfile.invoke(boxFilePath);
}

void BoxProgram::initStack()
{
    Type datatype = 0;
    char buffer[MAX_BUFFER_WORD] = { 0 };

    TRACE("BOX_PROGRAM", "initStack()");

    while (EOK)
    {
        boxfile.read((Byte *)&datatype, 1);

        if (datatype == DATA_TYPE_END)
            return;

        boxfile.read(buffer, DATA_TYPES_SIZE[datatype]);
        stack.addData(datatype, buffer);
    }
}

void BoxProgram::initHeap()
{
    Type datatype = 0;

    TRACE("BOX_PROGRAM", "initHeap()");

    while (1)
    {
        boxfile.read((Byte *)&datatype, 1);

        if (datatype == START)
            break;

        heap.addPointer(datatype);
    }
}

void BoxProgram::addArgument(Data *data)
{
    stack.addData(data->getType(), data->getAddress());
}

void BoxProgram::execute()
{
    TRACE("BOX_PROGRAM", "execute()");
    boxInstructionSet.execute(heap);
}

void BoxProgram::initInstructions()
{
    OperationFormat *programCounter = (OperationFormat *)boxfile.getPc();

    do
    {
        programCounter++;
        boxInstructionSet.add(programCounter, heap, stack);
    } while (programCounter->opCode != ESTART);
}

#endif	//BOXPROGRAM_H
