#include "struct.h"
void initCMP();
void checkCMP(int);
void checkTLB(TLB[], int, int);
void checkCache();
int checkPT(PageTable[], int, int, int);
int Pagefault(Memory[], int, int);
void UpdateTLB(TLB[], int, int, int);
void UpdatePT(PageTable[], int, int);
void UpdateCache(int, int);
void UpdateMemory(Memory[], int);
