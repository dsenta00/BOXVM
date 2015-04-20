TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    BOXVM.cpp

HEADERS += \
    BOXVM.h \
    FileOperationsMacro.h \
    ByteCode.h \
    TestBox.h \
    DataTree.h \
    MemoryPool.h \
    Loop.h \
    File.h \
    Stack.h \
    ExecuteMacro.h \
    CPUTime.h \
    FileList.h \
    BoxInfo.h \
    BoxProgram.h \
    Heap.h \
    Execute.h \
    VirtualStackMemory.h \
    InvokeBox.h \
    Data.h \
    DataNode.h \
    ProgramMonitor.h \
    ALU.h \
    Registry.h

