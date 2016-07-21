#include "Var.h"
#include "Memory.h"
#include "define.h"
#include "translate.h"
void initForwarding(){
    Forwarding.forwardingRs_EX = Forwarding.forwardingRs_ID = Forwarding.forwardingRt_EX = Forwarding.forwardingRt_ID = 0;
}

int checkMem(int gap){
    if((tmpEX) > 1024 - gap){
        memOverflow = 1;
    }
    if(tmpEX % (gap)){
        misalignment = 1;
    }
    if(memOverflow || misalignment){
        return 0;
    }

    return 1;
}

void find_nearest_value(char *a, char *b, int type){
    unsigned tmp = IDBuffer.instruction << 26 >> 26;

    if(IDBuffer.rs > 0){

        if((type != lui) && !(type == Rtype && (tmp == sll || tmp == srl || tmp == sra))){
            if(EXBuffer.opcode == Rtype && EXBuffer.rd == IDBuffer.rs){
                *a = 1;
            }else if(between(EXBuffer.opcode, 8, 59) && !between(EXBuffer.opcode, 40, 43) && EXBuffer.rt == IDBuffer.rs){
                *a = 1;
            }else if(EXBuffer.opcode == jal && 31 == IDBuffer.rs){
                *a = 1;
            }else if(MEMBuffer.opcode == Rtype && (MEMBuffer.instruction << 26 >> 26 != jr) && MEMBuffer.rd == IDBuffer.rs){
                *a = 2;
            }else if(between(MEMBuffer.opcode, 8, 59) && !between(MEMBuffer.opcode, 40, 43) && MEMBuffer.rt == IDBuffer.rs){
                *a = 2;
            }else if(MEMBuffer.opcode == jal && 31 == IDBuffer.rs){
                *a = 2;
            }else{
                *a = 0;
            }
        }
    }

    if((type == Rtype && tmp != jr) || between(type, 40, 43) || between(type, 4, 5)){
        if(IDBuffer.rt > 0){
            if(EXBuffer.opcode == Rtype && EXBuffer.rd == IDBuffer.rt){
                *b = 1;
            }else if(between(EXBuffer.opcode, 8, 59)&& !between(EXBuffer.opcode, 40, 43) && EXBuffer.rt == IDBuffer.rt){
                *b = 1;
            }else if(EXBuffer.opcode == jal && 31 == IDBuffer.rt){
                *b = 1;
            }else if(MEMBuffer.opcode == Rtype && (MEMBuffer.instruction << 26 >> 26 != jr) && MEMBuffer.rd == IDBuffer.rt){
                *b = 2;
            }else if(between(MEMBuffer.opcode, 8, 59) && !between(MEMBuffer.opcode, 40, 43) && MEMBuffer.rt == IDBuffer.rt){
                *b = 2;
            }else if(MEMBuffer.opcode == jal && 31 == IDBuffer.rt){
                *b = 2;
            }else{
                *b = 0;
            }
        }
    }
}
