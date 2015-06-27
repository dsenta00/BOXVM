#ifndef PROGRAMMONITOR_H
#define PROGRAMMONITOR_H
#include "BoxInfo.h"

class ProgramMonitor {
public:
    ProgramMonitor();
    ~ProgramMonitor();
    void SetError(Status);
    void SetPath(char *);
    void WriteErrorReport();
    bool OK();
protected:
    Status status;
    char *path;
};

ProgramMonitor::ProgramMonitor()
{
    status = EVERYTHING_OK;
    path = null;
}

ProgramMonitor::~ProgramMonitor()
{
    if(status)
        this->WriteErrorReport();
}

void ProgramMonitor::SetPath(char *_execpath)
{
    path = _execpath;
}

void ProgramMonitor::SetError(Status _stat)
{
    status = _stat;
}

bool ProgramMonitor::OK()
{
    return !status;
}

void ProgramMonitor::WriteErrorReport()
{
    char *p_path = null;
    FILE *fp = null;

    printf("\n\tFatal runtime error. [ERROR CODE = 0x%08x] (%d)", status, status);
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
        fprintf(fp, "\n\t[ERROR CODE = 0x%08x] (%d)\n\n\t*** ", status, status);

        switch (status)
        {
            case REGISTRYUNEX:
                fprintf(fp, "Trying to do operation on unknown registry count.");
            break;
            case UNDEF_POOL_ERR:
                fprintf(fp, "Undefined pool section.");
            break;
            case POOL_SIZE_ERR:
                fprintf(fp, "Unable to allocate zero or negative size of pool space.");
            break;
            case POOL_RESERVE_ERR:
                fprintf(fp, "BOXVM internal error: Memory pool reservation error.");
            break;
            case ERRBUFFCONT:
                fprintf(fp, "BOXVM internal error: Code segment memory allocation error.");
            break;
            case STATIC_OVERFLOW:
                fprintf(fp, "Static data virtual memory overflow.");
            break;
            case OPER_NULL_ERR:
                fprintf(fp, "Unable to do operation on null memory.");
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
            case DYN_TYPE_ERR:
                fprintf(fp, "Bad dynamic data type declaration.");
            break;
            case STAT_TYPE_ERR:
                fprintf(fp, "Bad static data type declaration.");
            break;
            case INIT_DATA_ERR:
                fprintf(fp, "Data initialization error.");
            break;
            case HEAP_UNEX_ERR:
                fprintf(fp, "Heap returned corrupted memory (null).");
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
            case SET_NULL_ERR:
                fprintf(fp, "Setting data memory value with corrupted memory [null].");
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
            case FILE_OPER_ERR:
                fprintf(fp, "Unable to execute write/read operation on corrupted file memory [null].");
            break;
            case ZERO_VM_ERR:
                fprintf(fp, "Unable to allocate zero elements of virtual memory.");
            break;
            case VM_MALL_ERR:
                fprintf(fp, "BOXVM internal error error: Static virtual memory allocation error.");
            break;
            case ERROR_READ_BOX:
                fprintf(fp, "Error loading BOX program content into memory.");
            break;
        }

        fclose(fp);
    }
}

#endif // PROGRAMMONITOR_H
