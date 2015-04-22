#ifndef EXECUTE_H
#define EXECUTE_H
#include "BoxInfo.h"
#include "ALU.h"
#include "Stack.h"
#include "Registry.h"
#include "Heap.h"
#include "FileList.h"
#include "Loop.h"
#include "ByteCode.h"
#include "ExecuteMacro.h"

class Execute {
public:
	Execute();
    Execute(Bcode, Bcode, ProgramMonitor *);
    ~Execute();

    void Do(Stack &, Heap &);
protected:
    Registry registry;
    ByteCode *bytecode;
    FileList file_list;
    Loop loop_list;
    Bcode operation;
    ALU alu;
    ProgramMonitor *monitor;
    Adress op1;
    Adress op2;
    Type type;
    Type temp;
    Data *data;
    Byte dataid[MAXARGS];
    Byte op_index;
    Status status;
};

Execute::Execute()
{
    bytecode = NULL;
    operation = NULL;
    op1 = op2 = NULL;
    type = temp = 0;
	op_index = START;
    monitor = NULL;
    status = 0;
}

Execute::Execute(Bcode _codesegment, Bcode _bytecodestart, ProgramMonitor *_monitor)
{
    monitor = _monitor;
    file_list.SetMonitor(monitor);
    registry.SetMonitor(monitor);
    loop_list.SetMonitor(monitor);
    alu.SetMonitor(monitor);
    op_index = START;
    operation = NULL;
    op1 = op2 = NULL;
    type = temp = 0;
    bytecode = new ByteCode(_codesegment, _bytecodestart);

    if (!bytecode)
        SETERR(BC_MAL_ERR);
}

void Execute::Do(Stack &stack, Heap &heap)
{
	do
	{
		operation = READBYTECODE;
		op_index = *operation;

		switch (op_index)
        {
            case MOV: case ADD: case SUB: case MUL: case DIV: case MOD:
                GETREGISTRY(op1);
                temp = type;
                GETREGISTRY(op2);

                if (EOK)
                {
                    alu.Operation(op_index, op1, op2, temp);
                }
            continue;
            case ADI: case SUC: case MUC: case DIC: case MODC:
                GETREGISTRY(op1);

                if (EOK)
                {
                    alu.Operation(op_index, op1, *READBYTECODE, type);
                }
            continue;
            case SCAN:
                GETREGISTRY(op1);
                if (EOK)
                {
                    alu.Scan(op1, type);
                }
            continue;
            case PRINT:
                GETREGISTRY(op1);
                if (EOK)
                {
                    alu.Print(op1, type);
                }
            continue;
            case PRINTLN:
                GETREGISTRY(op1);
                if (EOK)
                {
                    alu.PrintLN(op1, type);
                }
            continue;
            case NEW:
                dataid[0] = *READBYTECODE;
                dataid[1] = *READBYTECODE;
                heap.MallocDefrag(dataid[0], dataid[1]);
            continue;
            case FNEW:
                dataid[0] = *READBYTECODE;
                dataid[1] = *READBYTECODE;
                heap.Malloc(dataid[0], dataid[1]);
            continue;
            case NEWV:
                dataid[0] = *READBYTECODE;
                GETREGISTRY(op1);
                heap.MallocDefrag(dataid[0], *(Size *)op1);
            continue;
            case FNEWV:
                dataid[0] = *READBYTECODE;
                GETREGISTRY(op1);
                heap.Malloc(dataid[0], *(Size *)op1);
            continue;
            case FREE:
                heap.Free(*READBYTECODE);
            continue;
            case LEA:
                dataid[0] = *READBYTECODE;
                GETREGISTRY(op1);
                heap.Lea(registry, &type, dataid[0], *(Count *)op1, *READBYTECODE);
            continue;
            case LEAC:
                dataid[0] = *READBYTECODE;
                dataid[1] = *READBYTECODE;
                heap.Lea(registry, &type, dataid[0], dataid[1], *READBYTECODE);
            continue;
            case PUSH:
                dataid[0] = *READBYTECODE;
                heap.Lea(registry, &type, -1, dataid[0], 0);
            continue;
            case PUSHS:
                data = stack.SearchFor(*READBYTECODE);
                registry.SetRegistry(data, *READBYTECODE);
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
                BRANCHIF(!AREEQUAL);
            continue;
            case LOOPE:
                EXITLOOPIF(!AREEQUAL);
            continue;
            case CMPNE:
                BRANCHIF(AREEQUAL);
            continue;
            case LOOPNE:
                EXITLOOPIF(AREEQUAL);
            continue;
            case CMPG:
                BRANCHIF(AREEQUAL || FIRSTBIGGER);
            continue;
            case LOOPG:
                EXITLOOPIF(AREEQUAL || FIRSTBIGGER);
            continue;
            case CMPL:
                BRANCHIF(AREEQUAL || SECONDBIGGER);
            continue;
            case LOOPL:
                EXITLOOPIF(AREEQUAL || SECONDBIGGER);
            continue;
            case CMPGE:
                BRANCHIF(SECONDBIGGER);
            continue;
            case LOOPGE:
                EXITLOOPIF(SECONDBIGGER);
            continue;
            case CMPLE:
                BRANCHIF(FIRSTBIGGER);
            continue;
            case LOOPLE:
                EXITLOOPIF(FIRSTBIGGER);
            continue;
                //operation [none]
            case REPLOOP:
                bytecode->SetByteCode(loop_list.GetStartLoop()-1);
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
                if (EOK)
                {
                    alu.Rand(op1,type);
                }
            continue;
            case ESTART:
                return;
            continue;
            default:
                SETERR(UKNOWN_OPER_ERR);
            break;
		}

    } while(EOK);
}

Execute::~Execute()
{
	if (bytecode)
        delete bytecode;
}

#endif
