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
    void Do(Stack &, Heap &);
protected:
    Registry registry;
    ByteCode bytecode;
    FileList file_list;
    Loop loop_list;
    ALU alu;
    ProgramMonitor *monitor;
};

Execute::Execute()
{
    monitor = null;
}

Execute::Execute(Bcode _codesegment, Bcode _bytecodestart, ProgramMonitor *_monitor)
{
    monitor = _monitor;
    file_list.SetMonitor(monitor);
    registry.SetMonitor(monitor);
    loop_list.SetMonitor(monitor);
    alu.SetMonitor(monitor);
    bytecode.InitByteCode(_codesegment, _bytecodestart);
}

void Execute::Do(Stack &stack, Heap &heap)
{
    Address op1 = null;
    Address op2 = null;
    Type type = null;
    Type tempType = null;
    Data *data = null;
    Byte dataid[MAXARGS] = {null};
    Byte opIndex = START;
    Bcode programCounter = null;

	do
	{
        programCounter = READBYTECODE;
        opIndex = *programCounter;

        switch (opIndex)
        {
            case MOV: case ADD: case SUB: case MUL: case DIV: case MOD:
                GETREGISTRY(op1);
                tempType = type;
                GETREGISTRY(op2);

                if (EOK)
                {
                    alu.Operation(opIndex, op1, op2, tempType);
                }
            continue;
            case ADI: case SUC: case MUC: case DIC: case MODC:
                GETREGISTRY(op1);

                if (EOK)
                {
                    alu.Operation(opIndex, op1, *READBYTECODE, type);
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
            case PUSHS:
                data = stack.SearchFor(*READBYTECODE);
                registry.SetRegistry(data, *READBYTECODE);
            continue;
            case FEOF:
                dataid[0] = *READBYTECODE;
                dataid[1] = *READBYTECODE;

                if(file_list.Feof(dataid[0]))
                {
                    bytecode.Jump(dataid[1]);
                }
            break;
            case ISOPEN:
                dataid[0] = *READBYTECODE;
                dataid[1] = *READBYTECODE;

                if(file_list.Feof(dataid[0]))
                {
                    bytecode.Jump(dataid[1]);
                }
            break;
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
                bytecode.SetByteCode(loop_list.GetStartLoop()-1);
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
                    alu.Rand(op1, type);
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

#endif
