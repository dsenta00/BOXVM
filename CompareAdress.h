#ifndef COMPAREADRESS_H
#define COMPAREADRESS_H
#include "BoxInfo.h"

template <typename T>
inline int CheckAdressEquality(T *adress1, T* adress2)
{
    if (adress1 != NULL && adress2 != NULL)
    {
        if (*adress1 == *adress2)
            return AREEQUAL;
        else if (*adress1 > *adress2)
            return FIRSTBIGGER;
        else
            return SECONDBIGGER;
    }
    else
        return ADR_COMP_ERR;
}

int CheckStatement(Adress adress1, Adress adress2, Type type)
{
    static int strcmp_res = 0;

    switch (type)
    {
        case _CHAR:
            return CheckAdressEquality(adress1, adress2);
        break;
        case _INT:
            return CheckAdressEquality((int *)adress1, (int *)adress2);
        break;
        case _SHORT:
            return CheckAdressEquality((short *)adress1, (short *)adress2);
        break;
        case _LONG:
            return CheckAdressEquality((long *)adress1, (long *)adress2);
        break;
        case _FLOAT:
            return CheckAdressEquality((float *)adress1, (float *)adress2);
        break;
        case _DOUBLE:
            return CheckAdressEquality((double *)adress1, (double *)adress2);
        break;
        case _STRING:
            strcmp_res = strcmp(adress1, adress2);

            if (strcmp_res < 0)
                return SECONDBIGGER;
            else if(strcmp_res > 0)
                return FIRSTBIGGER;
            else
                return AREEQUAL;
        break;
        default:
            return ADR_COMP_ERR;
        break;
    }
}

#endif // COMPAREADRESS_H
