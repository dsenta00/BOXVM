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
	OperandQueue *opQ;
	ByteCode *bytecode;
	FileList *file_list;
	Loop *loop_list;
	Bcode operation;
	Adress op1;
	Adress op2;
	Type type;
	char dataid[MAXARGS];
	char op_index;
	Status mode;
	Status status;
public:
	Execute();
	Execute(Bcode, Bcode);
	~Execute();

	Status GetStatus();
	Status OpQ(Stack &, Heap &);
	Status Reg(Stack &, Heap &);
	Status Do(Stack &, Heap &);
};

Status Execute::GetStatus()
{
	return status;
}

Execute::Execute()
{
	opQ = NULL;
	bytecode = NULL;
	file_list = NULL;
	loop_list = NULL;
	operation = NULL;
	op1 = op2 = NULL;
	mode = OPQMODE;
	type = 0;
	op_index = START;
	status = EVERYTHING_OK;
}

Execute::Execute(Bcode _codesegment, Bcode _bytecodestart)
{
	status = EVERYTHING_OK;
	mode = OPQMODE;
	op_index = START;
	operation = NULL;
	op1 = op2 = NULL;
	type = 0;
	opQ = new OperandQueue();

	if (opQ)
	{
		loop_list = new Loop();

		if (loop_list)
		{
			file_list = new FileList();

			if (file_list)
			{
				bytecode = new ByteCode(_codesegment, _bytecodestart);

				if (!bytecode)
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
	while (status >= EVERYTHING_OK && op_index != ESTART)
	{
		switch (mode)
		{
		case OPQMODE:
			status = OpQ(stack, heap);
			continue;
		case REGISTRYMODE:
			status = Reg(stack, heap);
			continue;
		default:
			return status;
			break;
		}
	}

	return status;
}

Status Execute::OpQ(Stack &stack, Heap &heap)
{
	do
	{
		operation = READBYTECODE;
		op_index = *operation;

		switch (op_index)
		{
            case MOV:
                dataid[0] = *READBYTECODE;
                dataid[1] = *READBYTECODE;

                CHECKANDGETADRESS(op1, 0);
                CHECKANDGETADRESS(op2, 1);

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
                Scan(POPADRESS, type);
            continue;
            case PRINT:
                Print(POPADRESS, type);
            continue;
            case PRINTLN:
                Println(POPADRESS, type);
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
                status = heap.Lea(opQ, &type, dataid[0], *(int *)GETADRESS(1));
            continue;
            case LEAC:
                dataid[0] = *READBYTECODE;
                dataid[1] = *READBYTECODE;
                status = heap.Lea(opQ, &type, dataid[0], dataid[1]);
            continue;
            case PUSH:
                status = heap.Lea(opQ, &type, -1, *READBYTECODE);
            continue;
            case PUSHS:
                dataid[0] = *READBYTECODE;
                type = GETTYPE(0);
                op1 = GETADRESS(0);
                status = opQ->Push(op1, type);
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
                CMPCHECKANDPUSH;
                dataid[0] = *READBYTECODE;

                if (status > AREEQUAL)
                {
                    READBYTECODE;
                    bytecode->SkipByteCode(dataid[0]);
                }

            continue;
            case LOOPE:
                LOOPCHECKANDPUSH;
                dataid[0] = *READBYTECODE;

                if (status > AREEQUAL)
                {
                    if ((operation = loop_list->GetEndLoop()))
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
                CMPCHECKANDPUSH;
                dataid[0] = *READBYTECODE;

                if (status == AREEQUAL)
                {
                    READBYTECODE;
                    bytecode->SkipByteCode(dataid[0]);
                }
            continue;
            case LOOPNE:
                LOOPCHECKANDPUSH;
                dataid[0] = *READBYTECODE;

                if (status == AREEQUAL)
                {
                    if ((operation = loop_list->GetEndLoop()))
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
                CMPCHECKANDPUSH;
                dataid[0] = *READBYTECODE;

                if (status == AREEQUAL || status != FIRSTBIGGER)
                {
                    READBYTECODE;
                    bytecode->SkipByteCode(dataid[0]);
                }
            continue;
            case LOOPG:
                LOOPCHECKANDPUSH;
                dataid[0] = *READBYTECODE;

                if (status == AREEQUAL || status != FIRSTBIGGER)
                {
                    if ((operation = loop_list->GetEndLoop()))
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
                CMPCHECKANDPUSH;
                dataid[0] = *READBYTECODE;

                if (status == AREEQUAL || status != SECONDBIGGER)
                {
                    READBYTECODE;
                    bytecode->SkipByteCode(dataid[0]);
                }
            continue;
            case LOOPL:
                LOOPCHECKANDPUSH;
                dataid[0] = *READBYTECODE;

                if (status == AREEQUAL || status != SECONDBIGGER)
                {
                    if ((operation = loop_list->GetEndLoop()))
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
                CMPCHECKANDPUSH;
                dataid[0] = *READBYTECODE;

                if (status == SECONDBIGGER)
                {
                    READBYTECODE;
                    bytecode->SkipByteCode(dataid[0]);
                }
            continue;
            case LOOPGE:
                LOOPCHECKANDPUSH;
                dataid[0] = *READBYTECODE;

                if (status == SECONDBIGGER)
                {
                    if ((operation = loop_list->GetEndLoop()))
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
                CMPCHECKANDPUSH;
                dataid[0] = *READBYTECODE;

                if (status == FIRSTBIGGER)
                {
                    READBYTECODE;
                    bytecode->SkipByteCode(dataid[0]);
                }
            continue;
            case LOOPLE:
                LOOPCHECKANDPUSH;
                dataid[0] = *READBYTECODE;

                if (status == FIRSTBIGGER)
                {
                    if ((operation = loop_list->GetEndLoop()))
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
                bytecode->SetByteCode(loop_list->GetStartLoop() - 1);

                if (operation != loop_list->GetEndLoop())
                    loop_list->SetEndLoop(operation);
            continue;
            case OPENW:
                OPENFILE(_WRITE);
            continue;
            case OPENR:
                OPENFILE(_READ);
            continue;
            case OPENA:
                OPENFILE(_APPEND);
            continue;
            case RAND:
                dataid[0] = *READBYTECODE;
                CHECKANDGETADRESS(op1, 0);

                status = rand();
                status = Operation(op_index, op1, (char *)&status, type);
            continue;
            case REG:
                mode = REGISTRYMODE;
            continue;
            case ESTART:
            continue;
            default:
                status = UKNOWN_OPER_ERR;
            continue;
		}

	} while (status >= EVERYTHING_OK && op_index != ESTART && mode == OPQMODE);

	return status;
}

Status Execute::Reg(Stack &stack, Heap &heap)
{
	opQ->ResetOperandQueue();

	do
	{
		operation = READBYTECODE;
		op_index = *operation;

		switch (op_index)
        {
            case MOV: case ADD: case SUB: case MUL: case DIV: case MOD:
                GETREGISTRY(op1);

                if (!status)
                {
                    GETREGISTRY(op2);

                    if (!status)
                    {
                        status = Operation(op_index, op1, op2, type);
                    }
                }
            continue;
            case ADI: case SUC: case MUC: case DIC: case MODC:
                GETREGISTRY(op1);

                if (!status)
                {
                    status = Operation(op_index, op1, *READBYTECODE, type);
                }
            continue;
            case SCAN:
                GETREGISTRY(op1);
                if (!status)
                {
                    Scan(op1, type);
                }
            continue;
            case PRINT:
                GETREGISTRY(op1);
                if (!status)
                {
                    Print(op1, type);
                }
            continue;
            case PRINTLN:
                GETREGISTRY(op1);
                if (!status)
                {
                    Println(op1, type);
                }
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
                status = heap.Lea(opQ, &type, dataid[0], *(int *)GETADRESS(1));
            continue;
            case LEAC:
                dataid[0] = *READBYTECODE;
                dataid[1] = *READBYTECODE;
                status = heap.Lea(opQ, &type, dataid[0], dataid[1]);
            continue;
            case PUSH:
                status = heap.Lea(opQ, &type, -1, *READBYTECODE);
            continue;
            case PUSHS:

                dataid[0] = *READBYTECODE;
                type = GETTYPE(0);
                op1 = GETADRESS(0);

                SETREGISTRY(op1);
            continue;
            case GETD:
                FILEOPREG(ReadOperationFile, double);
            continue;
            case GETF:
                FILEOPREG(ReadOperationFile, float);
            continue;
            case GETL:
                FILEOPREG(ReadOperationFile, long);
            continue;
            case GETSH:
                FILEOPREG(ReadOperationFile, short);
            continue;
            case GETC:
                FILEOPREG(ReadOperationFile, char);
            continue;
            case GETI:
                FILEOPREG(ReadOperationFile, int);
            continue;
            case GETS:
                FILEOPREG(ReadOperationFileString, char);
            continue;
            case PUTD:
                FILEOPREG(WriteOperationFile, double);
            continue;
            case PUTF:
                FILEOPREG(WriteOperationFile, float);
            continue;
            case PUTL:
                FILEOPREG(WriteOperationFile, long);
            continue;
            case PUTSH:
                FILEOPREG(WriteOperationFile, short);
            continue;
            case PUTC:
                FILEOPREG(WriteOperationFile, char);
            continue;
            case PUTI:
                FILEOPREG(WriteOperationFile, int);
            continue;
            case PUTS:
                FILEOPREG(WriteOperationFileString, char);
            continue;
            case GETLINE:
                FILEOPREG(GetLine, char);
            continue;
            case CMPE:
                CMPCHECKANDPUSHREG;
                dataid[0] = *READBYTECODE;

                if (status > AREEQUAL)
                {
                    READBYTECODE;
                    bytecode->SkipByteCode(dataid[0]);
                }

            continue;
            case LOOPE:
                LOOPCHECKANDPUSHREG;
                dataid[0] = *READBYTECODE;

                if (status > AREEQUAL)
                {
                    if ((operation = loop_list->GetEndLoop()))
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
                CMPCHECKANDPUSHREG;
                dataid[0] = *READBYTECODE;

                if (status == AREEQUAL)
                {
                    READBYTECODE;
                    bytecode->SkipByteCode(dataid[0]);
                }
            continue;
            case LOOPNE:
                LOOPCHECKANDPUSHREG;
                dataid[0] = *READBYTECODE;

                if (status == AREEQUAL)
                {
                    if ((operation = loop_list->GetEndLoop()))
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
                CMPCHECKANDPUSHREG;
                dataid[0] = *READBYTECODE;

                if (status == AREEQUAL || status != FIRSTBIGGER)
                {
                    READBYTECODE;
                    bytecode->SkipByteCode(dataid[0]);
                }
            continue;
            case LOOPG:
                LOOPCHECKANDPUSHREG;
                dataid[0] = *READBYTECODE;

                if (status == AREEQUAL || status != FIRSTBIGGER)
                {
                    if ((operation = loop_list->GetEndLoop()))
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
                CMPCHECKANDPUSHREG;
                dataid[0] = *READBYTECODE;

                if (status == AREEQUAL || status != SECONDBIGGER)
                {
                    READBYTECODE;
                    bytecode->SkipByteCode(dataid[0]);
                }
            continue;
            case LOOPL:
                LOOPCHECKANDPUSHREG;
                dataid[0] = *READBYTECODE;

                if (status == AREEQUAL || status != SECONDBIGGER)
                {
                    if ((operation = loop_list->GetEndLoop()))
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
                CMPCHECKANDPUSHREG;
                dataid[0] = *READBYTECODE;

                if (status == SECONDBIGGER)
                {
                    READBYTECODE;
                    bytecode->SkipByteCode(dataid[0]);
                }
            continue;
            case LOOPGE:
                LOOPCHECKANDPUSHREG;
                dataid[0] = *READBYTECODE;

                if (status == SECONDBIGGER)
                {
                    if ((operation = loop_list->GetEndLoop()))
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
                CMPCHECKANDPUSHREG;
                dataid[0] = *READBYTECODE;

                if (status == FIRSTBIGGER)
                {
                    READBYTECODE;
                    bytecode->SkipByteCode(dataid[0]);
                }
            continue;
            case LOOPLE:
                LOOPCHECKANDPUSHREG;
                dataid[0] = *READBYTECODE;

                if (status == FIRSTBIGGER)
                {
                    if ((operation = loop_list->GetEndLoop()))
                        bytecode->SetByteCode(operation);
                    else
                    {
                        READBYTECODE; //preskace se jedan byte
                        bytecode->SkipByteCode(dataid[0]);
                    }

                    loop_list->PopLoop();
                }
            continue;
                //operation [none]
            case REPLOOP:
                bytecode->SetByteCode(loop_list->GetStartLoop() - 1);

                if (operation != loop_list->GetEndLoop())
                    loop_list->SetEndLoop(operation);
            continue;
            case OPENW:
                OPENFILE(_WRITE);
            continue;
            case OPENR:
                OPENFILE(_READ);
            continue;
            case OPENA:
                OPENFILE(_APPEND);
            continue;
            case RAND:
                GETREGISTRY(op1);
                if (!status)
                {
                    status = rand();
                    status = Operation(op_index, op1, (char *)&status, type);
                }
            continue;
            case ESTART:
                return status;
            continue;
            case ENDREG:
                mode = OPQMODE;
            break;
            default:
                status = UKNOWN_OPER_ERR;
            continue;
		}

	} while (status >= EVERYTHING_OK && op_index != ENDREG);

	return status;
}

Execute::~Execute()
{
	if (bytecode)
		delete bytecode;

	if (opQ)
		delete opQ;

	if (loop_list)
		delete loop_list;

	if (file_list)
		delete file_list;
}

#endif
