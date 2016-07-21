#ifndef _STRUCT_H_
#define _STRUCT_H_
typedef struct HitAndMiss{
    unsigned hitNum, missNum;
}HitAndMiss;

typedef struct initValues{
    int iMemSize, dMemSize, iMemPageSize, dMemPageSize, iCacheTotalSize, iCacheBlockSize, iCacheSet, dCacheTotalSize, dCacheBlockSize, dCacheSet;
}initValues;

typedef struct TLB{
    int VPN, PPN, PutInCycle, valid;
}TLB;

typedef struct PageTable{
    int valid, PPN;
}PageTable;

typedef struct Cache{
    int valid, tag, MRU;
}Cache;

typedef struct Memory{
    int PutInCycle, valid;
}Memory;

typedef struct CacheEntry{
    int row, col;
}CacheEntry;

#endif
