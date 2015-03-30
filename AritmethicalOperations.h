#ifndef ARITMETHICALOPERATIONS_H
#define ARITMETHICALOPERATIONS_H
#include "BoxInfo.h"

template <typename T>
inline Status AddOperation(T *operand1, T *operand2)
{
	if (operand1 && operand2)
		*operand1 += *operand2;
	else
		return OPER_NULL_ERR;

	return EVERYTHING_OK;
}

template <typename T>
inline Status AddOperation(T *operand1, Size increment)
{
	if (operand1)
		*operand1 += increment;
	else
		return OPER_NULL_ERR;

	return EVERYTHING_OK;
}

template <typename T>
inline Status SubOperation(T *operand1, T *operand2)
{
	if (operand1 && operand2)
		*operand1 -= *operand2;
	else
		return OPER_NULL_ERR;

	return EVERYTHING_OK;
}

template <typename T>
inline Status SubOperation(T *operand1, Size increment)
{
	if (operand1)
		*operand1 -= increment;
	else
		return OPER_NULL_ERR;

	return EVERYTHING_OK;
}

template <typename T>
inline Status MulOperation(T *operand1, T *operand2)
{
	if (operand1 && operand2)
		*operand1 *= *operand2;
	else
		return OPER_NULL_ERR;

	return EVERYTHING_OK;
}

template <typename T>
inline Status MulOperation(T *operand1, Size increment)
{
	if (operand1)
		*operand1 *= increment;
	else
		return OPER_NULL_ERR;

	return EVERYTHING_OK;
}

template <typename T>
inline Status DivOperation(T *operand1, T *operand2)
{
	if (operand1 && operand2)
	{
		if (*operand2)
			*operand1 /= *operand2;
		else
			return DIV_NULL_ERR;
	}
	else
		return OPER_NULL_ERR;

	return EVERYTHING_OK;
}

template <typename T>
inline Status DivOperation(T *operand1, Size increment)
{
	if (operand1)
	{
		if (increment)
			*operand1 /= increment;
		else
			return DIV_NULL_ERR;
	}
	else
		return OPER_NULL_ERR;

	return EVERYTHING_OK;
}

template <typename T>
inline Status ModOperation(T *operand1, T *operand2)
{
	if (operand1 && operand2)
	{
		if (*operand2)
			*operand1 %= *operand2;
		else
			return DIV_NULL_ERR;
	}
	else
		return OPER_NULL_ERR;

	return EVERYTHING_OK;
}

template <typename T>
inline Status ModOperation(T *operand1, Size increment)
{
	if (operand1)
    {
        if (increment)
            *operand1 %= increment;
        else
            return DIV_NULL_ERR;
    }
	else
		return OPER_NULL_ERR;

	return EVERYTHING_OK;
}

template <typename T>
inline Status MovOperation(T *operand1, T *operand2)
{
	if (operand1 && operand2)
		*operand1 = *operand2;
	else
		return STACK_SET_ERR;

	return EVERYTHING_OK;
}

Status Operation(char OP, Adress store_adress, Adress adress, Type type)
{
	if (OP == MOV)
	{
		switch (type)
		{
            case _CHAR:
                return MovOperation(store_adress, adress);
            break;
            case _INT:
                return MovOperation((int *)store_adress, (int *)adress);
            break;
            case _SHORT:
                return MovOperation((short *)store_adress, (short *)adress);
            break;
            case _LONG:
                return MovOperation((long *)store_adress, (long *)adress);
            break;
            case _FLOAT:
                return MovOperation((float *)store_adress, (float *)adress);
            break;
            case _DOUBLE:
                return MovOperation((double *)store_adress, (double *)adress);
            break;
            case _STRING:
                if (store_adress && adress)
                    strcpy(store_adress, adress);
                else
                    return OPER_NULL_ERR;
                return EVERYTHING_OK;
            break;
		}
	}
	else if (OP == ADD)
	{
		switch (type)
		{
            case _CHAR:
                return AddOperation(store_adress, adress);
            break;
            case _INT:
                return AddOperation((int *)store_adress, (int *)adress);
            break;
            case _SHORT:
                return AddOperation((short *)store_adress, (short *)adress);
            break;
            case _LONG:
                return AddOperation((long *)store_adress, (long *)adress);
            break;
            case _FLOAT:
                return AddOperation((float *)store_adress, (float *)adress);
            break;
            case _DOUBLE:
                return AddOperation((double *)store_adress, (double *)adress);
            break;
            case _STRING:
                if (store_adress && adress)
                    strcat(store_adress, adress);
                else
                    return OPER_NULL_ERR;
                return EVERYTHING_OK;
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
                return MulOperation((int *)store_adress, (int *)adress);
            break;
            case _SHORT:
                return MulOperation((short *)store_adress, (short *)adress);
            break;
            case _LONG:
                return MulOperation((long *)store_adress, (long *)adress);
            break;
            case _FLOAT:
                return MulOperation((float *)store_adress, (float *)adress);
            break;
            case _DOUBLE:
                return MulOperation((double *)store_adress, (double *)adress);
            break;
		}
	}
	else if (OP == DIV)
	{
		switch (type)
		{
            case _CHAR:
                return DivOperation(store_adress, adress);
            break;
            case _INT:
                return DivOperation((int *)store_adress, (int *)adress);
            break;
            case _SHORT:
                return DivOperation((short *)store_adress, (short *)adress);
            break;
            case _LONG:
                return DivOperation((long *)store_adress, (long *)adress);
            break;
            case _FLOAT:
                return DivOperation((float *)store_adress, (float *)adress);
            break;
            case _DOUBLE:
                return DivOperation((double *)store_adress, (double *)adress);
            break;
		}
	}
	else if (OP == SUB)
	{
		switch (type)
		{
            case _CHAR:
                return SubOperation(store_adress, adress);
            break;
            case _INT:
                return SubOperation((int *)store_adress, (int *)adress);
            break;
            case _SHORT:
                return SubOperation((short *)store_adress, (short *)adress);
            break;
            case _LONG:
                return SubOperation((long *)store_adress, (long *)adress);
            break;
            case _FLOAT:
                return SubOperation((float *)store_adress, (float *)adress);
            break;
            case _DOUBLE:
                return SubOperation((double *)store_adress, (double *)adress);
            break;
		}
	}
	else if (OP == MOD)
	{
		switch (type)
		{
            case _CHAR:
                return ModOperation(store_adress, adress);
            break;
            case _INT:
                return ModOperation((int *)store_adress, (int *)adress);
            break;
            case _SHORT:
                return ModOperation((short *)store_adress, (short *)adress);
            break;
            case _LONG:
                return ModOperation((long *)store_adress, (long *)adress);
            break;
		}
	}

	return UKNOWN_OPER_ERR;
}

