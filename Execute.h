#ifndef EXECUTE_H
#define EXECUTE_H

#include "BoxInfo.h"
#include "AritmethicalOperations.h"
#include "Stack.h"
#include "OperationQueue.h"
#include "Heap.h"
#include "FileList.h"
#include "Loop.h"
#include "ByteCode.h"
#include "ExecuteMacro.h"

class Execute
{
	OperationQueue *op_queue;
	ByteCode *bytecode;
	FileList *file_list;
	Loop *loop_list;
    Status status;
public:
	Execute();
    Execute(Bcode, Bcode);
	~Execute();

    Status GetStatus();
    Status Do(Stack &, Heap &);
};

Status Execute::GetStatus()
{
	return status;
}

Execute::Execute()
{
	op_queue = NULL;
	bytecode = NULL;
	file_list = NULL;
	loop_list = NULL;
	status = EVERYTHING_OK;
}

Execute::Execute(Bcode _codesegment, Bcode _bytecodestart)
{
	status = EVERYTHING_OK;
	op_queue = new OperationQueue();

	if (op_queue != NULL)
	{
		loop_list = new Loop();

		if (loop_list != NULL)
		{
			file_list = new FileList();

			if (file_list != NULL)
			{
                bytecode = new ByteCode(_codesegment, _bytecodestart);

				if (bytecode == NULL)
					status = BC_MAL_ERR;
			}
			else
				status = FLIST_MAL_ERR;
		}
		else
			status = LOOP_MAL_ERR;
	}
	else
		status = BUFF_MALL_ERR;
}

