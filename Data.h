#ifndef DATA_H
#define DATA_H
#include "BoxInfo.h"

class Data {
public:
    Data();
    Data(Type);
    Data(Address , Type);
    Type GetType();							// --	Get variable type
    Address GetEndAddress();					// --	Get variable end address (end adr. is not part of var.)
    Status SetValue(Address);				// --	Method for initialization any type of fundamental data
    void SetExternData(Address, Type);		// --	Set new start address and type contained from heap
    Size GetSize();
    Address GetAddress();                     // --	Get variable start address
    Address GetAddress(int);
    void SetAddress(Address);
    void SetSize(Size);
protected:
    template <typename T>
    inline void Set(T *);

    Address starta;
    Address enda;
    Type type;
    Size size;
};

Data::Data()
{
    starta = enda = null;
    size = 0;
    type = 0;
}

Data::Data(Type _type)
{
    starta = enda = null;
    type = _type;
    size = 0;
}

Data::Data(Address _starta, Type _type)
{
    starta = _starta;
    type = _type;
}

template <typename T>
inline void Data::Set(T *_value)
{
    T *ptr = (T *)starta;
    *ptr = *(T *)_value;
    enda = (char *)(++ptr);
}

Status Data::SetValue(Address _value)
{
    if (_value)
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
    {
        return SET_NULL_ERR;
    }

    return EVERYTHING_OK;
}

void Data::SetExternData(Address _extrn, Type _type)
{
    starta = _extrn;
    type = _type;
}

Type Data::GetType()
{
    return type;
}

Address Data::GetAddress()
{
    return starta;
}

Address Data::GetEndAddress()
{
    return enda;
}

void Data::SetAddress(Address _address)
{
    starta = _address;
}

void Data::SetSize(Size _size)
{
    size = _size;
}

Address Data::GetAddress(int _index)
{
    if (_index < 0 || _index >= size)
    {
        return null;
    }
    else
    {
        switch (this->type)
        {
            case _CHAR:
                return HeapReturnAddress(1);
            break;
            case _INT:  case _FLOAT:
                return HeapReturnAddress(4);
            break;
            case _SHORT:
                return HeapReturnAddress(2);
            break;
            case _LONG: case _DOUBLE:
                return HeapReturnAddress(8);
            break;
            default:
                return null;
            break;
        }
    }
}

Size Data::GetSize()
{
    return size;
}


#endif // DATA_H
