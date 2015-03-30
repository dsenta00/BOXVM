#ifndef LOOPNODE_H
#define LOOPNODE_H

#include "BoxInfo.h"

class LoopNode
{
	Bcode start;
	Bcode end;
public:
	LoopNode();
	void SetEndLoop(Bcode);
	void NewLoopNode(Bcode);
	Bcode GetStartLoop();
	Bcode GetEndLoop();
};

LoopNode::LoopNode()
{
	start = NULL;
	end = NULL;
}

void LoopNode::SetEndLoop(Bcode _adress)
{
	end = _adress;
}

void LoopNode::NewLoopNode(Bcode _adress)
{
	start = _adress;
	end = NULL;
}

Bcode LoopNode::GetStartLoop()
{
	return start;
}

Bcode LoopNode::GetEndLoop()
{
	return end;
}

#endif // LOOPNODE_H
