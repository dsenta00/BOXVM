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
    void ResetOperandQueue();
    Status SetRegistry(Adress, Type, Count);
    Status GetRegistry(Adress *, Type &, Count);
};

OperandQueue::OperandQueue()
{
    this->ResetOperandQueue();
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

void OperandQueue::ResetOperandQueue()
{
    pend = pstart = STARTBUFFER;
}

Status OperandQueue::SetRegistry(Adress _adress, Type _type, Count _regnum)
{
    if(_regnum >= 0 && _regnum < MAXBUFFERSIZE)
    {
        queuebuffer[_regnum].SetExternData(_adress, _type);
        return EVERYTHING_OK;
    }
    else
        return REGISTRYUNEX;
}

Status OperandQueue::GetRegistry(Adress *_adress, Type &_type, Count _regnum)
{
    if(_regnum >= 0 && _regnum < MAXBUFFERSIZE)
    {
        *_adress = queuebuffer[_regnum].GetStartAdress();
        _type = queuebuffer[_regnum].GetType();
        return EVERYTHING_OK;
    }
    else
        return REGISTRYUNEX;
}

#endif
