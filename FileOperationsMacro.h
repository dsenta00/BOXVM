#ifndef FILEOPERATIONSMACRO_H
#define FILEOPERATIONSMACRO_H

#define WRITEOPDECL(__TYPE) Status WriteOperationFile(__TYPE *);
#define READOPDECL(__TYPE)  Status ReadOperationFile(__TYPE *);

#define WRITEOP(__TYPE, __FORMAT)                       \
    Status File::WriteOperationFile(__TYPE *_data)      \
    {                                                   \
        if (mode != _READ)                              \
        {                                               \
            fprintf(fp, __FORMAT, *_data);              \
            return EVERYTHING_OK;                       \
        }                                               \
        else                                            \
            return ERROR_WRITE;                         \
    }

#define READOP(__TYPE, __FORMAT)                        \
    Status File::ReadOperationFile(__TYPE *_data)       \
    {                                                   \
        if (mode == _READ)                              \
        {                                               \
            if (!feof(fp))                              \
            {                                           \
                fscanf(fp, __FORMAT, _data);            \
                return EVERYTHING_OK;                   \
            }                                           \
            else                                        \
                return READ_END_ERR;                    \
        }                                               \
        else                                            \
            return ERROR_READ;                          \
    }

#define FINDFILE(_count)    &Head;                      \
while(pfile != NULL && pfile->GetCount() != _count)     \
    pfile = pfile->next;

#endif // FILEOPERATIONSMACRO_H
