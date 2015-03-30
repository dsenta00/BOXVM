#ifndef POINTERNODE_H
#define POINTERNODE_H

#include "BoxInfo.h"
#include "Node.h"
#include "Pointer.h"

class PointerNode : public Node
{
	Pointer *ptr;
public:
	PointerNode *Left;
	PointerNode *Right;

	PointerNode(Pointer *, Count);
	Pointer *GetPointer();
	~PointerNode();
};

PointerNode::PointerNode(Pointer *_newptr, Count _count)
{
	ptr = _newptr;
	count = _count;
	Left = Right = NULL;
}

Pointer *PointerNode::GetPointer()
{
	return ptr;
}

PointerNode::~PointerNode()
{
	if (ptr)
		delete ptr;
}

#endif
