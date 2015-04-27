#ifndef FILEOPERATIONSMACRO_H
#define FILEOPERATIONSMACRO_H

enum FILE_MODES
{
    _UNOPEN =	   -1,  // Unopened file stream.
    _READ =			0,  // File stream opened for read.
    _WRITE =		1,  // File stream opened for write.
    _APPEND =		2   // File stream opened for append.
};

#define WRITEOPDECL(__TYPE) void WriteOperationFile(__TYPE *);
#define READOPDECL(__TYPE)  void ReadOperationFile(__TYPE *);

#define WRITEOP(__TYPE, __FORMAT)                       \
    void File::WriteOperationFile(__TYPE *_data)      \
    {                                                   \
            fprintf(fp, __FORMAT, *_data);              \
                  \
    }

#define READOP(__TYPE, __FORMAT)                        \
    void File::ReadOperationFile(__TYPE *_data)       \
    {                                                   \
            fscanf(fp, __FORMAT, _data);                \
    }

#define FINDFILE(_count)    &Head;                      \
while(pfile && pfile->GetCount() != _count)     \
    pfile = pfile->next;

#endif // FILEOPERATIONSMACRO_H
