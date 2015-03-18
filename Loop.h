#ifndef LOOP_H
#define LOOP_H

#include "BoxInfo.h"
#include "LoopNode.h"

class Loop
{
    LoopNode LoopBuffer[MAXLOOPSIZE];
	LoopNode *Current;
	LoopNode *MakeLoop;
    Status status;
public:

    Loop();
    Status PushLoop(Bcode);
    Status PopLoop();
    Bcode GetStartLoop();
    void SetEndLoop(Bcode);
    Bcode GetEndLoop();
};

Loop::Loop()
{
    Current = STARTLOOP;
    MakeLoop = STARTLOOP;
    status = EVERYTHING_OK;
}

Status Loop::PushLoop(Bcode _adress)
{
    if (MakeLoop == ENDLOOP)
        status = LOOP_OVERFLOW;
    else
    {
        MakeLoop->NewLoopNode(_adress);
        Current = MakeLoop;
        MakeLoop++;
    }

    return status;
}

Status Loop::PopLoop()
{
    if (MakeLoop == STARTLOOP)
        status = LOOP_OUT_ERR;
    else
    {
        MakeLoop = Current;

        if (Current == STARTLOOP)
            MakeLoop--;
    }

    return status;
}

Bcode Loop::GetStartLoop()
{
    return Current->GetStartLoop();
}

void Loop::SetEndLoop(Bcode _adress)
{
    Current->SetEndLoop(_adress);
}

Bcode Loop::GetEndLoop()
{
    return Current->GetEndLoop();
}


#endif
