#ifndef FILE_H
#define FILE_H

#include "BoxInfo.h"
#include "FileOperationsMacro.h"

class File
{
    FILE *fp;
    Count count;
    int mode;
public:
	File *next;

	File();
	~File();

    Status Open(char *, int, Count);
    Status ReadOperationFileString(char *);
    Status WriteOperationFileString(char *);
    Status GetLine(char *);
    Status ReadAllFile(char *, DSize);
    Count GetCount();

	WRITEOPDECL(int)
	WRITEOPDECL(short)
	WRITEOPDECL(long)
	WRITEOPDECL(char)
	WRITEOPDECL(float)
	WRITEOPDECL(double)
	WRITEOPDECL(char *)
	READOPDECL(int)
	READOPDECL(short)
	READOPDECL(long)
	READOPDECL(char)
	READOPDECL(float)
	READOPDECL(double)
};

File::File()
{
    fp = NULL;
    mode = _UNOPEN;
	count = 0;
	next = NULL;
}

Status File::Open(char *_path, int _mode, Count _count)
{
	count = _count;
    mode = _mode;

    switch(mode)
    {
        case _WRITE:
            fp = fopen(_path, "w+");
        break;
        case _READ:
            fp = fopen(_path, "r");
        break;
        case _APPEND:
            fp = fopen(_path, "a");
        break;
    }

    if (!fp)
        return ERROR_OPEN;
	else
        return EVERYTHING_OK;
}

WRITEOP(int, "%d")
WRITEOP(short, "%hd")
WRITEOP(long, "%ld")
WRITEOP(char, "%c")
WRITEOP(float, "%f")
WRITEOP(double, "%lf")
WRITEOP(char *, "%s")
READOP(int, " %d")
READOP(short, " %hd")
READOP(long, " %ld")
READOP(char, " %c")
READOP(float, " %f")
READOP(double, " %lf")

Status File::ReadOperationFileString(char *_data)
{
    if (mode == _READ)
	{
		if (!feof(fp))
        {
			fscanf(fp, " %s", _data);
            return EVERYTHING_OK;
        }
		else
            return READ_END_ERR;
    }
    else
        return ERROR_READ;
}

Status File::WriteOperationFileString(char *_data)
{
    if (mode != _READ)
    {
        fprintf(fp, "%s", _data);
        return EVERYTHING_OK;
    }
    else
        return ERROR_WRITE;
}

Status File::GetLine(char *buffer)
{
	if (mode != _READ)
        return ERROR_READ;
    else if (!fgets(buffer, BLOCK_SIZE, fp))
        return READ_END_ERR;
    else
        return EVERYTHING_OK;
}

Status File::ReadAllFile(char *container, DSize container_size)
{
    DSize file_size = 0;

	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp);

    if (file_size < container_size)
	{
		rewind(fp);

        if (!fread(container, sizeof(char), file_size, fp))
            return EMPTY_FILE;
        else
            return EVERYTHING_OK;
	}
    else
        return LARGE_FILE_ERR;
}

Count File::GetCount()
{
	return count;
}

File::~File()
{
    if (fp)
		fclose(fp);
}

#endif
