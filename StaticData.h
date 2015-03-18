#ifndef STATICDATA_H
#define STATICDATA_H

#include "BoxInfo.h"

class StaticData
{
    Adress starta;
    Adress enda;
    Type type;

    template <typename T> inline void Set(T *);
public:
	StaticData();
    StaticData(Adress , Type);

    Type GetType();							// --	Get variable type
    Adress GetStartAdress();					// --	Get variable start adress
    Adress GetEndAdress();					// --	Get variable end adress (end adr. is not part of var.)
    Status SetValue(Adress);				// --	Method for initialization any type of fundamental data
    void SetExternData(Adress, Type);		// --	Set new start adress and type contained from heap
};

StaticData::StaticData()
{
    starta = enda = NULL;
	type = 0;
}

StaticData::StaticData(Adress _starta, Type _type)
{
    starta = _starta;
	type = _type;
}

template <typename T>
inline void StaticData::Set(T *_value)
{
    T *ptr = (T *)starta;
	*ptr = *(T *)_value;
    enda = (char *)(++ptr);
}

Status StaticData::SetValue(Adress _value)
{
	if (_value != NULL)
	{
		switch (type)
		{
			case _CHAR:
				Set(_value);
			break;
			case _INT:
				Set((int *)_value);
			break;
			case _SHORT:
				Set((short *)_value);
			break;
			case _LONG:
				Set((long *)_value);
			break;
			case _FLOAT:
				Set((float *)_value);
			break;
			case _DOUBLE:
				Set((double *)_value);
			break;
			case _STRING:
                strcpy(starta, _value);
                enda = starta;
                enda = strchr(enda, '\0');
                enda++;
			break;
			default:
				return UKNOWN_TYPE_ERR;
			break;
		}
	}
	else
		return SET_NULL_ERR;

	return EVERYTHING_OK;
}

void StaticData::SetExternData(Adress _extrn, Type _type)
{
    starta = _extrn;
	type = _type;
}

Type StaticData::GetType()
{
	return type;
}

Adress StaticData::GetStartAdress()
{
    return starta;
}

Adress StaticData::GetEndAdress()
{
    return enda;
}

#endif
