#ifndef DATA_H
#define DATA_H
#include "BoxInfo.h"

class Data {
public:
    Data();
    Data(Type);
    Data(Adress , Type);
    Type GetType();							// --	Get variable type
    Adress GetEndAdress();					// --	Get variable end adress (end adr. is not part of var.)
    Status SetValue(Adress);				// --	Method for initialization any type of fundamental data
    void SetExternData(Adress, Type);		// --	Set new start adress and type contained from heap
    Size GetSize();
    Adress GetAdress();                     // --	Get variable start adress
    Adress GetAdress(int);
    void SetAdress(Adress);
    void SetSize(Size);
protected:
    template <typename T>
    inline void Set(T *);

    Adress starta;
    Adress enda;
    Type type;
    Size size;
};

Data::Data()
{
    starta = enda = NULL;
    size = 0;
    type = 0;
}

Data::Data(Type _type)
{
    starta = enda = NULL;
    type = _type;
    size = 0;
}

Data::Data(Adress _starta, Type _type)
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

Status Data::SetValue(Adress _value)
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
        return SET_NULL_ERR;

    return EVERYTHING_OK;
}

void Data::SetExternData(Adress _extrn, Type _type)
{
    starta = _extrn;
    type = _type;
}

Type Data::GetType()
{
    return type;
}

Adress Data::GetAdress()
{
    return starta;
}

Adress Data::GetEndAdress()
{
    return enda;
}

void Data::SetAdress(Adress _adress)
{
    starta = _adress;
}

void Data::SetSize(Size _size)
{
    size = _size;
}

Adress Data::GetAdress(int _index)
{
    if (_index < 0 || _index >= size)
        return NULL;
    else
    {
        switch (this->type)
        {
            case _CHAR:
                return HeapReturnAdress(1);
            break;
            case _INT:  case _FLOAT:
                return HeapReturnAdress(4);
            break;
            case _SHORT:
                return HeapReturnAdress(2);
            break;
            case _LONG: case _DOUBLE:
                return HeapReturnAdress(8);
            break;
            default:
                return NULL;
            break;
        }
    }
}

Size Data::GetSize()
{
    return size;
}


#endif // DATA_H
