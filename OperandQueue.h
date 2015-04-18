#ifndef OperandQUEUE_H
#define OperandQUEUE_H

#include "BoxInfo.h"
#include "Data.h"

class OperandQueue {
public:
    OperandQueue();
    Status Push(Data *);
    Status Push(Data *, Count);
    Adress Pop(Type &);
    Status SetRegistry(Data *, Count);
    Status SetRegistry(Data *, Count, Count);
    Status GetRegistry(Adress *, Type &, Count);
    void ResetOperandQueue();
protected:

    Data *buffer[MAXBUFFERSIZE];
    Count index[MAXBUFFERSIZE];
    Count start;
    Count end;
};

OperandQueue::OperandQueue()
{
    memset(this, 0, sizeof(OperandQueue));
}

Status OperandQueue::Push(Data *_data)
{
    buffer[end] = _data;
    index[end] = 0;

    if (end < 7)
        end++;
    else
        return QUEUE_OVERFLOW;

    return EVERYTHING_OK;
}

Status OperandQueue::Push(Data *_data, Count _index)
{
    buffer[end] = _data;
    index[end] = _index;

    if (end < 7)
        end++;
    else
        return QUEUE_OVERFLOW;

    return EVERYTHING_OK;
}

Adress OperandQueue::Pop(Type &_type)
{
    Data *q = buffer[start];

    if (end)
    {
        if (++start == end)
            start = end = 0;
    }

    _type = q->GetType();

    if(index[start])
        return q->GetAdress(index[start]);
    else
        return q->GetAdress();
}

void OperandQueue::ResetOperandQueue()
{
    start = end = 0;
}

Status OperandQueue::SetRegistry(Data *data, Count _regnum)
{
    if(_regnum >= 0 && _regnum < MAXBUFFERSIZE)
    {
        buffer[_regnum] = data;
        index[_regnum] = 0;
        return EVERYTHING_OK;
    }
    else
        return REGISTRYUNEX;
}

Status OperandQueue::SetRegistry(Data *data, Count _regnum, Count _index)
{
    if(_regnum >= 0 && _regnum < MAXBUFFERSIZE)
    {
        buffer[_regnum] = data;
        index[_regnum] = _index;
        return EVERYTHING_OK;
    }
    else
        return REGISTRYUNEX;
}

Status OperandQueue::GetRegistry(Adress *_adress, Type &_type, Count _regnum)
{
    if(_regnum >= 0 && _regnum < MAXBUFFERSIZE)
    {
        if(index[_regnum])
            *_adress = buffer[_regnum]->GetAdress(index[_regnum]);
        else
            *_adress = buffer[_regnum]->GetAdress();

        _type = buffer[_regnum]->GetType();

        return EVERYTHING_OK;
    }
    else
        return REGISTRYUNEX;
}


#endif
