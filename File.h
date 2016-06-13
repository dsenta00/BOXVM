#ifndef FILE_H
#define FILE_H
#include "BoxInfo.h"
#include "ProgramMonitor.h"
#include "Data.h"

#define FILE_UNOPEN 0 // 00000000
#define FILE_READ   1 // 00000001
#define FILE_WRITE  2 // 00000010
#define FILE_APPEND 6 // 00000110

class File {
public:
    File();
    ~File();
    bool assertRead();
    bool assertWrite();
    bool isOpen();
    void open(char *, int, Count);
    void read(Data *data);
    void write(Data *data);
    void readLine(Data *data);
    void invokeFile(char *, Size);
    bool isCount(Count count);
    Type getMode();
    FILE *getFp();
protected:
    FILE *fp;
    Type mode;
};

File::File()
{
    memset(this, 0, sizeof(File));
}

bool File::isOpen()
{
    return FILE_UNOPEN != mode;
}

bool File::assertRead()
{
    if (!(FILE_READ & mode))
    {
        SETERR(ERRORFILE_READ);
        return false;
    }

    if (feof(fp))
    {
        SETERR(READ_END_ERR);
        return false;
    }

    return true;
}

bool File::assertWrite()
{
    if (!(FILE_WRITE & mode))
    {
        SETERR(ERRORFILE_WRITE);
        return false;
    }

    return true;
}

FILE *File::getFp()
{
    return fp;
}

Type File::getMode()
{
    return mode;
}

void File::open(char *path, int mode, Count count)
{
    this->mode = mode;

    switch (mode)
    {
    case FILE_WRITE:
        fp = fopen(path, "w+");
        break;
    case FILE_READ:
        fp = fopen(path, "r+b");
        break;
    case FILE_APPEND:
        fp = fopen(path, "a");
        break;
    }

    if (!fp)
    {
        SETERR(ERROR_OPEN);
        this->mode = FILE_UNOPEN;
    }
}

void File::read(Data *data)
{
    Address address = data->getAddress();

    if (assertRead())
    {
        switch (data->getType())
        {
        case BOX_CHAR:
            fscanf(fp, " %c", address);
            break;
        case BOX_INT:
            fscanf(fp, " %d", (int *)address);
            break;
        case BOX_FLOAT:
            fscanf(fp, " %f", (float *)address);
            break;
        case BOX_DOUBLE:
            fscanf(fp, " %lf", (double *)address);
            break;
        case BOX_LONG:
            fscanf(fp, " %ld", (long *)address);
            break;
        case BOX_STRING:
            fscanf(fp, " %s", address);
            break;
        }
    }
}

void File::write(Data *data)
{
    Address address = data->getAddress();

    if (assertWrite())
    {
        switch (data->getType())
        {
        case BOX_CHAR:
            fprintf(fp, "%c", *address);
            break;
        case BOX_INT:
            fprintf(fp, "%d", *(int *)address);
            break;
        case BOX_FLOAT:
            fprintf(fp, "%f", *(float *)address);
            break;
        case BOX_DOUBLE:
            fprintf(fp, "%lf", *(double *)address);
            break;
        case BOX_LONG:
            fprintf(fp, "%ld", *(long *)address);
            break;
        case BOX_STRING:
            fprintf(fp, "%s", address);
            break;
        }
    }
}

void File::readLine(Data *data)
{
    if (assertRead())
    {
        fgets(data->getAddress(), BLOCK_SIZE, fp);
    }
}

void File::invokeFile(char *container, Size container_size)
{
    Size file_size = 0;

    if (!assertRead())
    {
        return;
    }

    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp);

    if (file_size >= container_size)
    {
        SETERR(LARGE_FILE_ERR);
    }

    rewind(fp);

    if (file_size == 0)
    {
        memset(container, 0, container_size);
        return;
    }

    fread(container, sizeof(char), file_size, fp);
}

File::~File()
{
    if (fp)
    {
        fclose(fp);
    }
}
#endif
