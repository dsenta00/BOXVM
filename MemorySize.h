#ifndef MEMORY_SIZE
#define MEMORY_SIZE

#define SIZE_LEVELS (6)

#define SMALL_MEM_CHUNK      (8)
#define MEDIUM_MEM_CHUNK     (32)
#define LARGE_MEM_CHUNK      (128)
#define VERY_LARGE_MEM_CHUNK (4096)
#define HUGE_MEM_CHUNK       (8192)
#define LIMIT_MEM_CHUNK      (65536)

const Size memorySize[SIZE_LEVELS] =
{
    SMALL_MEM_CHUNK,
    MEDIUM_MEM_CHUNK,
    LARGE_MEM_CHUNK,
    VERY_LARGE_MEM_CHUNK,
    HUGE_MEM_CHUNK,
    LIMIT_MEM_CHUNK
};

#endif