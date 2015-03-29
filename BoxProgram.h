#ifndef BOXPROGRAM_H
#define BOXPROGRAM_H

#include "BoxInfo.h"
#include "Node.h"
#include "InvokeBox.h"
#include "Execute.h"

class BoxProgram
{
    InvokeBox *boxfile;
	Stack stack;
	Heap *heap;
    Status status;
public:
	BoxProgram();
	~BoxProgram();

    Status ReadSourceCode(char *);
    Status SetStack();
    Status SetPool();
    Status SetHeap();
    Status ExecuteProgram();
};


BoxProgram::BoxProgram()
{
	status = 0;
	boxfile = NULL;
	heap = NULL;
}

Status BoxProgram::ReadSourceCode(char *_filepath)
{
    boxfile = new InvokeBox();

    if (boxfile)
		status = boxfile->ReadAll(_filepath);
	else
		status = BOXREADERR;

	return status;
}

Status BoxProgram::SetStack()
{
    Type datatype = 0;
	int intID = 0, i = 0;
	short shortID = 0;
	char buffer[MAXBUFFERWORD] = { 0 };

	boxfile->GetNextWord(&shortID);

	if (shortID == ID_STACK)
	{
		boxfile->GetNextWord(&intID);
		stack.SetVirtualMemory(intID);
		boxfile->GetNextWord(&shortID);

		if (shortID != ID_DATA)
			status = UNDEF_DATA_ERR;
	}
	else
		status = UNDEF_STACK_ERR;

    if(!status)
    {
        do
        {
            boxfile->GetNextWord(&shortID);

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
                    status = STAT_TYPE_ERR;
                break;
            }

            switch (datatype)
            {
                case _CHAR:
                    boxfile->GetNextWord(&buffer[0]);
                break;
                case _INT: case _FLOAT:
                    boxfile->GetNextWord(&buffer[0]);
                    boxfile->GetNextWord(&buffer[1]);
                    boxfile->GetNextWord(&buffer[2]);
                    boxfile->GetNextWord(&buffer[3]);
                break;
                case _LONG: case _DOUBLE:
                    boxfile->GetNextWord(&buffer[0]);
                    boxfile->GetNextWord(&buffer[1]);
                    boxfile->GetNextWord(&buffer[2]);
                    boxfile->GetNextWord(&buffer[3]);
                    boxfile->GetNextWord(&buffer[4]);
                    boxfile->GetNextWord(&buffer[5]);
                    boxfile->GetNextWord(&buffer[6]);
                    boxfile->GetNextWord(&buffer[7]);
                break;
                case _SHORT:
                    boxfile->GetNextWord(&buffer[0]);
                    boxfile->GetNextWord(&buffer[1]);
                break;
                case _STRING:
                    i = 0;

                    boxfile->GetNextWord(&buffer[i]);
                    while (buffer[i]) 	// 0 is end of string
                        boxfile->GetNextWord(&buffer[++i]);

                    buffer[i] = '\0';
                break;
            }

            if (!status)
                status = stack.PushStack(datatype, buffer);

        }while (!status);
    }
	return status;
}

Status BoxProgram::SetPool()
{
	int intID = 0;

	boxfile->GetNextWord(&intID);

    if(intID)
    {
        heap = new Heap(intID);

        if (heap)
            status = heap->GetStatus();
        else
            status = HEAPERR;
    }

	return status;
}

Status BoxProgram::SetHeap()
{
	short shortID = 0;

	boxfile->GetNextWord(&shortID); //reads @h
	boxfile->GetNextWord(&shortID);

	if (shortID != ID_CODE)
	{
        do
		{
			switch (shortID)
			{
                case ID_CHAR:
                    status = heap->PushPointer(_CHAR);
                break;
                case ID_INT:
                    status = heap->PushPointer(_INT);
                break;
                case ID_SHORT:
                    status = heap->PushPointer(_SHORT);
                break;
                case ID_LONG:
                    status = heap->PushPointer(_LONG);
                break;
                case ID_DOUBLE:
                    status = heap->PushPointer(_DOUBLE);
                break;
                case ID_FLOAT:
                    status = heap->PushPointer(_FLOAT);
                break;
                default:
                    status = STAT_TYPE_ERR;
				break;
			}

			boxfile->GetNextWord(&shortID);

			if (shortID == ID_CODE)
				break;

        } while (!status);
	}
	else if (shortID == ID_CODE)
		status = EVERYTHING_OK;
	else
		status = DATA_HEAP_ERR;

	return status;
}

Status BoxProgram::ExecuteProgram()
{
    Execute processor (
		boxfile->GetCodeSegment(),
		boxfile->GetExecuteCode()
    );

	status = processor.GetStatus();

    if (!status)
    {
        status = processor.Do(stack, *heap);
    }

	return status;
}

BoxProgram::~BoxProgram()
{
    if (boxfile)
		delete boxfile;

	boxfile = NULL;
}

#endif	//BOXPROGRAM_H
