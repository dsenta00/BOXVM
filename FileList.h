#ifndef FILELIST_H
#define FILELIST_H

#include "BoxInfo.h"
#include "File.h"

class FileList
{
	File Head;
	File *pfile;
    Status status;
public:
	FileList();
	~FileList();

    Status PushFile(Count, char *, int);
    Status ReadOperationFileString(Adress, Count);
    Status WriteOperationFileString(Adress, Count);
    Status ReadAllFile(Adress, Size, Count);
    Status GetLine(Adress, Count);

	template <typename T>
    Status ReadOperationFile(T *, Count);

	template <typename T>
    Status WriteOperationFile(T *, Count);
};

FileList::FileList()
{
	memset(&Head, 0, sizeof(File));
	Head.next = NULL;
	pfile = NULL;
	status = EVERYTHING_OK;
}

Status FileList::PushFile(Count _count, char *_path, int _mode)
{
    if (Head.GetCount() == 0)
        status = Head.Open(_path, _mode, _count);
	else
	{
		pfile = FINDFILE(_count);

		if (pfile != NULL)
			status = ALLRDY_OPEN;
		else
			pfile = new File();

        if (status == EVERYTHING_OK)
        {
            if (pfile != NULL)
            {
                status = pfile->Open(_path, _mode, _count);

                if (status == EVERYTHING_OK)
                {
                    pfile->next = Head.next;
                    Head.next = pfile;
                }
            }
            else
                status = PUSH_FILE_ERR;
        }
	}

	return status;
}

template <typename T>
Status FileList::ReadOperationFile(T *read_data, Count _count)
{
    pfile = FINDFILE(_count);

	if (pfile == NULL)
		status = FILE_OPER_ERR;
	else
		status = pfile->ReadOperationFile(read_data);

	return status;
}

template <typename T>
Status FileList::WriteOperationFile(T *write_data, Count _count)
{
    pfile = FINDFILE(_count);

	if (pfile == NULL)
		status = FILE_OPER_ERR;
	else
		status = pfile->WriteOperationFile(write_data);

	return status;
}

Status FileList::ReadOperationFileString(Adress read_data, Count _count)
{
    pfile = FINDFILE(_count);

	if (pfile == NULL)
		status = FILE_OPER_ERR;
	else
		status = pfile->ReadOperationFileString(read_data);

	return status;
}

Status FileList::WriteOperationFileString(Adress read_data, Count _count)
{
    pfile = FINDFILE(_count);

	if (pfile == NULL)
		status = FILE_OPER_ERR;
	else
		status = pfile->WriteOperationFileString(read_data);

	return status;
}

Status FileList::ReadAllFile(Adress read_data, Size _size, Count _count)
{

    pfile = FINDFILE(_count);

	if (pfile == NULL)
		status = FILE_OPER_ERR;
	else
		status = pfile->ReadAllFile(read_data, _size);

	return status;
}

Status FileList::GetLine(Adress read_data, Count _count)
{
    pfile = FINDFILE(_count);

	if (pfile == NULL)
		status = FILE_OPER_ERR;
	else
		status = pfile->GetLine(read_data);

	return status;
}

FileList::~FileList()
{
	while (Head.next != NULL)
	{
		pfile = Head.next;
		Head.next = pfile->next;
		delete pfile;
	}

	pfile = NULL;
}

#endif
