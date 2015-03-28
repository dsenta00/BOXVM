#ifndef EXECUTE_H
#define EXECUTE_H

#include "BoxInfo.h"
#include "AritmethicalOperations.h"
#include "Stack.h"
#include "OperandQueue.h"
#include "Heap.h"
#include "FileList.h"
#include "Loop.h"
#include "ByteCode.h"
#include "ExecuteMacro.h"

class Execute
{
    OperandQueue *op_queue;
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
    Status Do(Stack &);
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
    op_queue = new OperandQueue();

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

Status Execute::Do(Stack &stack)
{
    Bcode operation = NULL;
    Adress op1 = NULL, op2 = NULL;
    Type type = 0;
    char dataid[MAXARGS] = { 0 }, op_index = START;

    do
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
            continue;
            case ADD: case SUB: case MUL: case DIV: case MOD:
                op1 = POPADRESS;
                op2 = POPADRESS;

                status = Operation(op_index, op1, op2, type);
            continue;
            case ADI: case SUC: case MUC: case DIC: case MODC:
                status = Operation(op_index, POPADRESS, *READBYTECODE, type);
            continue;
            case SCAN:
                SCANOP(POPADRESS, type)
            continue;
            case PRINT:
                PRINTOP(POPADRESS, type)
            continue;
            case PRINTLN:
                PRINTLNOP(POPADRESS, type)
            continue;
            case PUSHS:
                dataid[0] = *READBYTECODE;
                type = GETTYPE(0);
                op1 = GETADRESS(0);
                status = op_queue->Push(op1, type);
            continue;
            case GETD:
                FILEOP(ReadOperationFile, double);
            continue;
            case GETF:
                FILEOP(ReadOperationFile, float);
            continue;
            case GETL:
                FILEOP(ReadOperationFile, long);
            continue;
            case GETSH:
                FILEOP(ReadOperationFile, short);
            continue;
            case GETC:
                FILEOP(ReadOperationFile, char);
            continue;
            case GETI:
                FILEOP(ReadOperationFile, int);
            continue;
            case GETS:
                FILEOP(ReadOperationFileString, char);
            continue;
            case PUTD:
                FILEOP(WriteOperationFile, double);
            continue;
            case PUTF:
                FILEOP(WriteOperationFile, float);
            continue;
            case PUTL:
                FILEOP(WriteOperationFile, long);
            continue;
            case PUTSH:
                FILEOP(WriteOperationFile, short);
            continue;
            case PUTC:
                FILEOP(WriteOperationFile, char);
            continue;
            case PUTI:
                FILEOP(WriteOperationFile, int);
            continue;
            case PUTS:
                FILEOP(WriteOperationFileString, char);
            continue;
            case GETLINE:
                FILEOP(GetLine, char);
            continue;
            case CMPE:
                CMPCHECKANDPUSH
                dataid[0] = *READBYTECODE;

                if (status > AREEQUAL)
                {
                    READBYTECODE;
                    bytecode->SkipByteCode(dataid[0]);
                }

            continue;
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
            continue;
            case CMPNE:
                CMPCHECKANDPUSH
                dataid[0] = *READBYTECODE;

                if (status == AREEQUAL)
                {
                    READBYTECODE;
                    bytecode->SkipByteCode(dataid[0]);
                }
            continue;
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
            continue;
            case CMPG:
                CMPCHECKANDPUSH
                dataid[0] = *READBYTECODE;

                if (status == AREEQUAL || status != FIRSTBIGGER)
                {
                    READBYTECODE;
                    bytecode->SkipByteCode(dataid[0]);
                }
            continue;
            case LOOPG:
                LOOPCHECKANDPUSH
                dataid[0] = *READBYTECODE;

                if (status == AREEQUAL || status != FIRSTBIGGER)
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
            continue;
            case CMPL:
                CMPCHECKANDPUSH
                dataid[0] = *READBYTECODE;

                if (status == AREEQUAL || status != SECONDBIGGER)
                {
                    READBYTECODE;
                    bytecode->SkipByteCode(dataid[0]);
                }
            continue;
            case LOOPL:
                LOOPCHECKANDPUSH
                dataid[0] = *READBYTECODE;

                if (status == AREEQUAL || status != SECONDBIGGER)
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
            continue;
            case CMPGE:
                CMPCHECKANDPUSH
                dataid[0] = *READBYTECODE;

                if (status == SECONDBIGGER)
                {
                    READBYTECODE;
                    bytecode->SkipByteCode(dataid[0]);
                }
            continue;
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
            continue;
            case CMPLE:
                CMPCHECKANDPUSH
                dataid[0] = *READBYTECODE;

                if (status == FIRSTBIGGER)
                {
                    READBYTECODE;
                    bytecode->SkipByteCode(dataid[0]);
                }
            continue;
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
            continue;
            case REPLOOP:
                bytecode->SetByteCode(loop_list->GetStartLoop()-1);

                if (operation != loop_list->GetEndLoop())
                    loop_list->SetEndLoop(operation);
            continue;
            case OPENW:
                OPENFILE(_WRITE)
            continue;
            case OPENR:
                OPENFILE(_READ)
            continue;
            case OPENA:
                OPENFILE(_APPEND)
            continue;
            case RAND:
                dataid[0] = *READBYTECODE;
                CHECKANDGETADRESS(op1, 0)

                status = rand();
                status = Operation(op_index, op1, (char *)&status, type);
            continue;
            case ESTART:
                printf("\n\tPress any key to continue . . .\n");
            continue;
            default:
                status = UKNOWN_OPER_ERR;
            continue;
        }
    }while (status >= EVERYTHING_OK && op_index != ESTART);

    if (status > EVERYTHING_OK)
        status = EVERYTHING_OK;

    return status;
}

