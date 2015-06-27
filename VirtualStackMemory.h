#ifndef VIRTUALSTACKMEMORY_H
#define VIRTUALSTACKMEMORY_H
#include "BoxInfo.h"
#include "ProgramMonitor.h"

class VirtualStackMemory {
public:
	VirtualStackMemory();
	~VirtualStackMemory();
	inline void Initialize(Size, ProgramMonitor *);
	Address GetNext();
	void SetNext(Address);
protected:
	ProgramMonitor *monitor;
	Address memory;
	Address nextaddr;
	Size limit;
};

VirtualStackMemory::VirtualStackMemory()
{
	memory = null;
	nextaddr = null;
	limit = null;
}

VirtualStackMemory::~VirtualStackMemory()
{
    if(memory)
    {
        free(memory);
    }
}

inline void VirtualStackMemory::Initialize(Size _limit, ProgramMonitor *_monitor)
{
	monitor = _monitor;

	if (_limit > 0)
	{
		limit = _limit;
		memory = nextaddr = (Address)calloc(limit, sizeof(char));

		if (!memory)
		{
			SETERR(VM_MALL_ERR);
		}
	}
	else
	{
		SETERR(ZERO_VM_ERR);
	}
}

Address VirtualStackMemory::GetNext()
{
	if (nextaddr < memory + limit)
	{
		return nextaddr;
	}
	else
	{
		SETERR(STATIC_OVERFLOW);
		return null;
	}
}

void VirtualStackMemory::SetNext(Address _nextaddr)
{
	nextaddr = _nextaddr;
}

#endif // VIRTUALSTACKMEMORY_H
