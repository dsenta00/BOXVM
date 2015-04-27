#ifndef ARITMETHICALOPERATIONS_H
#define ARITMETHICALOPERATIONS_H
#include "BoxInfo.h"
#include "ProgramMonitor.h"

class ALU {
public:
    ALU();
    void SetMonitor(ProgramMonitor *);
    template <typename T>
    inline void AddOperation(T *, T *);
    template <typename T>
    inline void AddOperation(T *, Byte);
    template <typename T>
    inline void SubOperation(T *, T *);
    template <typename T>
    inline void SubOperation(T *, Byte);
    template <typename T>
    inline void MulOperation(T *, T *);
    template <typename T>
    inline void MulOperation(T *, Byte);
    template <typename T>
    inline void DivOperation(T *, T *);
    template <typename T>
    inline void DivOperation(T *, Byte);
    template <typename T>
    inline void ModOperation(T *, T *);
    template <typename T>
    inline void ModOperation(T *, Byte);
    template <typename T>
    inline void MovOperation(T *, T *);
    template <typename T>
    inline void CheckAdressEquality(T *, T *);
    void CheckStatement(Adress, Adress, Type);
    inline void Print(Adress, Type);
    inline void Rand(Adress, Type);
    inline void PrintLN(Adress, Type);
    inline void Scan(Adress, Type);
    void Operation(Byte, Adress, Byte, Type);
    void Operation(Byte, Adress, Adress, Type);

    long GetFlag();
protected:
    ProgramMonitor *monitor;
    char p_itoa[11];
    long flag;
};

ALU::ALU()
{
    memset(this, null, sizeof(ALU));
}

long ALU::GetFlag()
{
    return flag;
}

template <typename T>
inline void ALU::CheckAdressEquality(T *adress1, T* adress2)
{
    flag = (long)(*adress1 - *adress2);
}

void ALU::CheckStatement(Adress adress1, Adress adress2, Type type)
{
    if(adress1 && adress2)
    {
        switch (type)
        {
            case _CHAR:
                CheckAdressEquality(adress1, adress2);
            break;
            case _INT:
                CheckAdressEquality((int *)adress1, (int *)adress2);
            break;
            case _SHORT:
                CheckAdressEquality((short *)adress1, (short *)adress2);
            break;
            case _LONG:
                CheckAdressEquality((long *)adress1, (long *)adress2);
            break;
            case _FLOAT:
                CheckAdressEquality((float *)adress1, (float *)adress2);
            break;
            case _DOUBLE:
                CheckAdressEquality((double *)adress1, (double *)adress2);
            break;
            case _STRING:
                flag = strcmp(adress1, adress2);
            break;
        }
    }
    else
    {
        SETERR(ADR_COMP_ERR);
    }
}

inline void ALU::Print(Adress __ADR, Type __TYPE)
{
    switch (__TYPE)
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

inline void ALU::PrintLN(Adress __ADR, Type __TYPE)
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
    #endif
}

inline void ALU::Scan(Adress __ADR, Type __TYPE)
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

inline void ALU::Rand(Adress __ADR, Type __TYPE)
{
    int randnum = rand();

    switch (__TYPE)
    {
        case _CHAR:
            *__ADR = randnum % 128;
        break;
        case _STRING:
            sprintf(__ADR, "%d", randnum);
        break;
        case _SHORT:
            *(short *)__ADR = randnum % 32768;
        break;
        case _INT:
            *(int *)__ADR = randnum;
        break;
        case _LONG:
            *(long *)__ADR = randnum;
        break;
        case _FLOAT:
            *(float *)__ADR = randnum;
        break;
        case _DOUBLE:
            *(double *)__ADR = randnum;
        break;
    }
}

void ALU::SetMonitor(ProgramMonitor *_monitor)
{
    monitor = _monitor;
}

template <typename T>
inline void ALU::AddOperation(T *operand1, T *operand2)
{
    *operand1 += *operand2;
}

template <typename T>
inline void ALU::AddOperation(T *operand1, Byte increment)
{
    *operand1 += increment;
}

template <typename T>
inline void ALU::SubOperation(T *operand1, T *operand2)
{
    *operand1 -= *operand2;
}