Status Execute::Do(Stack &stack, Heap &heap)
{
    Bcode operation = NULL;
    Adress op1 = NULL, op2 = NULL;
    Type type = 0;
    char dataid[MAXARGS] = { 0 }, op_index = START;

    do
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
            continue;
            case ADD: case SUB: case MUL: case DIV: case MOD:
                op1 = POPADRESS;
                op2 = POPADRESS;

                status = Operation(op_index, op1, op2, type);
            continue;
            case ADI: case SUC: case MUC: case DIC: case MODC:
                status = Operation(op_index, POPADRESS, *READBYTECODE, type);
            continue;
            case SCAN:
                SCANOP(POPADRESS, type)
            continue;
            case PRINT:
                PRINTOP(POPADRESS, type)
            continue;
            case PRINTLN:
                PRINTLNOP(POPADRESS, type)
            continue;
            case NEW:
                dataid[0] = *READBYTECODE;
                dataid[1] = *READBYTECODE;
                status = heap.MallocDefrag(dataid[0], dataid[1]);
            continue;
            case FNEW:
                dataid[0] = *READBYTECODE;
                dataid[1] = *READBYTECODE;
                status = heap.Malloc(dataid[0], dataid[1]);
            continue;
            case NEWV:
                dataid[0] = *READBYTECODE;
                dataid[1] = *READBYTECODE;
                status = heap.MallocDefrag(dataid[0], *(int *)GETADRESS(1));
            continue;
            case FNEWV:
                dataid[0] = *READBYTECODE;
                dataid[1] = *READBYTECODE;
                status = heap.Malloc(dataid[0], *(int *)GETADRESS(1));
            continue;
            case FREE:
                status = heap.Free(*READBYTECODE);
            continue;
            case LEA:
                dataid[0] = *READBYTECODE;
                dataid[1] = *READBYTECODE;
                status = heap.Lea(op_queue, &type, dataid[0], *(int *)GETADRESS(1));
            continue;
            case LEAC:
                dataid[0] = *READBYTECODE;
                dataid[1] = *READBYTECODE;
                status = heap.Lea(op_queue, &type, dataid[0], dataid[1]);
            continue;
            case PUSH:
                status = heap.Lea(op_queue, &type, -1, *READBYTECODE);
            continue;
            case PUSHS:
                dataid[0] = *READBYTECODE;
                type = GETTYPE(0);
                op1 = GETADRESS(0);
                status = op_queue->Push(op1, type);
            continue;
            case GETD:
                FILEOP(ReadOperationFile, double);
            continue;
            case GETF:
                FILEOP(ReadOperationFile, float);
            continue;
            case GETL:
                FILEOP(ReadOperationFile, long);
            continue;
            case GETSH:
                FILEOP(ReadOperationFile, short);
            continue;
            case GETC:
                FILEOP(ReadOperationFile, char);
            continue;
            case GETI:
                FILEOP(ReadOperationFile, int);
            continue;
            case GETS:
                FILEOP(ReadOperationFileString, char);
            continue;
            case PUTD:
                FILEOP(WriteOperationFile, double);
            continue;
            case PUTF:
                FILEOP(WriteOperationFile, float);
            continue;
            case PUTL:
                FILEOP(WriteOperationFile, long);
            continue;
            case PUTSH:
                FILEOP(WriteOperationFile, short);
            continue;
            case PUTC:
                FILEOP(WriteOperationFile, char);
            continue;
            case PUTI:
                FILEOP(WriteOperationFile, int);
            continue;
            case PUTS:
                FILEOP(WriteOperationFileString, char);
            continue;
            case GETLINE:
                FILEOP(GetLine, char);
            continue;
            case CMPE:
                CMPCHECKANDPUSH
                dataid[0] = *READBYTECODE;

                if (status > AREEQUAL)
                {
                    READBYTECODE;
                    bytecode->SkipByteCode(dataid[0]);
                }

            continue;
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
            continue;
            case CMPNE:
                CMPCHECKANDPUSH
                dataid[0] = *READBYTECODE;

                if (status == AREEQUAL)
                {
                    READBYTECODE;
                    bytecode->SkipByteCode(dataid[0]);
                }
            continue;
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
            continue;
            case CMPG:
                CMPCHECKANDPUSH
                dataid[0] = *READBYTECODE;

                if (status == AREEQUAL || status != FIRSTBIGGER)
                {
                    READBYTECODE;
                    bytecode->SkipByteCode(dataid[0]);
                }
            continue;
            case LOOPG:
                LOOPCHECKANDPUSH
                dataid[0] = *READBYTECODE;

                if (status == AREEQUAL || status != FIRSTBIGGER)
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
            continue;
            case CMPL:
                CMPCHECKANDPUSH
                dataid[0] = *READBYTECODE;

                if (status == AREEQUAL || status != SECONDBIGGER)
                {
                    READBYTECODE;
                    bytecode->SkipByteCode(dataid[0]);
                }
            continue;
            case LOOPL:
                LOOPCHECKANDPUSH
                dataid[0] = *READBYTECODE;

                if (status == AREEQUAL || status != SECONDBIGGER)
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
            continue;
            case CMPGE:
                CMPCHECKANDPUSH
                dataid[0] = *READBYTECODE;

                if (status == SECONDBIGGER)
                {
                    READBYTECODE;
                    bytecode->SkipByteCode(dataid[0]);
                }
            continue;
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
            continue;
            case CMPLE:
                CMPCHECKANDPUSH
                dataid[0] = *READBYTECODE;

                if (status == FIRSTBIGGER)
                {
                    READBYTECODE;
                    bytecode->SkipByteCode(dataid[0]);
                }
            continue;
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
            continue;
            case REPLOOP:
                bytecode->SetByteCode(loop_list->GetStartLoop()-1);

                if (operation != loop_list->GetEndLoop())
                    loop_list->SetEndLoop(operation);
            continue;
            case OPENW:
                OPENFILE(_WRITE)
            continue;
            case OPENR:
                OPENFILE(_READ)
            continue;
            case OPENA:
                OPENFILE(_APPEND)
            continue;
            case RAND:
                dataid[0] = *READBYTECODE;
                CHECKANDGETADRESS(op1, 0)

                status = rand();
                status = Operation(op_index, op1, (char *)&status, type);
            continue;
            case ESTART:
                printf("\n\tPress any key to continue . . .\n");
            continue;
            default:
                status = UKNOWN_OPER_ERR;
            continue;
		}
	}while (status >= EVERYTHING_OK && op_index != ESTART);

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
