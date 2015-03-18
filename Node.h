#ifndef NODE_H
#define NODE_H

#include "BoxInfo.h"

class Node {
protected:
    Count count;
public:
	Node();
    Node(Count);
    Count GetCount();
};

Node::Node()
{
	count = 0;
}

Node::Node(Count _count)
{
	count = _count;
}

Count Node::GetCount()
{
	return count;
}

#endif
