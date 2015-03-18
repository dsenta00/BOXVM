#ifndef STATICDATANODE_H
#define STATICDATANODE_H

#include "Node.h"
#include "StaticData.h"

class StaticDataNode : public Node {
protected:
	StaticData *DataInfo;
public:
	StaticDataNode *Left;
	StaticDataNode *Right;

    StaticDataNode(StaticData *, Count);
	StaticData *GetDataInfo();
	~StaticDataNode();
};

StaticDataNode::StaticDataNode(StaticData *_NewData, Count _count)
{
	Left = Right = NULL;
	DataInfo = _NewData;
	count = _count;
}

StaticData *StaticDataNode::GetDataInfo()
{
	return DataInfo;
}

StaticDataNode::~StaticDataNode()
{
	delete DataInfo;
}

#endif
