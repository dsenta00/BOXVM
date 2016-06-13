#ifndef FILELIST_H
#define FILELIST_H

#include "BoxInfo.h"
#include "ProgramMonitor.h"
#include "Data.h"
#include "File.h"
#include "OrderedCollection.h"

class FileList : public OrderedCollection <File> {
public:
    File *assertFind(Count count);
    void push(Count, char *, int);
    void invokeFile(Data *, Count);
    void readLine(Data *, Count);
    void read(Data *, Count);
    void write(Data *, Count);
};

File *FileList::assertFind(Count count)
{
    File *file = find(count);

    if (NULL == file)
    {
        SETERR(FILE_OPER_ERR);
    }

    return file;
}

void FileList::push(Count count, char *path, int mode)
{
    File *file = find(count);

    if (file != NULL && file->isOpen())
    {
        rewind(file->getFp());
        return;
    }

    file = new File();
    file->open(path, mode, count);

    if (NOK)
    {
        delete file;
        return;
    }

    add(count, file);
}

void FileList::read(Data *data, Count count)
{
    File *file = assertFind(count);

    if (NOK)
    {
        return;
    }

    file->read(data);
}

void FileList::write(Data *data, Count count)
{
    File *file = assertFind(count);

    if (NOK)
    {
        return;
    }


    file->write(data);
}

void FileList::invokeFile(Data *data, Count count)
{
    File *file = assertFind(count);

    if (NOK)
    {
        return;
    }

    file->invokeFile(data->getAddress(), data->getSize());
}

void FileList::readLine(Data *data, Count count)
{
    File *file = assertFind(count);

    if (NOK)
    {
        return;
    }

    file->readLine(data);
}

#endif
