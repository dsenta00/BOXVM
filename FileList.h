#ifndef FILELIST_H
#define FILELIST_H

#include "BoxInfo.h"
#include "ProgramMonitor.h"
#include "File.h"

class FileList {
public:
	FileList();
	~FileList();
    void PushFile(Count, char *, int);
    void SetMonitor(ProgramMonitor *);
    void ReadOperationFileString(Adress, Count);
    void WriteOperationFileString(Adress, Count);
    void ReadAllFile(Adress, Size, Count);
    void GetLine(Adress, Count);
    bool Feof(Count);
    bool IsOpened(Count);
	template <typename T>
    void ReadOperationFile(T *, Count);
	template <typename T>
    void WriteOperationFile(T *, Count);
protected:
    File Head;
    File *pfile;
    ProgramMonitor *monitor;
};

FileList::FileList()
{
    pfile = null;
    monitor = null;
}

void FileList::SetMonitor(ProgramMonitor *_monitor)
{
    monitor = _monitor;
}

void FileList::PushFile(Count _count, char *_path, int _mode)
{
	if (Head.GetCount() == 0)
    {
        Head.Open(_path, _mode, _count);
    }
	else
	{
		pfile = FINDFILE(_count);

        if (!pfile)
        {
            pfile = new File();

            if (pfile)
            {
                pfile->Open(_path, _mode, _count);

                if (EOK)
                {
                    pfile->next = Head.next;
                    Head.next = pfile;
                }
            }
            else
            {
                SETERR(PUSH_FILE_ERR);
            }
        }
		else
        {
            SETERR(ALLRDY_OPEN);
        }
    }
}

bool FileList::Feof(Count _count)
{
    pfile = FINDFILE(_count);

    if(!pfile->Getfp())
    {
        if(!feof(pfile->Getfp()))
        {
            return true;
        }
    }
    else
    {
        SETERR(FILE_OPER_ERR);
    }

    return false;
}

bool FileList::IsOpened(Count _count)
{
    pfile = FINDFILE(_count);

    if(pfile->Getfp())
    {
        return true;
    }

    return false;
}

template <typename T>
void FileList::ReadOperationFile(T *read_data, Count _count)
{
	pfile = FINDFILE(_count);

    if (pfile)
    {
        if(pfile->GetMode() == _READ)
        {
            if(!feof(pfile->Getfp()))
            {
                pfile->ReadOperationFile(read_data);
            }
            else
            {
                SETERR(READ_END_ERR);
            }
        }
        else
        {
            SETERR(ERROR_READ);
        }
    }
	else
    {
        SETERR(FILE_OPER_ERR);
    }
}

template <typename T>
void FileList::WriteOperationFile(T *write_data, Count _count)
{
    pfile = FINDFILE(_count);

    if (pfile)
    {
        if(pfile->GetMode() != _READ)
        {
            pfile->WriteOperationFile(write_data);
        }
        else
        {
            SETERR(ERROR_WRITE);
        }
    }
    else
    {
        SETERR(FILE_OPER_ERR);
    }
}

void FileList::ReadOperationFileString(Adress read_data, Count _count)
{
    pfile = FINDFILE(_count);

    if (pfile)
    {
        if(pfile->GetMode() == _READ)
        {
            if(!feof(pfile->Getfp()))
            {
                pfile->ReadOperationFileString(read_data);
            }
            else
            {
                SETERR(READ_END_ERR);
            }
        }
        else
        {
            SETERR(ERROR_READ);
        }
    }
    else
    {
        SETERR(FILE_OPER_ERR);
    }
}

void FileList::WriteOperationFileString(Adress write_data, Count _count)
{
    pfile = FINDFILE(_count);

    if (pfile)
    {
        if(pfile->GetMode() != _READ)
        {
            pfile->WriteOperationFileString(write_data);
        }
        else
        {
            SETERR(ERROR_WRITE);
        }
    }
    else
    {
        SETERR(FILE_OPER_ERR);
    }
}

void FileList::ReadAllFile(Adress read_data, Size _size, Count _count)
{
    pfile = FINDFILE(_count);

    if (pfile)
    {
        if(pfile->GetMode() == _READ)
        {
            pfile->ReadAllFile(read_data, _size);
        }
        else
        {
            SETERR(ERROR_READ);
        }
    }
    else
    {
        SETERR(FILE_OPER_ERR);
    }
}

void FileList::GetLine(Adress read_data, Count _count)
{
    pfile = FINDFILE(_count);

    if (pfile)
    {
        if(pfile->GetMode() == _READ)
        {
            if(!feof(pfile->Getfp()))
            {
                pfile->GetLine(read_data);
            }
            else
            {
                SETERR(READ_END_ERR);
            }
        }
        else
        {
            SETERR(ERROR_READ);
        }
    }
    else
    {
        SETERR(FILE_OPER_ERR);
    }
}

FileList::~FileList()
{
	while (Head.next)
	{
		pfile = Head.next;
		Head.next = pfile->next;
		delete pfile;
	}

    pfile = null;
}

#endif
