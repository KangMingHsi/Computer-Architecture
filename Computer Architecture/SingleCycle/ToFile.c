#include "Var.h"
#include "ToFile.h"
void printSnapShot(){
    int i = 0;
    fprintf(snap,"cycle %u\n", cycle++);
    for(i = 0; i < 32; i++){
        fprintf(snap,"$%02d: 0x%08X\n", i, reg[i]);
    }
    fprintf(snap,"PC: 0x%08X\n\n\n", PC);
}
void printError(){
    if(writeMemZero){
        writeMemZero = 0;
        fprintf(err, "In cycle %d: Write $0 Error\n", cycle);
    }

    if(numberOverflow){
        numberOverflow = 0;
        fprintf(err,"In cycle %d: Number Overflow\n", cycle);
    }

    if(memOverflow){
        memOverflow = 0;
        fprintf(err,"In cycle %d: Address Overflow\n", cycle);
    }

    if(misalignment){
        misalignment = 0;
        fprintf(err,"In cycle %d: Misalignment Error\n", cycle);
    }
}
