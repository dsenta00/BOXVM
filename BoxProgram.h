#ifndef BOXPROGRAM_H
#define BOXPROGRAM_H

#include "BoxInfo.h"
#include "ProgramMonitor.h"
#include "DataNode.h"
#include "InvokeBox.h"
#include "Execute.h"

class BoxProgram {
public:
	BoxProgram();
    BoxProgram(ProgramMonitor *);
	~BoxProgram();
    void ReadSourceCode(char *);
    void SetStack();
    void SetPool();
    void SetHeap();
    void ExecuteProgram();
protected:
    InvokeBox boxfile;
    Stack stack;
    Heap *heap;
    ProgramMonitor *monitor;
};

BoxProgram::BoxProgram()
{
    heap = null;
    monitor = null;
}

BoxProgram::BoxProgram(ProgramMonitor *_monitor)
{
    heap = null;
    monitor = _monitor;
}

void BoxProgram::ReadSourceCode(char *_filepath)
{
    boxfile.ReadAll(_filepath, monitor);
}

void BoxProgram::SetStack()
{
	Type datatype = 0;
    int intID = 0, i = 0;
	char buffer[MAXBUFFERWORD] = { 0 };

    stack.SetMonitor(monitor);

    boxfile.GetNextWord(&intID);
    stack.SetVirtualMemory(intID);

    if (EOK)
    {
        do
        {
            boxfile.GetNextWord(&datatype);

            if (datatype == '@')
            {
                break;
            }
            else if(datatype > 6 || datatype < 0)
            {
                SETERR(STAT_TYPE_ERR);
                break;
            }

            switch (datatype)
            {
                case _CHAR:
                    boxfile.GetNextWord(&buffer[0]);
                break;
                case _INT: case _FLOAT:
                    boxfile.GetNextWord(&buffer[0]);
                    boxfile.GetNextWord(&buffer[1]);
                    boxfile.GetNextWord(&buffer[2]);
                    boxfile.GetNextWord(&buffer[3]);
                break;
                case _LONG: case _DOUBLE:
                    boxfile.GetNextWord(&buffer[0]);
                    boxfile.GetNextWord(&buffer[1]);
                    boxfile.GetNextWord(&buffer[2]);
                    boxfile.GetNextWord(&buffer[3]);
                    boxfile.GetNextWord(&buffer[4]);
                    boxfile.GetNextWord(&buffer[5]);
                    boxfile.GetNextWord(&buffer[6]);
                    boxfile.GetNextWord(&buffer[7]);
                break;
                case _SHORT:
                    boxfile.GetNextWord(&buffer[0]);
                    boxfile.GetNextWord(&buffer[1]);
                break;
                case _STRING:
                    i = 0;

                    boxfile.GetNextWord(&buffer[i]);
                    while (buffer[i]) 	// 0 is end of string
                        boxfile.GetNextWord(&buffer[++i]);

                    buffer[i] = '\0';
                break;
            }

            stack.PushStack(datatype, buffer);

        }while(EOK);
    }
}

void BoxProgram::SetPool()
{
	int intID = 0;

    boxfile.GetNextWord(&intID);

	if (intID)
	{
        heap = new Heap(intID, monitor);
    }
}

void BoxProgram::SetHeap()
{
    Type datatype = 0;

    do
    {
        boxfile.GetNextWord(&datatype);

        if(datatype >= _CHAR && datatype <= _STRING)
        {
            heap->PushPointer(datatype);
        }
        else if(datatype == START)
        {
            break;
        }
        else
        {
            SETERR(DYN_TYPE_ERR);
            break;
        }
    } while (EOK);
}

void BoxProgram::ExecuteProgram()
{
    Execute processor (
        boxfile.GetCodeSegment(),
        boxfile.GetExecuteCode(),
        monitor
    );

    if (EOK)
	{
        processor.Do(stack, *heap);
    }
}

BoxProgram::~BoxProgram()
{
	if(heap)
    {
        delete heap;
    }
}

#endif	//BOXPROGRAM_H
