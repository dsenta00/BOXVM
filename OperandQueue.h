#ifndef OperandQUEUE_H
#define OperandQUEUE_H

#include "BoxInfo.h"
#include "StaticData.h"

class OperandQueue
{
	StaticData queuebuffer[MAXBUFFERSIZE];
	StaticData *pstart;
	StaticData *pend;
public:

    OperandQueue();
    Status Push(Adress, Type);
    Adress Pop(Type &);
};

OperandQueue::OperandQueue()
{
    pstart = pend = STARTBUFFER;
}

Status OperandQueue::Push(Adress _adress, Type _type)
{
    pend->SetExternData(_adress, _type);

    if (pend < ENDBUFFER)
        pend++;
    else
        return QUEUE_OVERFLOW;

    return EVERYTHING_OK;
}

Adress OperandQueue::Pop(Type &_type)
{
    StaticData *q = pstart;

    if (pend != STARTBUFFER)
    {
        if (++pstart == pend)
            pstart = pend = STARTBUFFER;
    }

    _type = q->GetType();
    return q->GetStartAdress();
}

#endif
