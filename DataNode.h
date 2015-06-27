#ifndef DATANODE_H
#define DATANODE_H
#include "BoxInfo.h"
#include "Data.h"

class DataNode {
public:
	DataNode(Data*, Count);
	DataNode();
	DataNode(Count);
	Count GetCount();
	Data *GetDataInfo();
	~DataNode();

	DataNode *Left;
	DataNode *Right;
protected:
	Data *DataInfo;
	Count count;
};

DataNode::DataNode(Data*_data, Count _count)
{
	Left = Right = null;
	DataInfo = _data;
	count = _count;
}

DataNode::DataNode()
{
	memset(this, null, sizeof(DataNode));
}

DataNode::DataNode(Count _count)
{
	memset(this, null, sizeof(DataNode));
	count = _count;
}

Count DataNode::GetCount()
{
	return count;
}

Data*DataNode::GetDataInfo()
{
	return DataInfo;
}

DataNode::~DataNode()
{
	delete DataInfo;
}

#endif // DATANODE_H
