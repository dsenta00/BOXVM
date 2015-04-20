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
    heap = NULL;
    monitor = NULL;
}

BoxProgram::BoxProgram(ProgramMonitor *_monitor)
{
    heap = NULL;
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
	short shortID = 0;
	char buffer[MAXBUFFERWORD] = { 0 };

    stack.SetMonitor(monitor);
    boxfile.GetNextWord(&shortID);

	if (shortID == ID_STACK)
	{
        boxfile.GetNextWord(&intID);
		stack.SetVirtualMemory(intID);
        boxfile.GetNextWord(&shortID);

		if (shortID != ID_DATA)
            SETERR(UNDEF_DATA_ERR);
	}
	else
        SETERR(UNDEF_STACK_ERR);

    if (EOK)
	{
		do
		{
            boxfile.GetNextWord(&shortID);

			if (shortID == ID_POOL)
				break;

			switch (shortID)
			{
				case ID_STRING:
				    datatype = _STRING;
				break;
				case ID_CHAR:
				    datatype = _CHAR;
				break;
				case ID_INT:
				    datatype = _INT;
				break;
				case ID_SHORT:
				    datatype = _SHORT;
				break;
				case ID_LONG:
				    datatype = _LONG;
				break;
				case ID_DOUBLE:
				    datatype = _DOUBLE;
				break;
				case ID_FLOAT:
				    datatype = _FLOAT;
				break;
				default:
				    datatype = 0;
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

            if (EOK)
                stack.PushStack(datatype, buffer);

        }while (EOK);
    }
}

void BoxProgram::SetPool()
{
	int intID = 0;

    boxfile.GetNextWord(&intID);

	if (intID)
	{
        heap = new Heap(intID, monitor);

        if (!heap)
            SETERR(HEAPERR);
    }
}

void BoxProgram::SetHeap()
{
	short shortID = 0;

    boxfile.GetNextWord(&shortID); //reads @h
    boxfile.GetNextWord(&shortID);

	if (shortID != ID_CODE)
	{
		do
		{
			switch (shortID)
			{
                case ID_CHAR:
                    heap->PushPointer(_CHAR);
                break;
                case ID_INT:
                    heap->PushPointer(_INT);
                break;
                case ID_SHORT:
                    heap->PushPointer(_SHORT);
                break;
                case ID_LONG:
                    heap->PushPointer(_LONG);
                break;
                case ID_DOUBLE:
                    heap->PushPointer(_DOUBLE);
                break;
                case ID_FLOAT:
                    heap->PushPointer(_FLOAT);
                break;
                default:
                    SETERR(DYN_TYPE_ERR);
                break;
			}

            boxfile.GetNextWord(&shortID);

			if (shortID == ID_CODE)
				break;

        } while (EOK);
	}
    else if (shortID == ID_CODE)
    {
        return;
    }
	else
    {
        SETERR(DATA_HEAP_ERR);
    }
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
		delete heap;

    heap = NULL;
}

#endif	//BOXPROGRAM_H
