#ifndef BYTECODE_H
#define BYTECODE_H

#include "BoxInfo.h"

class ByteCode {
public:
	ByteCode();
	ByteCode(Bcode, Bcode);
	~ByteCode();
	Bcode ReadByteCode();
	void SetByteCode(Bcode);
	void Jump(Byte);
protected:
	Bcode bytecode;
	Bcode codesegment;
};

ByteCode::~ByteCode()
{
	if (codesegment)
		free(codesegment);
	bytecode = codesegment = null;
}

ByteCode::ByteCode()
{
	bytecode = null;
	codesegment = null;
}

ByteCode::ByteCode(Bcode _codesegment, Bcode _bytecode)
{
	bytecode = _bytecode;
	codesegment = _codesegment;
}

void ByteCode::Jump(Byte n)
{
	bytecode += n;
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
