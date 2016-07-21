#include "Var.h"
#include "ToFile.h"
void printSnapShot(){
    int i = 0;
    fprintf(snap,"cycle %u\n", cycle++);
    for(i = 0; i < 32; i++){
        if(printPlace == i){
            fprintf(snap,"$%02d: 0x%08X\n", i, printValue);
            printPlace = 33;
        }else
            fprintf(snap,"$%02d: 0x%08X\n", i, reg[i]);
    }
    fprintf(snap,"PC: 0x%08X\n", PC);
    fprintf(snap,"IF: 0x%08X", IFBuffer.instruction);
    if(flush){
        fprintf(snap," to_be_flushed");
        PC = newPC;
    }else if(IFBuffer.stall){
        fprintf(snap," to_be_stalled");
    }
    fprintf(snap,"\nID: %s", IDBuffer.out);
    if(IDBuffer.stall){
        fprintf(snap," to_be_stalled");
    }else{
        if(Forwarding.forwardingRs_ID > 0){
            fprintf(snap," fwd_EX-DM_rs_$%d", Forwarding.forwardingRs_ID);
            Forwarding.forwardingRs_ID = 0;
        }
        if(Forwarding.forwardingRt_ID > 0){
            fprintf(snap," fwd_EX-DM_rt_$%d", Forwarding.forwardingRt_ID);
            Forwarding.forwardingRt_ID = 0;
        }
    }
    fprintf(snap,"\nEX: %s", EXBuffer.out);
    if(Forwarding.forwardingRs_EX > 0){
        fprintf(snap," fwd_EX-DM_rs_$%d", Forwarding.forwardingRs_EX);
        Forwarding.forwardingRs_EX = 0;
    }
    if(Forwarding.forwardingRt_EX > 0){
        fprintf(snap," fwd_EX-DM_rt_$%d", Forwarding.forwardingRt_EX);
        Forwarding.forwardingRt_EX = 0;
    }


    fprintf(snap,"\nDM: %s\n", MEMBuffer.out);
    fprintf(snap,"WB: %s\n\n\n", WBBuffer.out);
}
void printError(){
    if(writeMemZero){
        writeMemZero = 0;
        fprintf(err, "In cycle %d: Write $0 Error\n", cycle);
    }

    if(memOverflow){
        memOverflow = 0;
        fprintf(err,"In cycle %d: Address Overflow\n", cycle);
    }

    if(misalignment){
        misalignment = 0;
        fprintf(err,"In cycle %d: Misalignment Error\n", cycle);
    }

    if(numberOverflow){
        numberOverflow = 0;
        fprintf(err,"In cycle %d: Number Overflow\n", cycle);
    }
}