Status Execute::Do(Stack &stack, Heap &heap)
{
    Bcode operation = NULL;
    Adress op1 = NULL, op2 = NULL;
    Type type = 0;
    char dataid[MAXARGS] = { 0 }, op_index = START;

    while (status >= EVERYTHING_OK && op_index != ESTART)
	{
		operation = READBYTECODE;
        op_index = *operation;

        switch (op_index)
		{
            case MOV:
                dataid[0] = *READBYTECODE;
                dataid[1] = *READBYTECODE;

                CHECKANDGETADRESS(op1, 0)
                CHECKANDGETADRESS(op2, 1)

                status = Operation(op_index, op1, op2, type);
            break;
            case ADD: case SUB: case MUL: case DIV: case MOD:
                op1 = POPADRESS;
                op2 = POPADRESS;

                status = Operation(op_index, op1, op2, type);
            break;
            case ADI: case SUC: case MUC: case DIC: case MODC:
                dataid[0] = *READBYTECODE;
                op1 = POPADRESS;

                status = Operation(op_index, op1, dataid[0], type);
            break;
            case SCAN:
                op1 = POPADRESS;
                SCANOP(op1, type)
            break;
            case PRINT:
                op1 = POPADRESS;
                PRINTOP(op1, type)
            break;
            case NEW:
                dataid[0] = *READBYTECODE;
                dataid[1] = *READBYTECODE;
                status = heap.MallocDefrag(dataid[0], dataid[1]);
            break;
            case FNEW:
                dataid[0] = *READBYTECODE;
                dataid[1] = *READBYTECODE;
                status = heap.Malloc(dataid[0], dataid[1]);
            break;
            case NEWV:
                dataid[0] = *READBYTECODE;
                dataid[1] = *READBYTECODE;
                status = heap.MallocDefrag(dataid[0], *(int *)GETADRESS(1));
            break;
            case FNEWV:
                dataid[0] = *READBYTECODE;
                dataid[1] = *READBYTECODE;
                status = heap.Malloc(dataid[0], *(int *)GETADRESS(1));
            break;
            case FREE:
                status = heap.Free(*READBYTECODE);
            break;
            case LEA:
                dataid[0] = *READBYTECODE;
                dataid[1] = *READBYTECODE;
                status = heap.Lea(op_queue, &type, dataid[0], *(int *)GETADRESS(1));
            break;
            case LEAC:
                dataid[0] = *READBYTECODE;
                dataid[1] = *READBYTECODE;
                status = heap.Lea(op_queue, &type, dataid[0], dataid[1]);
            break;
            case PUSH:
                dataid[0] = *READBYTECODE;
                status = heap.Lea(op_queue, &type, -1, dataid[0]);
            break;
            case PUSHS:
                dataid[0] = *READBYTECODE;
                type = GETTYPE(0);
                op1 = GETADRESS(0);
                status = op_queue->Push(op1, type);
            break;
            case GETD:
                op1 = POPADRESS;
                FILEOP(ReadOperationFile, double);
            break;
            case GETF:
                op1 = POPADRESS;
                FILEOP(ReadOperationFile, float);
            break;
            case GETL:
                op1 = POPADRESS;
                FILEOP(ReadOperationFile, long);
            break;
            case GETSH:
                op1 = POPADRESS;
                FILEOP(ReadOperationFile, short);
            break;
            case GETC:
                op1 = POPADRESS;
                FILEOP(ReadOperationFile, char);
            break;
            case GETI:
                op1 = POPADRESS;
                FILEOP(ReadOperationFile, int);
            break;
            case GETS:
                op1 = POPADRESS;
                FILEOP(ReadOperationFileString, char);
            break;
            case PUTD:
                op1 = POPADRESS;
                FILEOP(WriteOperationFile, double);
            break;
            case PUTF:
                op1 = POPADRESS;
                FILEOP(WriteOperationFile, float);
            break;
            case PUTL:
                op1 = POPADRESS;
                FILEOP(WriteOperationFile, long);
            break;
            case PUTSH:
                op1 = POPADRESS;
                FILEOP(WriteOperationFile, short);
            break;
            case PUTC:
                op1 = POPADRESS;
                FILEOP(WriteOperationFile, char);
            break;
            case PUTI:
                op1 = POPADRESS;
                FILEOP(WriteOperationFile, int);
            break;
            case PUTS:
                op1 = POPADRESS;
                FILEOP(WriteOperationFileString, char);
            break;
            case GETLINE:
                op1 = POPADRESS;
                FILEOP(GetLine, char);
            break;
            case CMPE:
                CMPCHECKANDPUSH
                dataid[0] = *READBYTECODE;

                if (status > AREEQUAL)
                {
                    READBYTECODE;
                    bytecode->SkipByteCode(dataid[0]);
                }

            break;
            case LOOPE:
                LOOPCHECKANDPUSH
                dataid[0] = *READBYTECODE;

                if (status > AREEQUAL)
                {
                    if ((operation = loop_list->GetEndLoop()) != NULL)
                        bytecode->SetByteCode(operation);
                    else
                    {
                        READBYTECODE; //preskace se jedan byte
                        bytecode->SkipByteCode(dataid[0]);
                    }

                    loop_list->PopLoop();
                }
            break;
            case CMPNE:
                CMPCHECKANDPUSH
                dataid[0] = *READBYTECODE;

                if (status == AREEQUAL)
                {
                    READBYTECODE;
                    bytecode->SkipByteCode(dataid[0]);
                }
            break;
            case LOOPNE:
                LOOPCHECKANDPUSH
                dataid[0] = *READBYTECODE;

                if (status == AREEQUAL)
                {
                    if ((operation = loop_list->GetEndLoop()) != NULL)
                        bytecode->SetByteCode(operation);
                    else
                    {
                        READBYTECODE; //preskace se jedan byte
                        bytecode->SkipByteCode(dataid[0]);
                    }

                    loop_list->PopLoop();
                }
            break;
            case CMPG:
                CMPCHECKANDPUSH
                dataid[0] = *READBYTECODE;

                if (status != FIRSTBIGGER)
                {
                    READBYTECODE;
                    bytecode->SkipByteCode(dataid[0]);
                }
            break;
            case LOOPG:
                LOOPCHECKANDPUSH
                dataid[0] = *READBYTECODE;

                if (status != FIRSTBIGGER)
                {
                    if ((operation = loop_list->GetEndLoop()) != NULL)
                        bytecode->SetByteCode(operation);
                    else
                    {
                        READBYTECODE; //preskace se jedan byte
                        bytecode->SkipByteCode(dataid[0]);
                    }

                    loop_list->PopLoop();
                }
            break;
            case CMPL:
                CMPCHECKANDPUSH
                dataid[0] = *READBYTECODE;

                if (status != SECONDBIGGER)
                {
                    READBYTECODE;
                    bytecode->SkipByteCode(dataid[0]);
                }
            break;
            case LOOPL:
                LOOPCHECKANDPUSH
                dataid[0] = *READBYTECODE;

                if (status != SECONDBIGGER)
                {
                    if ((operation = loop_list->GetEndLoop()) != NULL)
                        bytecode->SetByteCode(operation);
                    else
                    {
                        READBYTECODE; //preskace se jedan byte
                        bytecode->SkipByteCode(dataid[0]);
                    }

                    loop_list->PopLoop();
                }
            break;
            case CMPGE:
                CMPCHECKANDPUSH
                dataid[0] = *READBYTECODE;

                if (status == SECONDBIGGER)
                {
                    READBYTECODE;
                    bytecode->SkipByteCode(dataid[0]);
                }
            break;
            case LOOPGE:
                LOOPCHECKANDPUSH
                dataid[0] = *READBYTECODE;

                if (status == SECONDBIGGER)
                {
                    if ((operation = loop_list->GetEndLoop()) != NULL)
                        bytecode->SetByteCode(operation);
                    else
                    {
                        READBYTECODE; //preskace se jedan byte
                        bytecode->SkipByteCode(dataid[0]);
                    }

                    loop_list->PopLoop();
                }
            break;
            case CMPLE:
                CMPCHECKANDPUSH
                dataid[0] = *READBYTECODE;

                if (status == FIRSTBIGGER)
                {
                    READBYTECODE;
                    bytecode->SkipByteCode(dataid[0]);
                }
            break;
            case LOOPLE:
                LOOPCHECKANDPUSH
                dataid[0] = *READBYTECODE;

                if (status == FIRSTBIGGER)
                {
                    if ((operation = loop_list->GetEndLoop()) != NULL)
                        bytecode->SetByteCode(operation);
                    else
                    {
                        READBYTECODE; //preskace se jedan byte
                        bytecode->SkipByteCode(dataid[0]);
                    }

                    loop_list->PopLoop();
                }
            break;
            case REPLOOP:
                bytecode->SetByteCode(loop_list->GetStartLoop()-1);//

                if (operation != loop_list->GetEndLoop())
                    loop_list->SetEndLoop(operation);
            break;
            case OPENW:
                dataid[0] = *READBYTECODE;
                status = file_list->PushFile(dataid[0], GETADRESS(0), _WRITE);
            break;
            case OPENR:
                dataid[0] = *READBYTECODE;
                status = file_list->PushFile(dataid[0], GETADRESS(0), _READ);
            break;
            case OPENA:
                dataid[0] = *READBYTECODE;
                status = file_list->PushFile(dataid[0], GETADRESS(0), _APPEND);
            break;
            case RAND:
                dataid[0] = *READBYTECODE;
                CHECKANDGETADRESS(op1, 0)

                status = rand();
                status = Operation(op_index, op1, (char *)&status, type);
            break;
            case ESTART:
                printf("\n\tPress any key to continue . . .\n");
            break;
            default:
                status = UKNOWN_OPER_ERR;
            break;
		}
	}

	if (status > EVERYTHING_OK)
		status = EVERYTHING_OK;

	return status;
}

Execute::~Execute()
{
	if (bytecode != NULL)
		delete bytecode;

	if (op_queue != NULL)
		delete op_queue;

	if (loop_list != NULL)
		delete loop_list;

	if (file_list != NULL)
		delete file_list;
}

#endif
