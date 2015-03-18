#ifndef OPERATIONQUEUE_H
#define OPERATIONQUEUE_H

#include "BoxInfo.h"
#include "StaticData.h"

class OperationQueue
{
	StaticData queuebuffer[MAXBUFFERSIZE];
	StaticData *pstart;
	StaticData *pend;
public:

    OperationQueue();
    Status Push(Adress, Type);
    Adress Pop(Type &);
};

OperationQueue::OperationQueue()
{
    pstart = pend = STARTBUFFER;
}

Status OperationQueue::Push(Adress _adress, Type _type)
{
    pend->SetExternData(_adress, _type);

    if (pend < ENDBUFFER)
        pend++;
    else
        return QUEUE_OVERFLOW;

    return EVERYTHING_OK;
}

Adress OperationQueue::Pop(Type &_type)
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
