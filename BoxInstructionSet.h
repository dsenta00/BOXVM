#ifndef BOX_INSTRUCTION_SET_H
#define BOX_INSTRUCTION_SET_H
#include "BoxInfo.h"
#include "BoxInstruction.h"
#include "OperationFormat.h"
#include "Data.h"
#include "Heap.h"
#include "Stack.h"

class BoxInstructionSet {
public:
    BoxInstructionSet();
    void add(OperationFormat *opFormat, Heap &heap, Stack &stack);
    void execute(Heap &heap);
    ~BoxInstructionSet();
private:

    BoxInstruction *getLoopStart();
    void decodeOperation(OperationFormat *opFormat, Data_p &data1, Data_p &data2, Size &constant, Stack &stack, Heap &heap);

    BoxInstruction *last;
    BoxInstruction head;
};

BoxInstructionSet::BoxInstructionSet()
{
    last = &head;
}

void BoxInstructionSet::add(OperationFormat *opFormat, Heap &heap, Stack &stack)
{
    Data_p data1;
    Data_p data2;
    Size constant;
    BoxInstruction *instruction;

    decodeOperation(opFormat, data1, data2, constant, stack, heap);

    instruction = new BoxInstruction(opFormat->opCode, data1, data2, constant);

    last->next = instruction;
    last = instruction;

    if (opFormat->opCode == REPLOOP)
    {
        instruction->branchOf = getLoopStart();
    }
}

BoxInstructionSet::~BoxInstructionSet()
{
    for (BoxInstruction *del = head.next;
        head.next != null;
        del = head.next)
    {
        head.next = del->next;
        delete del;
    }
}

void BoxInstructionSet::execute(Heap &heap)
{
    FileList fileList;
    BoxInstruction *instruction = head.next;

    do
    {
        instruction = instruction->execute(heap, fileList);
    } while (EOK && instruction != null);
}

BoxInstruction *BoxInstructionSet::getLoopStart()
{
    std::list<BoxInstruction *> stack;

    for (BoxInstruction *instruction = head.next;
        instruction->next != null;
        instruction = instruction->next)
    {
        switch (instruction->getOpCode())
        {
        case LOOPE:
        case LOOPNE:
        case LOOPG:
        case LOOPGE:
        case LOOPL:
        case LOOPLE:
            stack.push_front(instruction);
            break;
        case REPLOOP:
            stack.pop_front();
            break;
        }
    }

    return *stack.begin();
}

void BoxInstructionSet::decodeOperation(OperationFormat *opFormat, Data_p &data1, Data_p &data2, Size &constant, Stack &stack, Heap &heap)
{
    constant = opFormat->constant;

    if (opFormat->data1 != null)
    {
        data1 = stack.find(opFormat->data1);
    }

    if (opFormat->data2 != null)
    {
        data2 = stack.find(opFormat->data2);
    }

    if (opFormat->ptr != null)
    {
        data1 = heap.find(opFormat->ptr);
    }
}

#endif