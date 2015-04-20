#ifndef EXECUTEMACRO_H
#define EXECUTEMACRO_H
#include "BoxInfo.h"

#define GETADRESS(_ARG_NUM) stack.GetAdress(dataid[_ARG_NUM])
#define GETTYPE(_ARG_NUM) 	stack.GetType(dataid[_ARG_NUM])
#define READBYTECODE 		bytecode->ReadByteCode()
#define GETREGISTRY(__OP)   registry.GetRegistry(__OP, type, *READBYTECODE);

#define FILEOPREG(_FOP, _TYPE)                          \
dataid[0] = *READBYTECODE;                              \
GETREGISTRY(op1)                                        \
                                                        \
if(EOK)                                                 \
    file_list._FOP((_TYPE *)op1, dataid[0]);

#define OPENFILE(__MODE)                            \
dataid[0] = *READBYTECODE;                          \
file_list.PushFile(dataid[0], GETADRESS(0), __MODE);

#define LOOPCHECKANDPUSHREG                         \
GETREGISTRY(op1)\
GETREGISTRY(op2)                                \
if(EOK)                     \
{                                               \
    if(loop_list.GetStartLoop() != operation)  \
        loop_list.PushLoop(operation);\
    if(EOK)                 \
        alu.CheckStatement(op1, op2, type);\
}

#define CMPCHECKANDPUSHREG                          \
GETREGISTRY(op1)\
GETREGISTRY(op2)                                \
if(EOK)                     \
{                                               \
    alu.CheckStatement(op1, op2, type);    \
}

#endif // EXECUTEMACRO_H
