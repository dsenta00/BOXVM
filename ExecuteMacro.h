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

#define OPENFILE(__MODE)\
op1 = stack.GetAddress(dataid[*READBYTECODE]);\
file_list.PushFile(dataid[0], op1, __MODE);

#define COMPARE \
GETREGISTRY(op1);\
GETREGISTRY(op2);\
dataid[0] = *READBYTECODE;\
if(EOK)\
{\
    alu.CheckStatement(op1, op2, type);\
}

#define EXITLOOPIF(__STAT) COMPARE \
if (__STAT)\
{\
    bytecode->Jump(dataid[0]);\
    loop_list.PopLoop();\
}\
else if(loop_list.GetStartLoop() != operation)\
{\
    loop_list.PushLoop(operation);\
}

#define BRANCHIF(__STAT) COMPARE \
if (__STAT)\
{\
    bytecode->Jump(dataid[0]);\
}

#endif // EXECUTEMACRO_H
