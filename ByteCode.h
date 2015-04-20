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
/*
inline bool Check(Byte &i)
{
    if(i >= 0 && i <= MAXBUFFERSIZE)
        return true;
    else
        return false;
}

bool CheckRegistryBounds()
{
    Bcode p = codesegment;

    do
    {
        switch(*p)
        {
            case ADD: case SUB: case MOV: case DIV:
            case MUL:case MOD:
                p++;
                if(!Check(*p))
                    return false;
                p++;
                if(!Check(*p))
                    return false;
                p++;
            break;
            case ADI: case SUC: case DIC: case MUC:
            case MODC:
                p++;
                if(!Check(*p))
                    return false;
                p++;
            break;
            case SCAN: case PRINT: case PRINTLN: case RAND:
                p++;
                if(!Check(*p))
                    return false;
            break;
            case LOOPE: case LOOPNE: case LOOPL: case LOOPG:
            case LOOPLE: case LOOPGE: case CMPE: case CMPNE:
            case CMPL: case CMPG: case CMPLE: case CMPGE:
                p++;
                if(!Check(*p))
                    return false;
                p++;
                if(!Check(*p))
                    return false;
                p++;
                p++;
            break;
        }
    }
    while(*p != ESTART);

    return true;
}*/

void ByteCode::Jump(Byte n)
{
    bytecode += n - 1;
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
