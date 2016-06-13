#ifndef BOX_INSTRUCTION_H
#define BOX_INSTRUCTION_H
#include "BoxInfo.h"
#include "Data.h"
#include "ProgramMonitor.h"
#include "Heap.h"
#include "FileList.h"
#include "BoxProgram.h"

class BoxInstruction {
public:
    BoxInstruction();
    BoxInstruction(Byte opCode, Data *firstData, Data *secondData, Size constant);

    BoxInstruction *execute(Heap &heap, FileList &fileList);
    Byte getOpCode();

    BoxInstruction *next;
    BoxInstruction *branchOf;
private:
    void findBranch();
    BoxInstruction *branch(bool statement);

    void runProgram(Data *programName);

    Data *firstData;
    Data *secondData;
    Size constant;
    Byte opCode;
};

BoxInstruction::BoxInstruction()
{
    next = null;
    branchOf = null;
}

Byte BoxInstruction::getOpCode()
{
    return opCode;
}

BoxInstruction::BoxInstruction(Byte opCode, Data *firstData, Data *secondData, Size constant)
{
    this->opCode = opCode;
    this->firstData = firstData;
    this->secondData = secondData;
    this->constant = constant;

    this->next = null;
    this->branchOf = null;
}

void BoxInstruction::findBranch()
{
    branchOf = this;

    for (Size i = 0; i < constant; i++)
    {
        if (branchOf != null)
        {
            branchOf = branchOf->next;
        }
    }
}

BoxInstruction *BoxInstruction::branch(bool statement)
{
    if (statement)
    {
        return next;
    }

    if (branchOf == null)
        findBranch();

    return branchOf->next;
}

void BoxInstruction::runProgram(Data *programName)
{
    char systemInput[BLOCK_SIZE] = { 0 };
    sprintf(systemInput, "\"%s\" \"%s\"", BOXVM_PATH, programName->getAddress());
    SETERR(system(systemInput));
}

BoxInstruction *BoxInstruction::execute(Heap &heap, FileList &fileList)
{
    switch (opCode)
    {
    case REPLOOP:
        return branchOf;
    case CMPE:
    case LOOPE:
        return branch(*firstData == *secondData);
    case CMPNE:
    case LOOPNE:
        return branch(*firstData != *secondData);
    case CMPG:
    case LOOPG:
        return branch(*firstData > *secondData);
    case CMPL:
    case LOOPL:
        return branch(*firstData < *secondData);
    case CMPGE:
    case LOOPGE:
        return branch(*firstData >= *secondData);
    case CMPLE:
    case LOOPLE:
        return branch(*firstData <= *secondData);
    case MOV:
        *firstData = *secondData;
        break;
    case ADD:
        *firstData += *secondData;
        break;
    case SUB:
        *firstData -= *secondData;
        break;
    case MUL:
        *firstData *= *secondData;
        break;
    case DIV:
        *firstData /= *secondData;
        break;
    case MOD:
        *firstData %= *secondData;
        break;
    case ADI:
        *firstData += constant;
        break;
    case SUC:
        *firstData -= constant;
        break;
    case MUC:
        *firstData *= constant;
        break;
    case DIC:
        *firstData /= constant;
        break;
    case MODC:
        *firstData %= constant;
        break;
    case SCAN:
        firstData->scan();
        break;
    case PRINT:
        firstData->print();
        break;
    case PRINTLN:
        firstData->println();
        break;
    case NEW:
        heap.allocateMemory(firstData, constant);
        break;
    case NEWV:
        heap.allocateMemory(firstData, *(Size *)secondData->getAddress());
        break;
    case FREE:
        heap.freeMemory(firstData);
        break;
    case GET:
        fileList.read(firstData, constant);
        break;
    case PUT:
        fileList.write(firstData, constant);
        break;
    case GETLINE:
        fileList.readLine(firstData, constant);
        break;
    case OPENW:
        fileList.push(constant, firstData->getAddress(), FILE_WRITE);
        break;
    case OPENR:
        fileList.push(constant, firstData->getAddress(), FILE_READ);
        break;
    case OPENA:
        fileList.push(constant, firstData->getAddress(), FILE_APPEND);
        break;
    case RAND:
        firstData->random();
        break;
    case RUN:
        runProgram(firstData);
        break;
    case ESTART:
        return null;
    default:
        SETERR(UKNOWN_OPER_ERR);
        break;
    }

    return next;
}

#endif