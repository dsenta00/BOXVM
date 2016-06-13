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
#define MAX_BUFFER_SIZE     8
#define MAXFILESIZE         1048576
#define MAXPATHSIZE         1024
#define MAX_BUFFER_WORD     128
#define MAXLOOPSIZE         8
#define BLOCK_SIZE          4096

typedef unsigned int Type;
typedef unsigned int Status;
typedef char *Address;
typedef char *Bcode;
typedef char Byte;
typedef unsigned int Size;
typedef unsigned int Count;

char *BOXVM_PATH = null;

enum DATA_TYPES
{
    BOX_CHAR,
    BOX_INT,
    BOX_FLOAT,
    BOX_LONG,
    BOX_DOUBLE,
    BOX_STRING
};

const Size DATA_TYPES_SIZE[6] =
{
    1,
    4,
    4,
    8,
    8,
    0
};

enum OPERATIONS
{
    MOV,
    ADD,
    MUL,
    DIV,
    SUB,
    MOD,
    RAND,
    SCAN,
    PRINT,
    PRINTLN,
    ADI,
    MUC,
    DIC,
    SUC,
    MODC,
    CMPE,
    CMPNE,
    CMPG,
    CMPL,
    CMPGE,
    CMPLE,
    LOOPE,
    LOOPNE,
    LOOPG,
    LOOPL,
    LOOPGE,
    LOOPLE,
    NEW,
    NEWV,
    FREE,
    OPENW,
    OPENR,
    OPENA,
    PUT,
    GET,
    GETLINE,
    REPLOOP,
    RUN,
    START,
    ESTART
};

#endif
