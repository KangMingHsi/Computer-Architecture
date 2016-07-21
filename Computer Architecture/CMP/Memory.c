#include "Var.h"
#include "Memory.h"

int checkMem(int gap){
    if((Pos) > 1024 - gap){
        memOverflow = 1;
    }

    if(Pos % (gap)){
        misalignment = 1;
    }
    if(memOverflow || misalignment){
        return 0;
    }

    return 1;
}