template <typename T>
inline void ALU::SubOperation(T *operand1, Byte increment)
{
    *operand1 -= increment;
}

template <typename T>
inline void ALU::MulOperation(T *operand1, T *operand2)
{
    *operand1 *= *operand2;
}

template <typename T>
inline void ALU::MulOperation(T *operand1, Byte increment)
{
    *operand1 *= increment;
}

template <typename T>
inline void ALU::DivOperation(T *operand1, T *operand2)
{
    if (*operand2)
    {
        *operand1 /= *operand2;
    }
    else
    {
        SETERR(DIV_NULL_ERR);
    }
}

template <typename T>
inline void ALU::DivOperation(T *operand1, Byte increment)
{
    *operand1 /= increment;
}

template <typename T>
inline void ALU::ModOperation(T *operand1, T *operand2)
{
    if (*operand2)
    {
        *operand1 %= *operand2;
    }
    else
    {
        SETERR(DIV_NULL_ERR);
    }
}

template <typename T>
inline void ALU::ModOperation(T *operand1, Byte increment)
{
    *operand1 %= increment;
}

template <typename T>
inline void ALU::MovOperation(T *operand1, T *operand2)
{
    *operand1 = *operand2;
}

inline void ALU::Operation(Byte OP, Adress store_adress, Adress adress, Type type)
{
    if(store_adress && adress)
    {
        if (OP == MOV)
        {
            switch (type)
            {
                case _CHAR:
                    MovOperation(store_adress, adress);
                break;
                case _INT:
                    MovOperation((int *)store_adress, (int *)adress);
                break;
                case _SHORT:
                    MovOperation((short *)store_adress, (short *)adress);
                break;
                case _LONG:
                    MovOperation((long *)store_adress, (long *)adress);
                break;
                case _FLOAT:
                    MovOperation((float *)store_adress, (float *)adress);
                break;
                case _DOUBLE:
                    MovOperation((double *)store_adress, (double *)adress);
                break;
                case _STRING:
                    strcpy(store_adress, adress);
                break;
            }
        }
        else if (OP == ADD)
        {
            switch (type)
            {
                case _CHAR:
                    AddOperation(store_adress, adress);
                break;
                case _INT:
                    AddOperation((int *)store_adress, (int *)adress);
                break;
                case _SHORT:
                    AddOperation((short *)store_adress, (short *)adress);
                break;
                case _LONG:
                    AddOperation((long *)store_adress, (long *)adress);
                break;
                case _FLOAT:
                    AddOperation((float *)store_adress, (float *)adress);
                break;
                case _DOUBLE:
                    AddOperation((double *)store_adress, (double *)adress);
                break;
                case _STRING:
                    strcat(store_adress, adress);
                break;
            }
        }
        else if (OP == MUL)
        {
            switch (type)
            {
                case _CHAR:
                    MulOperation(store_adress, adress);
                break;
                case _INT:
                    MulOperation((int *)store_adress, (int *)adress);
                break;
                case _SHORT:
                    MulOperation((short *)store_adress, (short *)adress);
                break;
                case _LONG:
                    MulOperation((long *)store_adress, (long *)adress);
                break;
                case _FLOAT:
                    MulOperation((float *)store_adress, (float *)adress);
                break;
                case _DOUBLE:
                    MulOperation((double *)store_adress, (double *)adress);
                break;
            }
        }
        else if (OP == DIV)
        {
            switch (type)
            {
                case _CHAR:
                    DivOperation(store_adress, adress);
                break;
                case _INT:
                    DivOperation((int *)store_adress, (int *)adress);
                break;
                case _SHORT:
                    DivOperation((short *)store_adress, (short *)adress);
                break;
                case _LONG:
                    DivOperation((long *)store_adress, (long *)adress);
                break;
                case _FLOAT:
                    DivOperation((float *)store_adress, (float *)adress);
                break;
                case _DOUBLE:
                    DivOperation((double *)store_adress, (double *)adress);
                break;
            }
        }
        else if (OP == SUB)
        {
            switch (type)
            {
                case _CHAR:
                    SubOperation(store_adress, adress);
                break;
                case _INT:
                    SubOperation((int *)store_adress, (int *)adress);
                break;
                case _SHORT:
                    SubOperation((short *)store_adress, (short *)adress);
                break;
                case _LONG:
                    SubOperation((long *)store_adress, (long *)adress);
                break;
                case _FLOAT:
                    SubOperation((float *)store_adress, (float *)adress);
                break;
                case _DOUBLE:
                    SubOperation((double *)store_adress, (double *)adress);
                break;
            }
        }
        else if (OP == MOD)
        {
            switch (type)
            {
                case _CHAR:
                    ModOperation(store_adress, adress);
                break;
                case _INT:
                    ModOperation((int *)store_adress, (int *)adress);
                break;
                case _SHORT:
                    ModOperation((short *)store_adress, (short *)adress);
                break;
                case _LONG:
                    ModOperation((long *)store_adress, (long *)adress);
                break;
            }
        }
    }
    else
    {
        SETERR(OPER_NULL_ERR);
    }
}

