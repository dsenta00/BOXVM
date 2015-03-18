#ifndef EXECUTEMACRO_H
#define EXECUTEMACRO_H
#include "BoxInfo.h"
#include "CompareAdress.h"

#define GETADRESS(_ARG_NUM) stack.GetAdress(dataid[_ARG_NUM])
#define GETTYPE(_ARG_NUM) 	stack.GetType(dataid[_ARG_NUM])
#define POPADRESS 			op_queue->Pop(type)
#define READBYTECODE 		bytecode->ReadByteCode()

#define FILEOP(_FOP, _TYPE)                             \
    dataid[0] = *READBYTECODE;                          \
    status = file_list->_FOP((_TYPE *)op1, dataid[0]);

#define CHECKANDGETADRESS(_OP, _ARGC)                   \
    if(dataid[_ARGC] == -2)                             \
        _OP = POPADRESS;                                \
    else                                                \
    {                                                   \
        _OP = GETADRESS(_ARGC);                         \
        type = GETTYPE(_ARGC);                          \
                                                        \
        if(type == _CHAR)                               \
            type = _STRING;                             \
    }

#define LOOPCHECKANDPUSH                                \
    op1 = POPADRESS;                                    \
    op2 = POPADRESS;                                    \
    if(loop_list->GetStartLoop() != operation)          \
        status = loop_list->PushLoop(operation);        \
    if(status == EVERYTHING_OK)                         \
        status = CheckStatement(op1, op2, type);


#define CMPCHECKANDPUSH                                 \
    op1 = POPADRESS;                                    \
    op2 = POPADRESS;                                    \
    status = CheckStatement(op1, op2, type);


#define PRINTOP(__ADR, __TYPE)                                    	\
    switch (__TYPE)                                               	\
    {                                                             	\
        case _CHAR:		printf("%c",    *__ADR); 			break;	\
        case _STRING:	printf("%s",    __ADR);             break;	\
        case _INT:		printf("%d",    *(int *)__ADR); 	break;	\
        case _SHORT:	printf("%hd",   *(short *)__ADR);	break;	\
        case _LONG:		printf("%ld",   *(long *)__ADR);	break;	\
        case _FLOAT:	printf("%f",    *(float *)__ADR);	break;	\
        case _DOUBLE:	printf("%lf",   *(double *)__ADR);  break;	\
    }

#define SCANOP(__ADR, __TYPE)                                 	\
    switch (__TYPE)                                           	\
    {                                                         	\
        case _CHAR:		scanf(" %c", __ADR); 			break;	\
        case _STRING:	scanf(" %s", __ADR);			break;	\
        case _INT:		scanf(" %d", (int *)__ADR); 	break;	\
        case _SHORT:	scanf(" %hd", (short *)__ADR);	break;	\
        case _LONG:		scanf(" %ld", (long *)__ADR);	break;	\
        case _FLOAT:	scanf(" %f", (float *)__ADR);	break;	\
        case _DOUBLE:	scanf(" %lf", (double *)__ADR); break;	\
    }

#endif // EXECUTEMACRO_H
