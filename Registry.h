#ifndef Registry_H
#define Registry_H

#include "BoxInfo.h"
#include "ProgramMonitor.h"
#include "Data.h"

class Registry {
public:
    Registry();
    inline void SetRegistry(Data *, Count);
    inline void SetRegistry(Data *, Count, Count);
    inline void GetRegistry(Address &, Type &, Count);
    void ResetRegistry();
    void SetMonitor(ProgramMonitor *);
protected:
    Data *buffer[MAXBUFFERSIZE];
    Count index[MAXBUFFERSIZE];
    ProgramMonitor *monitor;
};

Registry::Registry()
{
    memset(this, null, sizeof(Registry));
}

void Registry::SetMonitor(ProgramMonitor *_monitor)
{
    monitor = _monitor;
}

void Registry::SetRegistry(Data *data, Count _regnum)
{
    if(_regnum >= null && _regnum < MAXBUFFERSIZE)
    {
        buffer[_regnum] = data;
        index[_regnum] = 0;
    }
    else
    {
        SETERR(REGISTRYUNEX);
    }
}

void Registry::SetRegistry(Data *data, Count _regnum, Count _index)
{
    if(_regnum >= null && _regnum < MAXBUFFERSIZE)
    {
        buffer[_regnum] = data;
        index[_regnum] = _index;
    }
    else
    {
        SETERR(REGISTRYUNEX);
    }
}

void Registry::GetRegistry(Address &_address, Type &_type, Count _regnum)
{
    if(_regnum >= null && _regnum < MAXBUFFERSIZE)
    {
        if(index[_regnum])
        {
            _address = buffer[_regnum]->GetAddress(index[_regnum]);
        }
        else
        {
            _address = buffer[_regnum]->GetAddress();
        }

        _type = buffer[_regnum]->GetType();
    }
    else
    {
        SETERR(REGISTRYUNEX);
    }
}

#endif
