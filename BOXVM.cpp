/*****************************************************************************************************************
 *	PROGRAM DESCRIPTION
 *
 *	@program	BOX programming language virutal machine
 *	@file		BOXVM.cpp
 *	@purpose	An abstract virtual machine that interprets programs written in an executable .box file format.
 *
 *	@author		Duje Senta
 *	@company	Faculty of Electrical Engineering, Mechanical Engineering and Naval Architecture, Split
 *	@version	0.6	27/04/2015
 *
 *****************************************************************************************************************/

#include "BOXVM.h"
#include "TestBox.h"

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        Testing();
    }
    else
    {
        RunProgram(argv[1]);
    }

    return 0;
}