Status Operation(char OP, Adress store_adress, Size increment, Type type)
{
	static char p_itoa[11] = { 0 };

	if (OP == ADI)
	{
		switch (type)
		{
            case _CHAR:
                return AddOperation(store_adress, increment);
            break;
            case _INT:
                return AddOperation((int *)store_adress, increment);
            break;
            case _SHORT:
                return AddOperation((short *)store_adress, increment);
            break;
            case _LONG:
                return AddOperation((long *)store_adress, increment);
            break;
            case _FLOAT:
                return AddOperation((float *)store_adress, increment);
            break;
            case _DOUBLE:
                return AddOperation((double *)store_adress, increment);
            break;
            case _STRING:
                sprintf(p_itoa, "%d", (int)increment);

                if (store_adress)
                    strcat(store_adress, p_itoa);
                else
                    return OPER_NULL_ERR;
                return EVERYTHING_OK;
            break;
		}
	}
	else if (OP == MUC)
	{
		switch (type)
		{
            case _CHAR:
                return MulOperation(store_adress, increment);
            break;
            case _INT:
                return MulOperation((int *)store_adress, increment);
            break;
            case _SHORT:
                return MulOperation((short *)store_adress, increment);
            break;
            case _LONG:
                return MulOperation((long *)store_adress, increment);
            break;
            case _FLOAT:
                return MulOperation((float *)store_adress, increment);
            break;
            case _DOUBLE:
                return MulOperation((double *)store_adress, increment);
            break;
		}
	}
	else if (OP == DIC)
	{
		switch (type)
		{
            case _CHAR:
                return DivOperation(store_adress, increment);
            break;
            case _INT:
                return DivOperation((int *)store_adress, increment);
            break;
            case _SHORT:
                return DivOperation((short *)store_adress, increment);
            break;
            case _LONG:
                return DivOperation((long *)store_adress, increment);
            break;
            case _FLOAT:
                return DivOperation((float *)store_adress, increment);
            break;
            case _DOUBLE:
                return DivOperation((double *)store_adress, increment);
            break;
		}
	}
	else if (OP == SUC)
	{
		switch (type)
		{
            case _CHAR:
                return SubOperation(store_adress, increment);
            break;
            case _INT:
                return SubOperation((int *)store_adress, increment);
            break;
            case _SHORT:
                return SubOperation((short *)store_adress, increment);
            break;
            case _LONG:
                return SubOperation((long *)store_adress, increment);
            break;
            case _FLOAT:
                return SubOperation((float *)store_adress, increment);
            break;
            case _DOUBLE:
                return SubOperation((double *)store_adress, increment);
            break;
		}
	}
	else if (OP == MODC)
	{
		switch (type)
		{
            case _CHAR:
                return ModOperation(store_adress, increment);
            break;
            case _INT:
                return ModOperation((int *)store_adress, increment);
            break;
            case _SHORT:
                return ModOperation((short *)store_adress, increment);
            break;
            case _LONG:
                return ModOperation((long *)store_adress, increment);
            break;
		}
	}

	return UKNOWN_OPER_ERR;
}

#endif // ARITMETHICALOPERATIONS_H
