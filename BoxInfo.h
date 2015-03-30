#ifndef BOXINFO_H
#define BOXINFO_H

/**
*
*	@file		BoxInfo.h
*	@purpose	Defines headers, constants, type definitions and macros specified by operation system.
*
*	@author		Duje Senta
*	@company	Faculty of Electrical Engineering, Mechanical Engineering and Naval Architecture, Split
*	@version	0.5	30/03/2015
*
*/

	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        #define _CRT_SECURE_NO_WARNINGS
        #define _CRT_SECURE_NO_DEPRECATE
        #include <Windows.h>
    #endif

	#include <iostream>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
    #include <time.h>

    #if defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
        #include <unistd.h>
        #include <sys/resource.h>
        #include <sys/times.h>
        #include <fcntl.h>
    #endif

	#define ID_STACK			0x7340
	#define ID_DATA				0x6440
	#define ID_POOL             0x7040
	#define ID_HEAP				0x6840
	#define ID_CODE				0x6340

	#define ID_INT 				0x6925
	#define ID_CHAR				0x6325
	#define ID_LONG				0x6C25
	#define ID_FLOAT 			0x6625
	#define ID_STRING 			0x7325
	#define ID_DOUBLE			0x6425
	#define ID_SHORT 			0x6825

    #define MAXBUFFERSIZE       8
    #define ENDBUFFER           &queuebuffer[MAXBUFFERSIZE-1]
    #define STARTBUFFER         &queuebuffer[0]

	#define MAXFILESIZE         1048576
	#define MAXARGS             2
	#define MAXPATHSIZE         1024
	#define MAXBUFFERWORD       128

    #define MAXLOOPSIZE         8
	#define STARTLOOP			&LoopBuffer[0]
    #define ENDLOOP				&LoopBuffer[MAXLOOPSIZE-1]

	#define AREEQUAL            0
	#define FIRSTBIGGER         1
	#define SECONDBIGGER        2

	#define BLOCK_SIZE          4096
	#define EXTRASPACE          32

    #define HeapReturnAdress(__size) starta + ((_index) * (__size))

	enum ERROR_CODES
	{
		EVERYTHING_OK =			 0,
		UNDEF_STACK_ERR =		-1,
		STAT_TYPE_ERR =			-2,
		INIT_DATA_ERR =			-3,
		DATA_HEAP_ERR =			-4,
		BUFF_NULL_ERR =			-5,
		HEAP_UNEX_ERR =			-6,
		HEAP_SET_ERR =			-7,
		HEAP_MALL_ERR =			-8,
		LOOP_OVERFLOW =			-9,
		LOOP_OUT_ERR =			-10,
		STACK_SET_ERR =			-11,
		STACK_MALL_ERR =		-12,
        BUFF_MALL_ERR =			-13,
        UKNOWN_TYPE_ERR =		-14,
        SET_NULL_ERR =			-15,
        ERROR_OPEN =			-16,
        ERROR_READ =			-17,
        READ_END_ERR =			-18,
        EMPTY_FILE =			-19,
        LARGE_FILE_ERR =		-20,
        ALLRDY_OPEN =			-21,
        PUSH_FILE_ERR =			-22,
        FILE_OPER_ERR =			-23,
        ZERO_VM_ERR =			-24,
        VM_MALL_ERR =			-25,
        QUEUE_OVERFLOW =		-26,
        ZERO_DYN_ERR =			-27,
        DYN_TYPE_ERR =			-28,
        DYN_MALLOC_ERR =		-29,
        UKNOWN_OPER_ERR =		-30,
        ADR_COMP_ERR =			-31,
        OPER_NULL_ERR =			-32,
        DIV_NULL_ERR =			-33,
        STATIC_OVERFLOW =		-34,
        BOXREADERR =			-35,
        ERRBUFFCONT =			-36,
        FLIST_MAL_ERR =			-37,
        LOOP_MAL_ERR =			-38,
        BC_MAL_ERR =			-39,
        UNDEF_DATA_ERR =		-40,
        ERROR_WRITE =			-41,
        POOL_MAL_ERR =			-42,
        POOL_RESERVE_ERR =		-43,
        POOL_SIZE_ERR =			-44,
        HEAPERR =				-45,
        UNDEF_POOL_ERR =		-46,
        FREE_OPER_ERR =			-47,
        ERROR_READ_BOX =		-48,
        REGISTRYUNEX =          -49
    };

	enum DATA_TYPES
	{
        _CHAR =		1,      // character        [1 byte]
        _INT =		2,      // integer          [4 byte]
        _SHORT =	3,      // short integer    [2 byte]
        _FLOAT =	4,      // floating point   [4 byte]
        _LONG =		5,      // long integer     [8 byte]
        _DOUBLE =	6,      // double float     [8 byte]
        _STRING =	7       // char array       [1 byte] * N
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
    *   [OpQ]   operation queue         *
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
    {                       // *OpQ mode*
        ADD =		1,      //              [pop adresses from OpQ and do add them]
        MUL =		2,      //              [pop adresses from OpQ and multiply them]
        DIV =		3,      //              [pop adresses from OpQ and divide them]
        SUB =		4,      //              [pop adresses from OpQ and subtract them]
        MOD =		5,      //              [pop adresses from OpQ and do MOD operation]
        RAND =		6,      //              [pop adress from OpQ and set random number]
        SCAN =		7,      //              [pop adress from OpQ and insert value from keyboard]
        PRINT =		8,      //              [pop adress from OpQ and print into console]
        PRINTLN =   9,      //              [pop adress from OpQ and print into console with new line]
        ADI =		10,     // [n]          [pop adress from OpQ  and add with [n]]
        MUC =		11,     // [n]          [pop adress from OpQ  and multiply with [n]]
        DIC =		12,     // [n]          [pop adress from OpQ  and divide with [n]]
        SUC =		13,     // [n]          [pop adress from OpQ  and subtract with [n]]
        MODC =		14,     // [n]          [pop adress from OpQ and do MOD operation with [n]]
        CMPE =		15,     // [n]          [pop adresses from OpQ and branch [n] number of instructions if not true]
        CMPNE =		16,     // .
        CMPG =		17,     // .
        CMPL =		18,     // .... (same for all CMP* family instructions) ...
        CMPGE =		19,     // .
        CMPLE =		20,     // .
        LOOPE =		21,     // [n]          [pop adresses from OpQ and branch [n] number of instructions if not true (Makes loop frame)]
        LOOPNE =	22,     // .
        LOOPG =		23,     // .
        LOOPL =		24,     // .... (same for all LOOP* family instructions]) ...
        LOOPGE =	25,     // .
        LOOPLE =	26,     // .
        PUSH =		27,     // [n]          [push adress from array element of [n] (ptr stored on top of ptr tree) into OpQ)
        FNEW =		28,     // [ptr][n]     [memory allocation by [n] number elements]
        NEW =		29,     // [ptr][n]     [memory allocation by [n] number elements without heap defragmentation]
        LEAC =		30,     // [ptr][n]     [push adress of [ptr][n] array element into OpQ>
        FNEWV =		31,     // [ptr][var]   [memory allocation by [var] number elements without heap defragmentation]
        NEWV =		32,     // [ptr][var]   [memory allocation by [var] number elements]
        LEA =		33,     // [ptr][var]   [push adress of [ptr][var] array element into OpQ>
        FREE =		34,     // [ptr]        [memory deallocation]
        PUSHS =     35,     // [var]        [push static adress with count [n] into OpQ]
        OPENW =		36,     // [str]        [open file stream for write by path [str]]
        OPENR =		37,     // [str]        [open file stream for read by path [str]]
        OPENA =		38,     // [str]        [open file stream for append by path [str]]
        PUTC =		39,     // [str]        [pop adress from OpQ and insert value into file stream by path [str]]
        PUTI =		40,     // .
        PUTSH =		41,     // .
        PUTF =		42,     // .            [same for all PUT* family instructions] ...
        PUTL =		43,     // .
        PUTD =		44,     // .
        PUTS =		45,     // .
        GETC =		46,     // [str]        [pop adress from OpQ and insert value from file stream by path [str]
        GETI =		47,     // .
        GETSH =		48,     // .
        GETF =		49,     // .
        GETL =		50,     // .            [same for all GET* family instructions]) ...
        GETD =		51,     // .
        GETS =		52,     // .
        GETLINE =	53,     // [str]        [pop adress from OpQ and insert line from file stream by path [str]]
        REPLOOP =	54,     //              [branch to loop start>
        START =		55,     //              [start program marker>
        ESTART =	56,     //              [end program marker>
        MOV =		57,     // [any][any]   [copy value from right argument to left argument]
        REG =       58,     //              [start marker for block of operations in registry mode]
        ENDREG =    59      //              [end marker for block of operations in registry mode]
    };

    /*** REGISTRY MODE DIFFERENCES **
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
     *      PUT*    [var][rx]       *
     *      GET*    [var][rx]       *
     *      GETLINE [var][rx]       *
     *                              *
     *      CMP*    [rx][rx][n]     *
     *      LOOP*   [rx][rx][n]     *
     *                              *
     *******************************/

	enum FILE_MODES
	{
        _UNOPEN =	   -1,  // Unopened file stream.
        _READ =			0,  // File stream opened for read.
        _WRITE =		1,  // File stream opened for write.
        _APPEND =		2   // File stream opened for append.
	};

    typedef short Type;
    typedef short Status;
    typedef char *Adress;
    typedef char *Bcode;
    typedef short Size;
    typedef int DSize;
    typedef char Count;

#endif
