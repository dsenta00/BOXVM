#ifndef POINTER_H
#define POINTER_H

#include "BoxInfo.h"

class Pointer
{
	Adress starta;
	Type type;
	Size size;
public:
	Pointer();
	Pointer(Type);

	Size GetSize();
	Type GetType();
	Adress GetAdress(int);
	Adress GetAdress();
	void SetAdress(Adress);
	void SetSize(Size);
};

Pointer::Pointer()
{
	starta = NULL;
	type = 0;
	size = 0;
}

Pointer::Pointer(Type _type)
{
	starta = NULL;
	type = _type;
	size = 0;
}

void Pointer::SetAdress(Adress _adress)
{
	starta = _adress;
}

void Pointer::SetSize(Size _size)
{
	size = _size;
}

Adress Pointer::GetAdress(int _index)
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

Adress Pointer::GetAdress()
{
	return starta;
}

Size Pointer::GetSize()
{
	return size;
}

Type Pointer::GetType()
{
	return type;
}


#endif