void ALU::Operation(Byte OP, Adress store_adress, Byte increment, Type type)
{
    if(store_adress)
    {
        if (OP == ADI)
        {
            switch (type)
            {
                case _CHAR:
                    AddOperation(store_adress, increment);
                break;
                case _INT:
                    AddOperation((int *)store_adress, increment);
                break;
                case _SHORT:
                    AddOperation((short *)store_adress, increment);
                break;
                case _LONG:
                    AddOperation((long *)store_adress, increment);
                break;
                case _FLOAT:
                    AddOperation((float *)store_adress, increment);
                break;
                case _DOUBLE:
                    AddOperation((double *)store_adress, increment);
                break;
                case _STRING:
                    sprintf(p_itoa, "%d", (int)increment);
                    strcat(store_adress, p_itoa);
                break;
            }
        }
        else if (OP == MUC)
        {
            switch (type)
            {
                case _CHAR:
                    MulOperation(store_adress, increment);
                break;
                case _INT:
                    MulOperation((int *)store_adress, increment);
                break;
                case _SHORT:
                    MulOperation((short *)store_adress, increment);
                break;
                case _LONG:
                    MulOperation((long *)store_adress, increment);
                break;
                case _FLOAT:
                    MulOperation((float *)store_adress, increment);
                break;
                case _DOUBLE:
                    MulOperation((double *)store_adress, increment);
                break;
            }
        }
        else if (OP == DIC)
        {
            switch (type)
            {
                case _CHAR:
                    DivOperation(store_adress, increment);
                break;
                case _INT:
                    DivOperation((int *)store_adress, increment);
                break;
                case _SHORT:
                    DivOperation((short *)store_adress, increment);
                break;
                case _LONG:
                    DivOperation((long *)store_adress, increment);
                break;
                case _FLOAT:
                    DivOperation((float *)store_adress, increment);
                break;
                case _DOUBLE:
                    DivOperation((double *)store_adress, increment);
                break;
            }
        }
        else if (OP == SUC)
        {
            if(increment)
            {
                switch (type)
                {
                    case _CHAR:
                        SubOperation(store_adress, increment);
                    break;
                    case _INT:
                        SubOperation((int *)store_adress, increment);
                    break;
                    case _SHORT:
                        SubOperation((short *)store_adress, increment);
                    break;
                    case _LONG:
                        SubOperation((long *)store_adress, increment);
                    break;
                    case _FLOAT:
                        SubOperation((float *)store_adress, increment);
                    break;
                    case _DOUBLE:
                        SubOperation((double *)store_adress, increment);
                    break;
                }
            }
            else
            {
                SETERR(DIV_NULL_ERR);
            }
        }
        else if (OP == MODC)
        {
            if(increment)
            {
                switch (type)
                {
                    case _CHAR:
                        ModOperation(store_adress, increment);
                    break;
                    case _INT:
                        ModOperation((int *)store_adress, increment);
                    break;
                    case _SHORT:
                        ModOperation((short *)store_adress, increment);
                    break;
                    case _LONG:
                        ModOperation((long *)store_adress, increment);
                    break;
                }
            }
            else
            {
                SETERR(DIV_NULL_ERR);
            }
        }
    }
    else
    {
        SETERR(OPER_NULL_ERR);
    }

}

#endif // ARITMETHICALOPERATIONS_H
