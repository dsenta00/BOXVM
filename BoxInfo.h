#ifndef BOXINFO_H
#define BOXINFO_H

/*****************************************************************************************************************
 *	PROGRAM DESCRIPTION
 *
 *	@program	BOX programming language virutal machine
 *	@file		BOXVM.cpp
 *	@purpose	Defines headers, constants, type definitions and macros specified by operation system.
 *
 *	@author		Duje Senta
 *	@company	Faculty of Electrical Engineering, Mechanical Engineering and Naval Architecture, Split
 *	@version	0.6	27/04/2015
 *
 *****************************************************************************************************************/


	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        #define _CRT_SECURE_NO_WARNINGS
        #define _CRT_SECURE_NO_DEPRECATE
		#include <Windows.h>
        #include <iomanip>
        #include <conio.h>
	#endif

    #include <iostream>
    #include <stdio.h>
    #include <stdlib.h>
	#include <string.h>
	#include <time.h>

	#if defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
            #include <unistd.h>
	#endif

    #define null                0
    #define MAXBUFFERSIZE       8
	#define MAXFILESIZE         1048576
    #define MAXARGS             2
	#define MAXPATHSIZE         1024
	#define MAXBUFFERWORD       128

    #define MAXLOOPSIZE         8
    #define STARTLOOP           &buffer[0]
    #define ENDLOOP             &buffer[MAXLOOPSIZE]

    #define AREEQUAL            (!alu.GetFlag())
    #define FIRSTBIGGER         (alu.GetFlag() < null)
    #define SECONDBIGGER        (alu.GetFlag() > null)

	#define BLOCK_SIZE          4096
	#define EXTRASPACE          32

    #define SETERR(__ERROR)     monitor->SetError(__ERROR)
    #define EOK                 monitor->OK()

    #define HeapReturnAddress(__size) starta + ((_index) * (__size))

	enum ERROR_CODES
	{
        EVERYTHING_OK =			 0,
        STAT_TYPE_ERR =			-2,
        HEAP_UNEX_ERR =			-6,
        HEAP_MALL_ERR =			-8,
		LOOP_OVERFLOW =			-9,
        LOOP_OUT_ERR =			-10,
        ERROR_OPEN =			-16,
		ERROR_READ =			-17,
        READ_END_ERR =			-18,
		EMPTY_FILE =			-19,
        LARGE_FILE_ERR =		-20,
		FILE_OPER_ERR =			-23,
        ZERO_VM_ERR =			-24,
        VM_MALL_ERR =			-25,
        DYN_TYPE_ERR =			-28,
        UKNOWN_OPER_ERR =		-30,
        ADR_COMP_ERR =			-31,
        OPER_NULL_ERR =			-32,
		DIV_NULL_ERR =			-33,
        STATIC_OVERFLOW =		-34,
        ERRBUFFCONT =			-36,
        ERROR_WRITE =			-41,
		POOL_RESERVE_ERR =		-43,
        POOL_SIZE_ERR =			-44,
		UNDEF_POOL_ERR =		-46,
		FREE_OPER_ERR =			-47,
        ERROR_READ_BOX =		-48,
        REGISTRYUNEX =          -49,
	};

	enum DATA_TYPES
	{
        _CHAR =		0,      // character        [1 byte]
        _SHORT =	1,      // short integer    [2 byte]
        _INT =		2,      // integer          [4 byte]
        _FLOAT =	3,      // floating point   [4 byte]
        _LONG =		4,      // long integer     [8 byte]
        _DOUBLE =	5,      // double float     [8 byte]
        _STRING =	6       // char array       [1 byte] * N
	};

    /********  OPERATION LEGEND  ********
    *                                   *
    *   [var] - static variable         *
    *   [any] - static/pointer variable *
    *   [ptr] - pointer variable        *
    *   [n]   - constant                *
    *   [str] - string static variable  *
    *   [rx]  - registry                *
    *                                   *
    *   [*C]    char                    *
    *   [*I]    integer                 *
    *   [*SH]   short integer           *
    *   [*L]    long integer            *
    *   [*F]    float                   *
    *   [*D]    double float            *
    *   [*S]    string                  *
    *                                   *
    ************************************/

	enum OPERATIONS
    {
        MOV =		0,
        ADD =		1,
        MUL =		2,
        DIV =		3,
        SUB =		4,
        MOD =		5,
        RAND =		6,
        SCAN =		7,
        PRINT =		8,
        PRINTLN =   9,
        ADI =		10,
        MUC =		11,
        DIC =		12,
        SUC =		13,
        MODC =		14,
        CMPE =		15,
        CMPNE =		16,
        CMPG =		17,
        CMPL =		18,
        CMPGE =		19,
        CMPLE =		20,
        LOOPE =		21,
        LOOPNE =	22,
        LOOPG =		23,
        LOOPL =		24,
        LOOPGE =	25,
        LOOPLE =	26,
        FNEW =		28,
        NEW =		29,
        LEAC =		30,
        FNEWV =		31,
        NEWV =		32,
        LEA =		33,
        FREE =		34,
        PUSHS =     35,
        OPENW =		36,
        OPENR =		37,
        OPENA =		38,
        FEOF =      39,
        ISOPEN =    40,
        PUTC =		41,
        PUTI =		42,
        PUTSH =		43,
        PUTF =		44,
        PUTL =		45,
        PUTD =		46,
        PUTS =		47,
        GETC =		48,
        GETI =		49,
        GETSH =		50,
        GETF =		51,
        GETL =		52,
        GETD =		53,
        GETS =		54,
        GETLINE =	55,
        REPLOOP =	56,
        PROC =      57,
        START =		58,
        ESTART =	59
    };

    /*** REGISTRY MODE FORMAT OPER **
     *                              *
     *      MOV [rx][rx]            *
     *      ADD [rx][rx]            *
     *      DIV [rx][rx]            *
     *      SUB [rx][rx]            *
     *      MUL [rx][rx]            *
     *      MOD [rx][rx]            *
     *                              *
     *      SCAN    [rx]            *
     *      PRINT   [rx]            *
     *      RAND    [rx]            *
     *      PRINTLN [rx]            *
     *                              *
     *      ADI     [rx][n]         *
     *      MUC     [rx][n]         *
     *      DIC     [rx][n]         *
     *      SUC     [rx][n]         *
     *      MODC    [rx][n]         *
     *                              *
     *      PUSHS   [var][rx]       *
     *      PUSH    [ptr][rx]       *
     *      LEA     [ptr][rx][rx]   *
     *      LEAC    [ptr][n][rx]    *
     *      NEW     [ptr][n]        *
     *      NEWV    [ptr][rx]       *
     *      FNEW    [ptr][n]        *
     *      FNEWV   [ptr][rx]       *
     *      FREE    [ptr]           *
     *                              *
     *      PUT*    [path][rx]      *
     *      GET*    [path][rx]      *
     *      GETLINE [path][rx]      *
     *      FEOF    [path][n]       *
     *      ISOPEN  [path]          *
     *                              *
     *      OPEN*   [path]          *
     *                              *
     *      CMP*    [rx][rx][n]     *
     *      LOOP*   [rx][rx][n]     *
     *                              *
     *******************************/

    typedef char Type;
    typedef int Status;
    typedef char *Address;
    typedef char *Bcode;
    typedef char Byte;
    typedef int Size;
    typedef int Count;
#endif
