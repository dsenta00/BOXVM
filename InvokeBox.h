#ifndef INVOKEBOX_H
#define INVOKEBOX_H
#include "BoxInfo.h"
#include "ProgramMonitor.h"

class InvokeBox {
public:
    void invoke(char *boxFilePath);
    Bcode getPc();
    void read(char *buffer, Size size);
protected:
    Size fetchSize(char *boxFilePath);
    Bcode codeSeg;
    Bcode programCounter;
};

Bcode InvokeBox::getPc()
{
    return programCounter - 1;
}

void InvokeBox::read(char *buffer, Size size)
{
    if (size == 0)
    {
        strcpy(buffer, programCounter);
        programCounter += (strlen(buffer) + 1);
    }
    else
    {
        memcpy(buffer, programCounter, size);
        programCounter += size;
    }
}

Size InvokeBox::fetchSize(char *boxFilePath)
{
    Size size;
    FILE *fp;

    fp = fopen(boxFilePath, "r+b");

    if (!fp)
    {
        SETERR(ERROR_OPEN);
        return 0;
    }

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fclose(fp);

    if (size == 0)
    {
        SETERR(EMPTY_FILE);
    }

    if (size > MAXFILESIZE)
    {
        SETERR(LARGE_FILE_ERR);
    }

    return size;
}

void InvokeBox::invoke(char *boxFilePath)
{
    FILE *fp;
    Size readSize = 0;
    Size fileSize = fetchSize(boxFilePath);

    if (NOK)
    {
        return;
    }

    programCounter = codeSeg = (Bcode)calloc(fileSize, sizeof(Byte));

    if (!codeSeg)
    {
        SETERR(ERR_ALLOC_CS);
        return;
    }

    fp = fopen(boxFilePath, "r+b");
    readSize = fread(codeSeg, sizeof(Byte), fileSize, fp);

    if (readSize != fileSize)
    {
        SETERR(ERRORFILE_READ_BOX);
    }

    fclose(fp);
}

#endif
