#ifndef INVOKEBOX_H
#define INVOKEBOX_H
#include "BoxInfo.h"

class InvokeBox
{
    Bcode codeSeg;
    Bcode p_codeSeg;
public:
    InvokeBox();
    ~InvokeBox();

    Status ReadAll(char *);
    Bcode GetExecuteCode();
    Bcode GetCodeSegment();
	template <typename T>
    inline void GetNextWord(T *);
};

InvokeBox::InvokeBox()
{
    p_codeSeg = codeSeg = NULL;
}

InvokeBox::~InvokeBox()
{
    p_codeSeg = codeSeg = NULL; //Koristi se u ByteCode, stoga ne smijes oslobadjat!!!
}

Status InvokeBox::ReadAll(char *_boxfilepath)
{
    Status status = EVERYTHING_OK;
    DSize file_size = 0, read_size = 0;
	FILE *fp = NULL;

	fp = fopen(_boxfilepath, "r+b");

	if (fp != NULL)
	{
		fseek(fp, 0, SEEK_END);
		file_size = ftell(fp);

		if (file_size > MAXFILESIZE)
			status = LARGE_FILE_ERR;
		else if (file_size == 0)
			status = EMPTY_FILE;
		else
		{
            p_codeSeg = codeSeg = (Bcode)calloc(file_size + 1, sizeof(char));

            if (codeSeg != NULL)
            {
				rewind(fp);
                read_size = fread(codeSeg, sizeof(char), file_size, fp);

				if (read_size == 0 || read_size != file_size)
					status = ERROR_READ_BOX;
			}
			else
				status = ERRBUFFCONT;
		}

		fclose(fp);
	}
	else
		status = ERROR_OPEN;

	return status;
}

Bcode InvokeBox::GetCodeSegment()
{
    return codeSeg;
}

Bcode InvokeBox::GetExecuteCode()
{
    return p_codeSeg;
}

template <typename T>
inline void InvokeBox::GetNextWord(T *_buffer)
{
    *_buffer = *(T *)p_codeSeg;
    p_codeSeg += sizeof(T);
}

#endif
