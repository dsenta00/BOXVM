#ifndef EXECUTEMACRO_H
#define EXECUTEMACRO_H
#include "BoxInfo.h"
#include "CompareAdress.h"

enum EXECUTEMODES
{
    REGISTRYMODE    =   1,
    OPQMODE         =   2
};

#define GETADRESS(_ARG_NUM) stack.GetAdress(dataid[_ARG_NUM])
#define GETTYPE(_ARG_NUM) 	stack.GetType(dataid[_ARG_NUM])
#define POPADRESS 			opQ->Pop(type)
#define READBYTECODE 		bytecode->ReadByteCode()
#define GETREGISTRY(__OP)   status = opQ->GetRegistry(&__OP, type, *READBYTECODE);

#define FILEOP(_FOP, _TYPE) status = file_list->_FOP((_TYPE *)POPADRESS, *READBYTECODE);

#define FILEOPREG(_FOP, _TYPE)                          \
dataid[0] = *READBYTECODE;                              \
GETREGISTRY(op1)                                        \
                                                        \
if(!status)                             \
    status = file_list->_FOP((_TYPE *)op1, dataid[0]);

#define CHECKANDGETADRESS(_OP, _ARGC)               \
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

#define OPENFILE(__MODE)                            \
dataid[0] = *READBYTECODE;                          \
status = file_list->PushFile(dataid[0], GETADRESS(0), __MODE);

#define LOOPCHECKANDPUSH                            \
op1 = POPADRESS;                                    \
op2 = POPADRESS;                                    \
if(loop_list->GetStartLoop() != operation)          \
    status = loop_list->PushLoop(operation);        \
if(!status)                         \
    status = CheckStatement(op1, op2, type);

#define CMPCHECKANDPUSH                             \
op1 = POPADRESS;                                    \
op2 = POPADRESS;                                    \
status = CheckStatement(op1, op2, type);

#define LOOPCHECKANDPUSHREG                         \
GETREGISTRY(op1)                                    \
if(!status)                         \
{                                                   \
    GETREGISTRY(op2)                                \
    if(!status)                     \
    {                                               \
        if(loop_list->GetStartLoop() != operation)  \
            status = loop_list->PushLoop(operation);\
        if(!status)                 \
            status = CheckStatement(op1, op2, type);\
    }                                               \
}

#define CMPCHECKANDPUSHREG                          \
GETREGISTRY(op1)                                    \
if(!status)                         \
{                                                   \
    GETREGISTRY(op2)                                \
    if(!status)                     \
    {                                               \
        status = CheckStatement(op1, op2, type);    \
    }                                               \
}

<<<<<<< HEAD
inline void Print(Adress __ADR, Type __TYPE)
{
    switch (__TYPE)
=======
inline void Print(Adress __ADR, Type _type)
{
    switch (_type)
>>>>>>> dc573c73fbc89a1fd726f4bd7e6faffc7f3b1af8
    {
        case _CHAR:		printf("%c",    *__ADR); 			break;
        case _STRING:	printf("%s",    __ADR);             break;
        case _INT:		printf("%d",    *(int *)__ADR); 	break;
        case _SHORT:	printf("%hd",   *(short *)__ADR);	break;
        case _LONG:		printf("%ld",   *(long *)__ADR);	break;
        case _FLOAT:	printf("%f",    *(float *)__ADR);	break;
        case _DOUBLE:	printf("%lf",   *(double *)__ADR);  break;
    }
}

<<<<<<< HEAD
inline void PrintLN(Adress __ADR, Type __TYPE)
{
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    switch (__TYPE)
    {
        case _CHAR:		printf("%c\r\n",    *__ADR); 			break;
        case _STRING:	printf("%s\r\n",    __ADR);             break;
        case _INT:		printf("%d\r\n",    *(int *)__ADR); 	break;
        case _SHORT:	printf("%hd\r\n",   *(short *)__ADR);	break;
        case _LONG:		printf("%ld\r\n",   *(long *)__ADR);	break;
        case _FLOAT:	printf("%f\r\n",    *(float *)__ADR);	break;
        case _DOUBLE:	printf("%lf\r\n",   *(double *)__ADR);  break;
    }
    #else
    switch (__TYPE)
    {
        case _CHAR:		printf("%c\n",    *__ADR); 			break;
        case _STRING:	printf("%s\n",    __ADR);             break;
        case _INT:		printf("%d\n",    *(int *)__ADR); 	break;
        case _SHORT:	printf("%hd\n",   *(short *)__ADR);	break;
        case _LONG:		printf("%ld\n",   *(long *)__ADR);	break;
        case _FLOAT:	printf("%f\n",    *(float *)__ADR);	break;
        case _DOUBLE:	printf("%lf\n",   *(double *)__ADR);  break;
    }
=======
inline void Println(Adress __ADR, Type _type)
{
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        switch (_type)
        {
            case _CHAR:		printf("%c\r\n",    *__ADR); 			break;
            case _STRING:	printf("%s\r\n",    __ADR);             break;
            case _INT:		printf("%d\r\n",    *(int *)__ADR); 	break;
            case _SHORT:	printf("%hd\r\n",   *(short *)__ADR);	break;
            case _LONG:		printf("%ld\r\n",   *(long *)__ADR);	break;
            case _FLOAT:	printf("%f\r\n",    *(float *)__ADR);	break;
            case _DOUBLE:	printf("%lf\r\n",   *(double *)__ADR);  break;
        }
    #else                               \
        switch (_type)
        {
            case _CHAR:		printf("%c\n",    *__ADR);          break;
            case _STRING:	printf("%s\n",    __ADR);           break;
            case _INT:		printf("%d\n",    *(int *)__ADR); 	break;
            case _SHORT:	printf("%hd\n",   *(short *)__ADR);	break;
            case _LONG:		printf("%ld\n",   *(long *)__ADR);	break;
            case _FLOAT:	printf("%f\n",    *(float *)__ADR);	break;
            case _DOUBLE:	printf("%lf\n",   *(double *)__ADR);break;
        }
>>>>>>> dc573c73fbc89a1fd726f4bd7e6faffc7f3b1af8
    #endif
}

inline void Scan(Adress __ADR, Type __TYPE)
{
    switch (__TYPE)
    {
        case _CHAR:		scanf(" %c", __ADR); 			break;
        case _STRING:	scanf(" %s", __ADR);			break;
        case _INT:		scanf(" %d", (int *)__ADR); 	break;
        case _SHORT:	scanf(" %hd", (short *)__ADR);	break;
        case _LONG:		scanf(" %ld", (long *)__ADR);	break;
        case _FLOAT:	scanf(" %f", (float *)__ADR);	break;
        case _DOUBLE:	scanf(" %lf", (double *)__ADR); break;
    }
}

#endif // EXECUTEMACRO_H
