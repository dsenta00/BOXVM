#ifndef PROGRAMMONITOR_H
#define PROGRAMMONITOR_H
#include "BoxInfo.h"

enum ERROR_CODES
{
    EVERYTHING_OK = 0,
    ERROR_OPEN,
    ERRORFILE_READ,
    ERRORFILE_WRITE,
    READ_END_ERR,
    EMPTY_FILE,
    LARGE_FILE_ERR,
    FILE_OPER_ERR,
    UKNOWN_OPER_ERR,
    DIV_NULL_ERR,
    ERR_ALLOC_CS,
    POOL_RESERVE_ERR,
    ERRORFILE_READ_BOX,
    MEM_ALOC_ERROR
};

const char *errorCodes[256]
{
    "", // EVERYTHING_OK
        "Failed to open file. File doesn't exist or you don't have permissions", // ERROR_OPEN
        "Cannot read from file opened for writing", // ERRORFILE_READ
        "Cannot write into file opened for reading.", // ERRORFILE_WRITE
        "Reached end of file, can not read further", // READ_END_ERR
        "Execute box file is empty", // EMPTY_FILE
        "File to large to read", // LARGE_FILE_ERR
        "Not found reference to file", // FILE_OPER_ERR
        "Trying to execute an unknown bytecode operation.", // UKNOWN_OPER_ERR
        "Trying to divide with with zero", // DIV_NULL_ERR
        "Code segment allocation error", // ERR_ALLOC_CS
        "Not enough resource to dynamicaly allocate memory pool", // POOL_RESERVE_ERR
        "Not enough resource to allocate data" // MEM_ALOC_ERROR
};

class ProgramMonitor {
public:
    ProgramMonitor();
    ~ProgramMonitor();
    void setError(Status);
    Status getStatus();
    void setLogPath(char *);
    void errorReport(FILE *);
    void writeErrorReport();
    bool OK();
    bool notOK();
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
    if (status)
        this->writeErrorReport();
}

void ProgramMonitor::setLogPath(char *execPath)
{
    path = execPath;
}

void ProgramMonitor::setError(Status stat)
{
    status = stat;
}

Status ProgramMonitor::getStatus()
{
    return status;
}

bool ProgramMonitor::OK()
{
    return status == 0;
}

bool ProgramMonitor::notOK()
{
    return status > 0;
}

void ProgramMonitor::errorReport(FILE *stream)
{
    fprintf(stream, "\n BOXVM RUNTIME ERROR REPORT:");
    fprintf(stream, "\n [ERROR CODE = 0x%X] (%d) (%s)\n\n\t*** ", status, status, errorCodes[status]);
}

void ProgramMonitor::writeErrorReport()
{
    char *ppath = null;
    FILE *fp = null;

    ppath = strchr(path, '.');

    if (ppath)
    {
        strcpy(ppath, ".logbox");
        fp = fopen(path, "w+");

        if (fp)
        {
            errorReport(fp);
            fclose(fp);
        }
    }

    errorReport(stdout);
}

ProgramMonitor programMonitor;

#define SETERR(__ERROR)     programMonitor.setError(__ERROR)
#define EOK                 programMonitor.OK()
#define NOK					programMonitor.notOK()

#endif // PROGRAMMONITOR_H
