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
    monitor = NULL;
}

void Loop::SetMonitor(ProgramMonitor *_monitor)
{
    monitor = _monitor;
}

void Loop::PushLoop(Bcode _adress)
{
    if (make == ENDLOOP)
        SETERR(LOOP_OVERFLOW);
    else
	{
        *make = _adress;
        curr = make;
        make++;
    }
}

void Loop::PopLoop()
{
    if (make == STARTLOOP)
        SETERR(LOOP_OUT_ERR);
	else
	{
        make = curr;

        if (curr != STARTLOOP)
            make--;
    }
}

Bcode Loop::GetStartLoop()
{
    return *curr;
}

#endif
