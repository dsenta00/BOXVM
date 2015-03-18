#ifndef DATATREE_H
#define DATATREE_H

#include "BoxInfo.h"

class Tree {
protected:
    Status status;
public:
	template <typename T>
    Size Height(T *);
	template <typename T>
    Size Difference(T *);
	template <typename T>
	T *RR_Rotation(T *);
	template <typename T>
	T *Balance(T *);
	template <typename T>
	T *DeleteTree(T *);

    Status GetStatus();
};

Status Tree::GetStatus()
{
	return status;
}

template <typename T>
Size Tree::Height(T *current)
{
    Size l_height = 0, r_height = 0;

	if (current != NULL)
	{
		l_height = Height(current->Left);
		r_height = Height(current->Right);
	}

	if (r_height > l_height)
		return r_height + 1;
	else
		return l_height + 1;
}

template <typename T>
Size Tree::Difference(T *_current)
{
	return Height(_current->Right) - Height(_current->Left);
}

template <typename T>
T *Tree::RR_Rotation(T *_parent)
{
	T *temp = NULL;

	temp = _parent->Right;
	_parent->Right = temp->Left;
	temp->Left = _parent;

	return temp;
}

template <typename T>
T *Tree::Balance(T *_current)
{
	if (_current->Right == NULL || _current->Right->Right == NULL)
		return _current;
	else
		_current->Right = Balance(_current->Right);

	if (Difference(_current) == 2)
		_current = RR_Rotation(_current);

	return _current;
}

template <typename T>
T *Tree::DeleteTree(T *_current)
{
	if (_current != NULL)
	{
		if (_current->Left != NULL)
			_current->Left = DeleteTree(_current->Left);
		if (_current->Right != NULL)
			_current->Right = DeleteTree(_current->Right);

		delete _current;
		_current = NULL;
	}

	return _current;
}

#endif // DATA_TREE_H
