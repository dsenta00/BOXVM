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
	pfile = NULL;
    monitor = NULL;
}

void FileList::SetMonitor(ProgramMonitor *_monitor)
{
    monitor = _monitor;
}

void FileList::PushFile(Count _count, char *_path, int _mode)
{
	if (Head.GetCount() == 0)
        SETERR(Head.Open(_path, _mode, _count));
	else
	{
		pfile = FINDFILE(_count);

		if (pfile)
            SETERR(ALLRDY_OPEN);
		else
			pfile = new File();

        if (EOK)
		{
			if (pfile)
			{
                SETERR(pfile->Open(_path, _mode, _count));

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
    }
}

template <typename T>
void FileList::ReadOperationFile(T *read_data, Count _count)
{
	pfile = FINDFILE(_count);

	if (!pfile)
        SETERR(FILE_OPER_ERR);
	else
        SETERR(pfile->ReadOperationFile(read_data));
}

template <typename T>
void FileList::WriteOperationFile(T *write_data, Count _count)
{
	pfile = FINDFILE(_count);

	if (!pfile)
        SETERR(FILE_OPER_ERR);
	else
        SETERR(pfile->WriteOperationFile(write_data));
}

void FileList::ReadOperationFileString(Adress read_data, Count _count)
{
	pfile = FINDFILE(_count);

	if (!pfile)
        SETERR(FILE_OPER_ERR);
	else
        SETERR(pfile->ReadOperationFileString(read_data));
}

void FileList::WriteOperationFileString(Adress read_data, Count _count)
{
	pfile = FINDFILE(_count);

	if (!pfile)
        SETERR(FILE_OPER_ERR);
	else
        SETERR(pfile->WriteOperationFileString(read_data));
}

void FileList::ReadAllFile(Adress read_data, Size _size, Count _count)
{

	pfile = FINDFILE(_count);

	if (!pfile)
        SETERR(FILE_OPER_ERR);
	else
        SETERR(pfile->ReadAllFile(read_data, _size));
}

void FileList::GetLine(Adress read_data, Count _count)
{
	pfile = FINDFILE(_count);

	if (!pfile)
        SETERR(FILE_OPER_ERR);
	else
        SETERR(pfile->GetLine(read_data));
}

FileList::~FileList()
{
	while (Head.next)
	{
		pfile = Head.next;
		Head.next = pfile->next;
		delete pfile;
	}

	pfile = NULL;
}

#endif
