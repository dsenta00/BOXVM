#ifndef BYTECODE_H
#define BYTECODE_H

#include "BoxInfo.h"

class ByteCode
{
	Bcode bytecode;
	Bcode codesegment;
public:
	ByteCode();
	ByteCode(Bcode, Bcode);
	~ByteCode();

	Bcode ReadByteCode();
	void SetByteCode(Bcode);
	void SkipByteCode(Size);
};

ByteCode::~ByteCode()
{
	if (codesegment)
		free(codesegment);
	bytecode = codesegment = NULL;
}

ByteCode::ByteCode()
{
	bytecode = NULL;
	codesegment = NULL;
}

ByteCode::ByteCode(Bcode _codesegment, Bcode _bytecode)
{
	bytecode = _bytecode;
	codesegment = _codesegment;
}

void ByteCode::SkipByteCode(Size n)
{
	do
	{
		switch (*bytecode)
		{
            case ADD: case MUL: case DIV: case SUB: case RAND:
            case SCAN: case PRINT: case PRINTLN: case MOD: case REPLOOP:
                bytecode++;
            break;
            case MOV: case LEAC: case LEA:
            case FNEW: case NEW: case NEWV: case FNEWV:
                bytecode += 3;
            break;
            default:
                bytecode += 2;
            break;
		}

		n--;

	} while (n > 0);

	bytecode--;
}

Bcode ByteCode::ReadByteCode()
{
	return ++bytecode;
}

void ByteCode::SetByteCode(Bcode adress)
{
	bytecode = adress;
}

#endif
