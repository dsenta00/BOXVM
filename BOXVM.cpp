/*
 *	PROGRAM DESCRIPTION
 *
 *	@program	BOX programming language virutal machine
 *	@file		BOXVM.cpp
 *	@purpose	An abstract virtual machine that interprets programs written in an executable .box file format.
 *
 *	@author		Duje Senta
 *	@company	Faculty of Electrical Engineering, Mechanical Engineering and Naval Architecture, Split
 *	@version	0.8	13/06/2016
 *
 */

//#define PRINT_DEBUG_MODE

#include "BOXVM.h"
#include "TestBox.h"
#include "BoxTrace.h"

int main(int argc, char *argv[])
{
    ADD_TRACE("MEMORY_COLLECTOR");
    ADD_TRACE("EXECUTE");
    ADD_TRACE("BOX_PROGRAM");

    BOXVM_PATH = argv[0];

    if (argc == 1)
    {
        Testing();
    }
    else
    {
        runBox(argc, argv);
    }

    return programMonitor.getStatus();
}
