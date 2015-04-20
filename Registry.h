#ifndef Registry_H
#define Registry_H

#include "BoxInfo.h"
#include "ProgramMonitor.h"
#include "Data.h"

class Registry {
public:
    Registry();
    void SetRegistry(Data *, Count);
    void SetRegistry(Data *, Count, Count);
    void GetRegistry(Adress &, Type &, Count);
    void ResetRegistry();
    void SetMonitor(ProgramMonitor *);
protected:
    Data *buffer[MAXBUFFERSIZE];
    Count index[MAXBUFFERSIZE];
    ProgramMonitor *monitor;
};

Registry::Registry()
{
    memset(this, 0, sizeof(Registry));
}

void Registry::SetMonitor(ProgramMonitor *_monitor)
{
    monitor = _monitor;
}

void Registry::SetRegistry(Data *data, Count _regnum)
{
    if(_regnum >= 0 && _regnum < MAXBUFFERSIZE)
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
    if(_regnum >= 0 && _regnum < MAXBUFFERSIZE)
    {
        buffer[_regnum] = data;
        index[_regnum] = _index;
    }
    else
    {
        SETERR(REGISTRYUNEX);
    }
}

void Registry::GetRegistry(Adress &_adress, Type &_type, Count _regnum)
{
    if(_regnum >= 0 && _regnum < MAXBUFFERSIZE)
    {
        if(index[_regnum])
            _adress = buffer[_regnum]->GetAdress(index[_regnum]);
        else
            _adress = buffer[_regnum]->GetAdress();

        _type = buffer[_regnum]->GetType();
    }
    else
    {
        SETERR(REGISTRYUNEX);
    }
}

#endif
