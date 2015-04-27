#ifndef LOOP_H
#define LOOP_H

#include "BoxInfo.h"
#include "ProgramMonitor.h"

class Loop {
public:
	Loop();
    void PushLoop(Bcode);
    void PopLoop();
    Bcode GetStartLoop();
    void SetMonitor(ProgramMonitor *);
protected:
    Bcode buffer[MAXLOOPSIZE];
    Bcode *curr;
    Bcode *make;
    ProgramMonitor *monitor;
};

Loop::Loop()
{
    curr = STARTLOOP;
    make = STARTLOOP;
    memset(buffer, 0, sizeof(Bcode));
}

void Loop::SetMonitor(ProgramMonitor *_monitor)
{
    monitor = _monitor;
}

void Loop::PushLoop(Bcode _adress)
{
    if (make != ENDLOOP)
    {
        *make = _adress;
        curr = make;
        make++;
    }
    else
    {
        SETERR(LOOP_OVERFLOW);
    }
}

void Loop::PopLoop()
{
    if (make != STARTLOOP)
    {
        make = curr;

        if (curr != STARTLOOP)
            make--;
    }
	else
    {
        SETERR(LOOP_OUT_ERR);
    }
}

Bcode Loop::GetStartLoop()
{
    return *curr;
}

#endif
