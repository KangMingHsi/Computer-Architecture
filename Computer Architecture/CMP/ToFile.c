#include "Var.h"
#include "ToFile.h"

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
