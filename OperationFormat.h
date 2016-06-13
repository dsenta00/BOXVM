#ifndef OPERATION_FORMAT_H
#define OPERATION_FORMAT_H
#include "Data.h"
#include "Stack.h"
#include "Heap.h"
#include "BoxTrace.h"

/*
    0[OP_CODE]
    1[PTR]
    2[PADD]
    4[DATA1]
    5[DATA2]
    6[CONST]
    */
#pragma pack (1)
typedef struct _operation {
    unsigned char opCode;
    unsigned char ptr;
    short         padding;
    unsigned char data1;
    unsigned char data2;
    short         constant;
} OperationFormat;

#endif