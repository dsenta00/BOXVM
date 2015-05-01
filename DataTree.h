#ifndef DATATREE_H
#define DATATREE_H

#include "BoxInfo.h"
#include "ProgramMonitor.h"
#include "DataNode.h"

class DataTree {
public:
	DataTree();
	Size Height(DataNode *);
	Size Difference(DataNode*);
	DataNode *RR_Rotation(DataNode *);
	DataNode *Balance(DataNode *);
	DataNode *DeleteTree(DataNode *);
	inline Data *SearchFor(Count);
	~DataTree();
protected:
	DataNode *Push(Data *);

	DataNode *root;
	DataNode *last;
	Count counter;
	ProgramMonitor *monitor;
};

DataTree::DataTree()
{
	counter = null;
	root = null;
	last = null;
	monitor = null;
}

DataNode *DataTree::Push(Data *_element)
{
	DataNode *q = new DataNode(_element, ++counter);

	if (q)
	{
		if (!root)
		{
			root = q;
			last = root;
		}
		else
		{
			last->Right = q;
			last = q;
			root = Balance(root);
		}
	}
	return root;
}

inline Data *DataTree::SearchFor(Count _count)
{
	DataNode *curr = root;

	while (curr)
	{
		if (curr->GetCount() > _count)
			curr = curr->Left;
		else if (curr->GetCount() < _count)
			curr = curr->Right;
		else
			break;
	}

	if (curr)
		return curr->GetDataInfo();
	else
		return null;
}

Size DataTree::Height(DataNode *current)
{
	Size l_height = 0, r_height = 0;

	if (current)
	{
		l_height = Height(current->Left);
		r_height = Height(current->Right);
	}

	if (r_height > l_height)
		return r_height + 1;
	else
		return l_height + 1;
}

Size DataTree::Difference(DataNode *_current)
{
	return Height(_current->Right) - Height(_current->Left);
}

DataNode *DataTree::RR_Rotation(DataNode *_parent)
{
	DataNode *temp = null;

	temp = _parent->Right;
	_parent->Right = temp->Left;
	temp->Left = _parent;

	return temp;
}

DataNode *DataTree::Balance(DataNode *_current)
{
	if (!_current->Right || !_current->Right->Right)
		return _current;
	else
		_current->Right = Balance(_current->Right);

	if (Difference(_current) == 2)
		_current = RR_Rotation(_current);

	return _current;
}

DataNode *DataTree::DeleteTree(DataNode *_current)
{
	if (_current)
	{
		if (_current->Left)
			_current->Left = DeleteTree(_current->Left);
		if (_current->Right)
			_current->Right = DeleteTree(_current->Right);

		delete _current;
		_current = null;
	}

	return _current;
}

DataTree::~DataTree()
{
	last = root = DeleteTree(root);
}

#endif // DATA_TREE_H
