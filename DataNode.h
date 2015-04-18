#ifndef DATANODE_H
#define DATANODE_H
#include "BoxInfo.h"
#include "Data.h"

class DataNode {
protected:
    Data *DataInfo;
    Count count;
public:
    DataNode *Left;
    DataNode *Right;

    DataNode(Data*, Count);
    DataNode();
    DataNode(Count);
    Count GetCount();
    Data *GetDataInfo();
    ~DataNode();
};

DataNode::DataNode(Data*_data, Count _count)
{
    Left = Right = NULL;
    DataInfo = _data;
    count = _count;
}

DataNode::DataNode()
{
    memset(this, 0, sizeof(DataNode));
}

DataNode::DataNode(Count _count)
{
    memset(this, 0, sizeof(DataNode));
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
