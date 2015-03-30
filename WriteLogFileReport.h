#ifndef WRITELOGERRORREPORT_H
#define WRITELOGERRORREPORT_H

#include "BoxInfo.h"

void WriteLogErrorReport(char *path, Status error_code)
{
	char *p_path = NULL;
	FILE *fp = NULL;

	printf("\n\tFatal runtime error. [ERROR CODE = 0x%08x] (%d)", error_code, error_code);
	printf("\n\tAll BOXVM reserved memory and connections are being released.\n");

	p_path = strchr(path, '.');

	if (p_path)
	{
		strcpy(p_path, ".logbox");
		fp = fopen(path, "w+");
	}

	if (fp)
	{
		printf("\n\tPlease read the error report located at <\"%s\">\n", path);
		fprintf(fp, "\n\tBOXVM RUNTIME ERROR REPORT:");
		fprintf(fp, "\n\t[ERROR CODE = 0x%08x] (%d)\n\n\t*** ", error_code, error_code);

		switch (error_code)
		{
            case REGISTRYUNEX:
                fprintf(fp, "Trying to do operation on unknown registry count.");
            break;
            case UNDEF_POOL_ERR:
                fprintf(fp, "Undefined pool section.");
            break;
            case HEAPERR:
                fprintf(fp, "BOXVM internal error: Error allocating class <Heap>.");
            break;
            case POOL_SIZE_ERR:
                fprintf(fp, "Unable to allocate zero or negative size of pool space.");
            break;
            case POOL_RESERVE_ERR:
                fprintf(fp, "BOXVM internal error: Memory pool reservation error.");
            break;
            case POOL_MAL_ERR:
                fprintf(fp, "BOXVM internal error: Class <MemoryPool> allocation error.");
            break;
            case UNDEF_DATA_ERR:
                fprintf(fp, "Undefined data segment error.");
            break;
            case ERRBUFFCONT:
                fprintf(fp, "BOXVM internal error: Code segment memory allocation error.");
            break;
            case BOXREADERR:
                fprintf(fp, "BOXVM internal error: class <ReadBoxFile> allocation error.");
            break;
            case STATIC_OVERFLOW:
                fprintf(fp, "Static data virtual memory overflow.");
            break;
            case OPER_NULL_ERR:
                fprintf(fp, "Unable to do operation on NULL memory.");
            break;
            case DIV_NULL_ERR:
                fprintf(fp, "Error, division by zero value (0).");
            break;
            case ADR_COMP_ERR:
                fprintf(fp, "Unknown addresses or types, unable to compare.");
            break;
            case UKNOWN_OPER_ERR:
                fprintf(fp, "Trying to execute an unknown bytecode operation.");
            break;
            case UNDEF_STACK_ERR:
                fprintf(fp, "Undefined stack segment.");
            break;
            case DYN_TYPE_ERR:
                fprintf(fp, "Bad dynamic data type declaration.");
            break;
            case STAT_TYPE_ERR:
                fprintf(fp, "Bad static data type declaration.");
            break;
            case INIT_DATA_ERR:
                fprintf(fp, "Data initialization error.");
            break;
            case DATA_HEAP_ERR:
                fprintf(fp, "Error declaring heap data.");
            break;
            case BUFF_NULL_ERR:
                fprintf(fp, "Operand queue reserved with corrupted memory [NULL] or unknown type from heap.");
            break;
            case HEAP_UNEX_ERR:
                fprintf(fp, "Heap returned corrupted memory (NULL).");
            break;
            case HEAP_SET_ERR:
                fprintf(fp, "BOXVM internal memory heap data allocation error.");
            break;
            case HEAP_MALL_ERR:
                fprintf(fp, "Non-existent data on heap, unable to allocate memory.");
            break;
            case LOOP_OVERFLOW:
                fprintf(fp, "Memory overflow on loop stack (n > %d).", MAXLOOPSIZE);
            break;
            case LOOP_OUT_ERR:
                fprintf(fp, "Memory underflow on loop stack (n < 0).");
            break;
            case STACK_SET_ERR:
                fprintf(fp, "Failed to set stack data memory.");
            break;
            case STACK_MALL_ERR:
                fprintf(fp, "BOXVM internal error: Error allocating data in stack memory.");
            break;
            case BUFF_MALL_ERR:
                fprintf(fp, "BOXVM internal error: Class <OperationQueue> allocation error.");
            break;
            case FLIST_MAL_ERR:
                fprintf(fp, "BOXVM internal error: Class <FileList> allocation error.");
            break;
            case LOOP_MAL_ERR:
                fprintf(fp, "BOXVM internal error: Class <Loop> allocation error.");
            break;
            case BC_MAL_ERR:
                fprintf(fp, "BOXVM internal error: Class <ByteCode> allocation error.");
            break;
            case UKNOWN_TYPE_ERR:
                fprintf(fp, "Initializing unknown data type error.");
            break;
            case SET_NULL_ERR:
                fprintf(fp, "Setting data memory value with corrupted memory [NULL].");
            break;
            case ERROR_OPEN:
                fprintf(fp, "File opening error. Check if file exist!");
            break;
            case ERROR_READ:
                fprintf(fp, "Cannot write into file opened for reading.");
            break;
            case ERROR_WRITE:
                fprintf(fp, "Cannot read from file opened for writing.");
            break;
            case READ_END_ERR:
                fprintf(fp, "[EOF] detected, unable to read further.");
            break;
            case EMPTY_FILE:
                fprintf(fp, "Cannot read empty file.");
            break;
            case LARGE_FILE_ERR:
                fprintf(fp, "File too big, unable to load into memory.");
            break;
            case ALLRDY_OPEN:
                fprintf(fp, "Unable to open file that is already open.");
            break;
            case PUSH_FILE_ERR:
                fprintf(fp, "Error allocating memory for file.");
            break;
            case FILE_OPER_ERR:
                fprintf(fp, "Unable to execute write/read operation on corrupted file memory [NULL].");
            break;
            case ZERO_VM_ERR:
                fprintf(fp, "Unable to allocate zero elements of virtual memory.");
            break;
            case VM_MALL_ERR:
                fprintf(fp, "BOXVM internal error error: Static virtual memory allocation error.");
            break;
            case QUEUE_OVERFLOW:
                fprintf(fp, "Operand queue overflow (n > %d).", MAXBUFFERSIZE);
            break;
            case ERROR_READ_BOX:
                fprintf(fp, "Error loading BOX program content into memory.");
            break;
		}

		fclose(fp);
	}
}

#endif  //WRITELOGERRORREPORT_H
