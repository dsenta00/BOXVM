#ifndef FILE_H
#define FILE_H

#include "BoxInfo.h"
#include "ProgramMonitor.h"
#include "FileOperationsMacro.h"

class File {
public:
	File();
	File(ProgramMonitor *);
	~File();
	void Open(char *, int, Count);
	void ReadOperationFileString(char *);
	void WriteOperationFileString(char *);
	void GetLine(char *);
	void ReadAllFile(char *, DSize);
	Count GetCount();
	Type GetMode();
	FILE *Getfp();

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

		File *next;
protected:
	FILE *fp;
	Count count;
	Type mode;
	ProgramMonitor *monitor;
};

File::File()
{
	memset(this, 0, sizeof(File));
}

File::File(ProgramMonitor *_monitor)
{
	memset(this, 0, sizeof(File));
	monitor = _monitor;
}

FILE *File::Getfp()
{
	return fp;
}

Type File::GetMode()
{
	return mode;
}

void File::Open(char *_path, int _mode, Count _count)
{
	count = _count;
	mode = _mode;

	switch (mode)
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
	{
		mode = _UNOPEN;
	}
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

void File::ReadOperationFileString(char *_data)
{
	fscanf(fp, " %s", _data);
}

void File::WriteOperationFileString(char *_data)
{
	fprintf(fp, "%s", _data);
}

void File::GetLine(char *buffer)
{
	fgets(buffer, BLOCK_SIZE, fp);
}

void File::ReadAllFile(char *container, DSize container_size)
{
	DSize file_size = 0;

	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp);

	if (file_size < container_size)
	{
		rewind(fp);

		if (!fread(container, sizeof(char), file_size, fp))
		{
			SETERR(EMPTY_FILE);
		}
	}
	else
	{
		SETERR(LARGE_FILE_ERR);
	}
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
