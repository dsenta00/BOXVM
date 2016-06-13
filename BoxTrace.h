#ifndef BOX_TRACE_H
#define BOX_TRACE_H
#if defined(DEBUG_MODE) || defined(PRINT_DEBUG_MODE)
#include "BoxInfo.h"
#include "Data.h"
#include "File.h"
#include <thread>
#include <list>
#include <string>

#define TRACE_MAX_INFO (256)

class BoxTrace {
public:
    void open(char *name);
    void add(char *traceGroup, char *info);
    void addTrace(std::string traceGroup);
    void print(char *traceGroup, char *info);
private:
    void addEntry(char *traceGroup, char *info);
    bool traceExist(std::string traceGroup);
    File file;
    std::list<std::string> traceList;
};

void BoxTrace::addTrace(std::string traceGroup)
{
    traceList.push_front(traceGroup);
}

bool BoxTrace::traceExist(std::string traceGroup)
{
    std::list<std::string>::iterator it = traceList.begin();

    while (true)
    {
        if (it == traceList.end())
            return false;

        if (*it == traceGroup)
            return true;

        it++;
    }

    return false;
}

void BoxTrace::open(char *name)
{
    char logNameFull[256];
    sprintf(logNameFull, "%s.log", name);
    file.open(logNameFull, FILE_WRITE, 0);
}

void BoxTrace::addEntry(char *traceGroup, char *info)
{
    Data data(BOX_STRING);
    char logEntry[TRACE_MAX_INFO];
    time_t timeVar;

    time(&timeVar);
    struct tm *time = localtime(&timeVar);

    sprintf(logEntry, "(%d:%d:%d) [%s] %s\n", time->tm_hour,
        time->tm_min,
        time->tm_sec,
        traceGroup,
        info);

    data.setAddress(logEntry);
    file.write(&data);
}

void BoxTrace::add(char *traceGroup, char *info)
{
    if (traceExist(traceGroup))
    {
        std::thread t1([&] { addEntry(traceGroup, info); });
        t1.join();
    }
}

void BoxTrace::print(char *traceGroup, char *info)
{
    char logEntry[TRACE_MAX_INFO];
    time_t timeVar;

    if (traceExist(traceGroup))
    {
        time(&timeVar);
        struct tm *time = localtime(&timeVar);
        printf("(%d:%d:%d) [%s] %s\n",
            time->tm_hour,
            time->tm_min,
            time->tm_sec,
            traceGroup,
            info);
    }
}

BoxTrace boxTrace;
char freeText[TRACE_MAX_INFO];
#endif

#if defined(DEBUG_MODE) || defined(PRINT_DEBUG_MODE)
#define ADD_TRACE(__GROUP) boxTrace.addTrace(__GROUP);
#else
#define ADD_TRACE(__GROUP) ;
#endif

#if defined(DEBUG_MODE)
#define TRACE(__GROUP, __FORMAT, ...) \
    sprintf(freeText, __FORMAT, __VA_ARGS__); \
    boxTrace.add(__GROUP, freeText);
#elif defined(PRINT_DEBUG_MODE)
#define TRACE(__GROUP, __FORMAT, ...) \
    sprintf(freeText, __FORMAT, __VA_ARGS__); \
    boxTrace.print(__GROUP, freeText);
#else
#define TRACE(__GROUP, __FORMAT, ...) ;
#endif

#endif