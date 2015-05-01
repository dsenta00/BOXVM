#ifndef INVOKEBOX_H
#define INVOKEBOX_H
#include "BoxInfo.h"
#include "ProgramMonitor.h"

class InvokeBox {
public:
	InvokeBox();
	void SetExecute(char *);
	void ReadAll(char *, ProgramMonitor *);
	Bcode GetExecuteCode();
	Bcode GetCodeSegment();
	template <typename T>
	inline void GetNextWord(T *);
protected:
	Bcode codeSeg;
	Bcode p_codeSeg;
};

InvokeBox::InvokeBox()
{
	codeSeg = p_codeSeg = null;
}

Bcode InvokeBox::GetCodeSegment()
{
	return codeSeg;
}

Bcode InvokeBox::GetExecuteCode()
{
	return p_codeSeg - 1;
}

template <typename T>
inline void InvokeBox::GetNextWord(T *_buffer)
{
	*_buffer = *(T *)p_codeSeg;
	p_codeSeg += sizeof(T);
}

void InvokeBox::ReadAll(char *_boxfilepath, ProgramMonitor *monitor)
{
	DSize file_size = 0, read_size = 0;
	FILE *fp = null;

	fp = fopen(_boxfilepath, "r+b");

	if (fp)
	{
		fseek(fp, 0, SEEK_END);
		file_size = ftell(fp);

		if (file_size > MAXFILESIZE)
		{
			SETERR(LARGE_FILE_ERR);
		}
		if (file_size == 0)
		{
			SETERR(EMPTY_FILE);
		}
		else
		{
			p_codeSeg = codeSeg = (Bcode)calloc(file_size + 1, sizeof(Byte));

			if (codeSeg)
			{
				rewind(fp);
				read_size = fread(codeSeg, sizeof(Byte), file_size, fp);

				if (read_size != file_size)
				{
					SETERR(ERROR_READ_BOX);
				}
			}
			else
			{
				SETERR(ERRBUFFCONT);
			}
		}

		fclose(fp);
	}
	else
	{
		SETERR(ERROR_OPEN);
	}
}

#endif
