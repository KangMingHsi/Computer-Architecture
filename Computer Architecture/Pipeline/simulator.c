#include "define.h"
#include "IO.h"
#include "Var.h"
#include "ToFile.h"
#include "Memory.h"
#include "translate.h"
#include <string.h>
#include <stdlib.h>

void Func(unsigned int ins, char* out, int mode){
    func = (ins << 26) >> 26;
    switch(func){
        case add:
            strcpy(out, "ADD");
            if(mode == 2){
                signRS = EXBuffer.a >> 31; signRT = EXBuffer.b >> 31;
                tmpEX = EXBuffer.a + EXBuffer.b;
                signCons = tmpEX >> 31;
                //printf("!!!0x%08x, 0x%08x, 0x%08x\n", tmpEX, EXBuffer.a, EXBuffer.b);
                if(signRS == signRT && signRS != signCons){
                    numberOverflow = 1;
                }
            }else if(mode == 3){
                tmpMEM = tmpEX;
            }else if(mode == 4){
                if(WBBuffer.rd == 0){
                    writeMemZero = 1;
                }else{
                    printPlace = WBBuffer.rd;
                    printValue = reg[printPlace];
                    reg[WBBuffer.rd] = tmpMEM;
                }
            }
            break;
        case sub:
            strcpy(out, "SUB");
            if(mode == 2){
                signRS = EXBuffer.a >> 31; signRT = (-EXBuffer.b) >> 31;
                tmpEX = EXBuffer.a - EXBuffer.b;
                signCons = tmpEX >> 31;

                if(signRS == signRT && signRS != signCons){
                    numberOverflow = 1;
                }
            }else if(mode == 3){
                tmpMEM = tmpEX;
            }else if(mode == 4){
                if(WBBuffer.rd == 0){
                    writeMemZero = 1;
                }else{
                    printPlace = WBBuffer.rd;
                    printValue = reg[printPlace];
                    reg[WBBuffer.rd] = tmpMEM;
                }
            }
            break;
        case addu:
            strcpy(out, "ADDU");
            if(mode == 2){
                tmpEX = EXBuffer.a + EXBuffer.b;
            }else if(mode == 3){
                tmpMEM = tmpEX;
            }else if(mode == 4){
                if(WBBuffer.rd == 0){
                    writeMemZero = 1;
                }else{
                    printPlace = WBBuffer.rd;
                    printValue = reg[printPlace];
                    reg[WBBuffer.rd] = tmpMEM;
                }
            }
            break;
        case And:
            strcpy(out, "AND");
            if(mode == 2){
                tmpEX = EXBuffer.a & EXBuffer.b;
            }else if(mode == 3){
                tmpMEM = tmpEX;
            }else if(mode == 4){
                if(WBBuffer.rd == 0){
                    writeMemZero = 1;
                }else{
                    printPlace = WBBuffer.rd;
                    printValue = reg[printPlace];
                    reg[WBBuffer.rd] = tmpMEM;
                }
            }
            break;
        case Or:
            strcpy(out, "OR");
            if(mode == 2){
                tmpEX = EXBuffer.a | EXBuffer.b;
            }else if(mode == 3){
                tmpMEM = tmpEX;
            }else if(mode == 4){
                if(WBBuffer.rd == 0){
                    writeMemZero = 1;
                }else{
                    printPlace = WBBuffer.rd;
                    printValue = reg[printPlace];
                    reg[WBBuffer.rd] = tmpMEM;
                }
            }
            break;
        case Xor:
            strcpy(out, "XOR");
            if(mode == 2){
                tmpEX = EXBuffer.a ^ EXBuffer.b;
            }else if(mode == 3){
                tmpMEM = tmpEX;
            }else if(mode == 4){
                if(WBBuffer.rd == 0){
                    writeMemZero = 1;
                }else{
                    printPlace = WBBuffer.rd;
                    printValue = reg[printPlace];
                    reg[WBBuffer.rd] = tmpMEM;
                }
            }
            break;
        case nor:
            strcpy(out, "NOR");
            if(mode == 2){
                tmpEX = ~(EXBuffer.a | EXBuffer.b);
            }else if(mode == 3){
                tmpMEM = tmpEX;
            }else if(mode == 4){
                if(WBBuffer.rd == 0){
                    writeMemZero = 1;
                }else{
                    printPlace = WBBuffer.rd;
                    printValue = reg[printPlace];
                    reg[WBBuffer.rd] = tmpMEM;
                }
            }
            break;
        case nand:
            strcpy(out, "NAND");
            if(mode == 2){
                tmpEX = ~(EXBuffer.a & EXBuffer.b);
            }else if(mode == 3){
                tmpMEM = tmpEX;
            }else if(mode == 4){
                if(WBBuffer.rd == 0){
                    writeMemZero = 1;
                }else{
                    printPlace = WBBuffer.rd;
                    printValue = reg[printPlace];
                    reg[WBBuffer.rd] = tmpMEM;
                }
            }
            break;
        case slt:
            strcpy(out, "SLT");
            if(mode == 2){
                RS = EXBuffer.a; RT = EXBuffer.b;
                tmpEX = RS < RT;
            }else if(mode == 3){
                tmpMEM = tmpEX;
            }else if(mode == 4){
                if(WBBuffer.rd == 0){
                    writeMemZero = 1;
                }else{
                    printPlace = WBBuffer.rd;
                    printValue = reg[printPlace];
                    reg[WBBuffer.rd] = tmpMEM;
                }
            }
            break;
        case sll:
            strcpy(out,"SLL");
            if(mode == 2){
                tmpEX = EXBuffer.b << EXBuffer.shamt;
                //printf("SLL: 0x%08X, 0x%08X, 0x%08X\n", tmpEX, EXBuffer.b, EXBuffer.shamt);
            }else if(mode == 3){
                tmpMEM = tmpEX;
            }else if(mode == 4){

                if(WBBuffer.rd == 0){
                    if((WBBuffer.shamt || WBBuffer.rt)){
                        writeMemZero = 1;
                    }else{
                        printPlace = WBBuffer.rd;
                        printValue = reg[printPlace];
                        reg[WBBuffer.rd] = tmpMEM;
                    }
                }else{
                    printPlace = WBBuffer.rd;
                    printValue = reg[printPlace];
                    reg[WBBuffer.rd] = tmpMEM;
                }

            }
            break;
        case srl:
            strcpy(out, "SRL");
            if(mode == 2){
                tmpEX = EXBuffer.b >> EXBuffer.shamt;
            }else if(mode == 3){
                tmpMEM = tmpEX;
            }else if(mode == 4){
                if(WBBuffer.rd == 0){
                    writeMemZero = 1;
                }else{
                    printPlace = WBBuffer.rd;
                    printValue = reg[printPlace];
                    reg[WBBuffer.rd] = tmpMEM;
                }
            }
            break;
        case sra:
            strcpy(out, "SRA");
            if(mode == 2){
                RT = EXBuffer.b;
                tmpEX = RT >> EXBuffer.shamt;
            }else if(mode == 3){
                tmpMEM = tmpEX;
            }else if(mode == 4){
                if(WBBuffer.rd == 0){
                    writeMemZero = 1;
                }else{
                    printPlace = WBBuffer.rd;
                    printValue = reg[printPlace];
                    reg[WBBuffer.rd] = tmpMEM;
                }
            }
            break;
        case jr:
            strcpy(out, "JR");
            if(mode == 1 && !IDBuffer.stall){
                newPC = IDBuffer.a - 4;
                flush = 1;
            }
            break;
        default:
            strcpy(out, "NOP");
    }
}

void Ins(unsigned int ins, char* out, int mode){
    if(mode == 2){
        getImmediateBoth(ins);
    }
    switch(ins>>26){
        case halt:
            strcpy(out, "HALT");
            break;
        case j:
            strcpy(out, "J");
            if(mode == 1){
                getAddr();
                newPC = (((IDBuffer.pc + 4) >> 28 << 28) | (addr << 2)) - 4;
                flush = 1;
            }
            break;
        case jal:
            strcpy(out, "JAL");
            if(mode == 1){
                getAddr();
                newPC = (((IDBuffer.pc + 4) >> 28 << 28) | (addr << 2)) - 4;
                flush = 1;
            }else if(mode == 3){
                tmpMEM = MEMBuffer.pc + 4;
            }else if(mode == 4){
                printValue = reg[31];
                reg[31] = tmpMEM;
                printPlace = 31;
            }
            break;
        case addi:
            strcpy(out, "ADDI");
            if(mode == 2){
                RS = EXBuffer.a; signRS = EXBuffer.a >> 31; signCons = (unsigned)constant2 >> 31;
                tmpEX = RS + constant2;
                signRT = tmpEX >> 31;

                if(signRS == signCons && signRS != signRT)
                    numberOverflow = 1;
            }else if(mode == 3){
                tmpMEM = tmpEX;
            }else if(mode == 4){
                if(WBBuffer.rt == 0){
                    writeMemZero = 1;
                }else{
                    printPlace = WBBuffer.rt;
                    printValue = reg[printPlace];
                    reg[WBBuffer.rt] = tmpMEM;
                }
            }
            break;
        case addiu:
            strcpy(out, "ADDIU");
            if(mode == 2){
                tmpEX = EXBuffer.a + constant2;
            }else if(mode == 3){
                tmpMEM = tmpEX;
            }else if(mode == 4){
                if(WBBuffer.rt == 0){
                    writeMemZero = 1;
                }else{
                    printPlace = WBBuffer.rt;
                    printValue = reg[printPlace];
                    reg[WBBuffer.rt] = tmpMEM;
                }
            }
            break;
        case lw:
            strcpy(out, "LW");
            if(mode == 2){
                signRS = EXBuffer.a >> 31; signCons = (unsigned)constant2 >> 31;
                tmpEX = EXBuffer.a + constant2;
                signRD = tmpEX >> 31;


                if(signRS == signCons && signRS != signRD)
                    numberOverflow = 1;
            }else if(mode == 3){
                int i;
                tmpMEM = 0;
                if(!checkMem(4)) return;


                for(i = 0; i < 4; i++){
                    tmpMEM = (tmpMEM << 8) + dM[tmpEX+i];
                       // printf("%02X", dM[tmpEX + i]);
                }

            }else if(mode == 4){
                if(WBBuffer.rt == 0){
                    writeMemZero = 1;
                }else{
                    printPlace = WBBuffer.rt;
                    printValue = reg[printPlace];
                    reg[WBBuffer.rt] = tmpMEM;
                }
            }
            break;
        case lh:
            strcpy(out, "LH");
            if(mode == 2){
                signRS = EXBuffer.a >> 31; signCons = (unsigned)constant2 >> 31;
                tmpEX = EXBuffer.a + constant2;
                signRD = tmpEX >> 31;
                if(signRS == signCons && signRS != signRD)
                    numberOverflow = 1;
            }else if(mode == 3){
                if(!checkMem(2)) return;
                tmpMEM = (char)dM[tmpEX] << 8;
                tmpMEM += dM[tmpEX+1];
            }else if(mode == 4){
                if(WBBuffer.rt == 0){
                    writeMemZero = 1;
                }else{
                    printPlace = WBBuffer.rt;
                    printValue = reg[printPlace];
                    reg[WBBuffer.rt] = tmpMEM;
                }
            }
            break;
        case lhu:
            strcpy(out, "LHU");
            if(mode == 2){
                signRS = EXBuffer.a >> 31; signCons = (unsigned)constant2 >> 31;
                tmpEX = EXBuffer.a + constant2;
                signRD = tmpEX >> 31;
                if(signRS == signCons && signRS != signRD)
                    numberOverflow = 1;
            }else if(mode == 3){
                int i;
                tmpMEM = 0;
                if(!checkMem(2)) return;

                for(i = 0; i < 2; i++){
                    tmpMEM = (tmpMEM << 8) + dM[tmpEX+i];
                }
            }else if(mode == 4){
                if(WBBuffer.rt == 0){
                    writeMemZero = 1;
                }else{
                    printPlace = WBBuffer.rt;
                    printValue = reg[printPlace];
                    reg[WBBuffer.rt] = tmpMEM;
                }
            }
            break;
        case lb:
            strcpy(out, "LB");
            if(mode == 2){
                signRS = EXBuffer.a >> 31; signCons = (unsigned)constant2 >> 31;
                tmpEX = EXBuffer.a + constant2;
                signRD = tmpEX >> 31;
                if(signRS == signCons && signRS != signRD)
                    numberOverflow = 1;
            }else if(mode == 3){
                if(!checkMem(1)) return;
                tmpMEM = (char)dM[tmpEX];
            }else if(mode == 4){
                if(WBBuffer.rt == 0){
                    writeMemZero = 1;
                }else{
                    printPlace = WBBuffer.rt;
                    printValue = reg[printPlace];
                    reg[WBBuffer.rt] = tmpMEM;
                }
            }
            break;
        case lbu:
            strcpy(out, "LBU");
            if(mode == 2){
                signRS = EXBuffer.a >> 31; signCons = (unsigned)constant2 >> 31;
                tmpEX = EXBuffer.a + constant2;
                signRD = tmpEX >> 31;
                if(signRS == signCons && signRS != signRD)
                    numberOverflow = 1;
            }else if(mode == 3){
                if(!checkMem(1)) return;
                tmpMEM = dM[tmpEX];
            }else if(mode == 4){
                if(WBBuffer.rt == 0){
                    writeMemZero = 1;
                }else{
                    printPlace = WBBuffer.rt;
                    printValue = reg[printPlace];
                    reg[WBBuffer.rt] = tmpMEM;
                }
            }
            break;
        case sw:
            strcpy(out, "SW");
            if(mode == 2){
                signRS = EXBuffer.a >> 31; signCons = (unsigned)constant2 >> 31;
                tmpEX = EXBuffer.a + constant2;
                signRD = tmpEX >> 31;
                if(signRS == signCons && signRS != signRD)
                    numberOverflow = 1;
            }else if(mode == 3){
                if(!checkMem(4)) return;
                dM[tmpEX] = reg[MEMBuffer.rt] >> 24;
                dM[tmpEX + 1] = reg[MEMBuffer.rt] << 8 >> 24;
                dM[tmpEX + 2] = reg[MEMBuffer.rt] << 16 >> 24;
                dM[tmpEX + 3] = reg[MEMBuffer.rt] << 24 >> 24;
            }

            break;
        case sh:
            strcpy(out, "SH");
            if(mode == 2){
                signRS = EXBuffer.a >> 31; signCons = (unsigned)constant2 >> 31;
                tmpEX = EXBuffer.a + constant2;
                signRD = tmpEX >> 31;
                if(signRS == signCons && signRS != signRD)
                    numberOverflow = 1;
            }else if(mode == 3){
                if(!checkMem(2)) return;
                dM[tmpEX] = reg[MEMBuffer.rt] << 16 >> 24;
                dM[tmpEX + 1] = reg[MEMBuffer.rt] << 24 >> 24;
            }
            break;
        case sb:
            strcpy(out, "SB");
            if(mode == 2){
                signRS = EXBuffer.a >> 31; signCons = (unsigned)constant2 >> 31;
                tmpEX = EXBuffer.a + constant2;
                signRD = tmpEX >> 31;

                if(signRS == signCons && signRS != signRD)
                    numberOverflow = 1;
            }else if(mode == 3){
                if(!checkMem(1)) return;
                dM[tmpEX] = reg[MEMBuffer.rt] << 24 >> 24;
            }
            break;
        case lui:
            strcpy(out, "LUI");
            if(mode == 2){
                tmpEX = constant2 << 16;
            }else if(mode == 3){
                tmpMEM = tmpEX;
            }else if(mode == 4){
                if(WBBuffer.rt == 0){
                    writeMemZero = 1;
                }else{
                    printPlace = WBBuffer.rt;
                    printValue = reg[printPlace];
                    reg[WBBuffer.rt] = tmpMEM;
                    //printf("cycel %d: %d %08X %08X\n", cycle, printPlace, printValue, tmpMEM);
                }
            }
            break;
        case andi:
            strcpy(out, "ANDI");
            if(mode == 2){
                tmpEX = EXBuffer.a & constant;
            }else if(mode == 3){
                tmpMEM = tmpEX;
            }else if(mode == 4){
                if(WBBuffer.rt == 0){
                    writeMemZero = 1;
                }else{
                    printPlace = WBBuffer.rt;
                    printValue = reg[printPlace];
                    reg[WBBuffer.rt] = tmpMEM;
                }
            }
            break;
        case ori:
            strcpy(out, "ORI");
            if(mode == 2){
                tmpEX = EXBuffer.a | constant;
            }else if(mode == 3){
                tmpMEM = tmpEX;
            }else if(mode == 4){
                if(WBBuffer.rt == 0){
                    writeMemZero = 1;
                }else{
                    printPlace = WBBuffer.rt;
                    printValue = reg[printPlace];
                    reg[WBBuffer.rt] = tmpMEM;
                }
            }
            break;
        case nori:
            strcpy(out, "NORI");
            if(mode == 2){
                tmpEX = ~(EXBuffer.a | constant);
            }else if(mode == 3){
                tmpMEM = tmpEX;
            }else if(mode == 4){
                if(WBBuffer.rt == 0){
                    writeMemZero = 1;
                }else{
                    printPlace = WBBuffer.rt;
                    printValue = reg[printPlace];
                    reg[WBBuffer.rt] = tmpMEM;
                }
            }
            break;
        case slti:
            strcpy(out, "SLTI");
            if(mode == 2){
                RS = EXBuffer.a;
                tmpEX = RS < constant2;
            }else if(mode == 3){
                tmpMEM = tmpEX;
            }else if(mode == 4){
                if(WBBuffer.rt == 0){
                    writeMemZero = 1;
                }else{
                    printPlace = WBBuffer.rt;
                    printValue = reg[printPlace];
                    reg[WBBuffer.rt] = tmpMEM;
                }
            }
            break;
        case beq:
            strcpy(out, "BEQ");
            if(mode == 1 && !IDBuffer.stall){
                getImmediateBoth(ins);
                if(IDBuffer.a == IDBuffer.b){
                    newPC = IDBuffer.pc + (constant2 << 2);
                    flush = 1;
                }
            }
            break;
        case bne:
            strcpy(out, "BNE");
            if(mode == 1  && !IDBuffer.stall){
                getImmediateBoth(ins);
                if(IDBuffer.a != IDBuffer.b){
                    newPC = IDBuffer.pc + (constant2 << 2);
                    flush = 1;
                }
            }
            break;
        case bgtz:
            strcpy(out, "BGTZ");
            if(mode == 1 && !IDBuffer.stall){
                getImmediateBoth(ins);
                if((int)(IDBuffer.a) > 0){
                    //printf("%d\n", PC);
                    newPC = IDBuffer.pc + (constant2 << 2);
                    flush = 1;
                    //printf("%d\n", PC);
                }
            }
            break;
        case Rtype:
            Func(ins,out,mode);
            break;
        default:
            strcpy(out, "NOP");
    }
}

void IF(){
    IFBuffer.stall = IDBuffer.stall;


    part1 = iM[PC]; part1 = part1 << 24;
    part2 = iM[PC+1]; part2 = part2 << 16;
    part3 = iM[PC+2]; part3 = part3 << 8;
    part4 = iM[PC+3];

    IFBuffer.instruction = part1 + part2 + part3 + part4;
    IFBuffer.opcode = IFBuffer.instruction >> 26;
    IFBuffer.pc = PC;

    printSnapShot();
    if(!IFBuffer.stall)
        PC = PC + 4;

}

void ID(){
    if(flush){
        bufferClear(&IDBuffer);
        flush = 0;
    }else if(!IDBuffer.stall){
        bufferCopy(&IDBuffer, &IFBuffer);
        Decode();
        //printf("(%d %d %d)\n", IDBuffer.rs, IDBuffer.rt, IDBuffer.rd);
    }

    IDBuffer.a = reg[IDBuffer.rs];
    IDBuffer.b = reg[IDBuffer.rt];

    char rsN = 0, rtN = 0;
    find_nearest_value(&rsN, &rtN, IDBuffer.opcode);
    IDBuffer.stall = 0;
    if(between(IDBuffer.opcode, 2, 7) || (IDBuffer.opcode == Rtype && (IDBuffer.instruction << 26 >> 26) == jr)){
        /*if(cycle == 324 || cycle == 351){
            printf("(%d,%d) (%d,%d) (%d,%d) (%d,%d) (%d,%d)\n", rsN, rtN , IDBuffer.rs, IDBuffer.rt, EXBuffer.rd, EXBuffer.rt,MEMBuffer.rd, MEMBuffer.rt, WBBuffer.rd, WBBuffer.rt);
        }*/

        int S = 0;
        switch(rsN){
            case 1:
                if(!between(EXBuffer.opcode, 40, 43))
                    IDBuffer.stall = 1;
                S = IDBuffer.stall;
                break;
            case 2:
                IDBuffer.stall = 1;
                if(MEMBuffer.opcode == Rtype){

                    if(IDBuffer.rs == MEMBuffer.rd ){
                        Forwarding.forwardingRs_ID = IDBuffer.rs;
                        IDBuffer.a = tmpMEM;
                        IDBuffer.stall = 0;
                    }
                }else{
                    if(between(MEMBuffer.opcode, 8, 43) && IDBuffer.rs == MEMBuffer.rt){
                        if(!between(MEMBuffer.opcode, 32, 37)){
                            Forwarding.forwardingRs_ID = IDBuffer.rs;
                            IDBuffer.a = tmpMEM;
                            IDBuffer.stall = 0;
                        }
                    }
                    if(MEMBuffer.opcode == jal && IDBuffer.rs == 31){
                        Forwarding.forwardingRs_ID = IDBuffer.rs;
                        IDBuffer.a = tmpMEM;
                        IDBuffer.stall = 0;
                    }
                }
                S = IDBuffer.stall;
                break;
            default:
                Forwarding.forwardingRs_ID = 0;
                break;
        }

        switch(rtN){
            case 1:
                if(!between(EXBuffer.opcode, 40, 43))
                    IDBuffer.stall = 1;
                break;
            case 2:
                IDBuffer.stall = 1;

                if(!S){
                    if(MEMBuffer.opcode == Rtype){
                        if(IDBuffer.rt == MEMBuffer.rd){
                            Forwarding.forwardingRt_ID = IDBuffer.rt;
                            IDBuffer.b = tmpMEM;
                            IDBuffer.stall = 0;
                        }
                    }else{
                        if(between(MEMBuffer.opcode, 8, 43) && IDBuffer.rt == MEMBuffer.rt){
                            if(!between(MEMBuffer.opcode, 32, 37)){
                                Forwarding.forwardingRt_ID = IDBuffer.rt;
                                IDBuffer.b = tmpMEM;
                                IDBuffer.stall = 0;
                            }
                            //printf("cycle %d: %d %d\n", cycle, IDBuffer.a, IDBuffer.b);
                            //system("pause");
                        }
                        if(MEMBuffer.opcode == jal && IDBuffer.rt == 31){
                            Forwarding.forwardingRt_ID = IDBuffer.rt;
                            IDBuffer.b = tmpMEM;
                            IDBuffer.stall = 0;
                        }
                    }
                }
                //printf("**%d %d %d\n", cycle, IDBuffer.rt, MEMBuffer.rt);
                break;
            default:
                //puts("No");
                Forwarding.forwardingRt_ID = 0;
                break;
        }


    }else if(IDBuffer.opcode == Rtype){
        switch(rsN){
        case 1:
            if(between(EXBuffer.opcode, 32, 37))
                IDBuffer.stall = 1;
            //printf("IDR_1rs %d\n", IDBuffer.rs);
            break;
        case 2:

            if(!between(MEMBuffer.opcode, 40, 43) && !(MEMBuffer.opcode == Rtype && (MEMBuffer.instruction << 26 >> 26 == jr)))
                IDBuffer.stall = 1;
            break;
        default:
           // puts("IDR_RSN");
           break;
        }

        switch(rtN){
        case 1:
            if(between(EXBuffer.opcode, 32, 37))
                IDBuffer.stall = 1;
            //printf("IDR_1rt %d\n", IDBuffer.rt);
            break;
        case 2:

            if(!between(MEMBuffer.opcode, 40, 43)&& !(MEMBuffer.opcode == Rtype && (MEMBuffer.instruction << 26 >> 26 == jr)))
                IDBuffer.stall = 1;
            break;
        default:
            //puts("IDR_RTN");
            break;
        }
    }else if(between(IDBuffer.opcode, 8, 59)){

        switch(rsN){
        case 1:

            if(between(EXBuffer.opcode, 32, 37) && EXBuffer.rt == IDBuffer.rs){
                IDBuffer.stall = 1;
            }
            break;
        case 2:
            if(!between(MEMBuffer.opcode, 40, 43))
                IDBuffer.stall = 1;
            break;
        default:

           // puts("ID_RSN");
           break;
        }

        switch(rtN){
        case 1:
            if(between(EXBuffer.opcode, 32, 37) && EXBuffer.rt == IDBuffer.rt)
                IDBuffer.stall = 1;
            else if(between(EXBuffer.opcode, 40, 43) && (EXBuffer.rt == IDBuffer.rt)){
                IDBuffer.stall = 1;
            }
            break;
        case 2:
            if(!between(MEMBuffer.opcode, 40, 43))
                IDBuffer.stall = 1;
            break;
        default:
           // puts("ID_RSN");
           break;
        }

    }

    if(IDBuffer.opcode == Rtype && (IDBuffer.instruction << 11) == 0)
        bufferClear(&IDBuffer);

    Ins(IDBuffer.instruction, IDBuffer.out, 1);

    //printf("ID,cycle%d:%s %d\n", cycle, IDBuffer.out, IDBuffer.stall);

}

void EX(){
    if(IDBuffer.stall){
        bufferClear(&EXBuffer);
    }else{
        bufferCopy(&EXBuffer, &IDBuffer);
    }
    unsigned tmp = EXBuffer.instruction << 26 >> 26;
    if(EXBuffer.opcode == Rtype && (EXBuffer.instruction << 26 >> 26 != jr)){
        if(MEMBuffer.opcode == Rtype){

            if(EXBuffer.rs > 0 && EXBuffer.rs == MEMBuffer.rd && !((tmp == sll || tmp == srl || tmp == sra))){
                Forwarding.forwardingRs_EX = EXBuffer.rs;
                EXBuffer.a = tmpMEM;
            }
            if(EXBuffer.rt > 0 && EXBuffer.rt == MEMBuffer.rd){
                Forwarding.forwardingRt_EX = EXBuffer.rt;
                EXBuffer.b = tmpMEM;
            }
        }else if(!between(MEMBuffer.opcode, 40, 43) && MEMBuffer.opcode >= 8){
            if(EXBuffer.rs > 0 && EXBuffer.rs == MEMBuffer.rt && !((tmp == sll || tmp == srl || tmp == sra))){
                Forwarding.forwardingRs_EX = EXBuffer.rs;
                EXBuffer.a = tmpMEM;
            }
            if(EXBuffer.rt > 0 && EXBuffer.rt == MEMBuffer.rt){
                Forwarding.forwardingRt_EX = EXBuffer.rt;
                EXBuffer.b = tmpMEM;
            }
        }
    }else{
        if(EXBuffer.opcode != halt)
           if(MEMBuffer.opcode == Rtype){
                if(EXBuffer.rs > 0 && EXBuffer.rs == MEMBuffer.rd && EXBuffer.opcode != lui){
                    Forwarding.forwardingRs_EX = EXBuffer.rs;
                    EXBuffer.a = tmpMEM;
                }
                if(between(EXBuffer.opcode, 40, 43) && EXBuffer.rt > 0 && EXBuffer.rt == MEMBuffer.rd){
                    Forwarding.forwardingRt_EX = EXBuffer.rt;
                }
            }else if(!between(MEMBuffer.opcode, 40,43) && MEMBuffer.opcode >= 8){
                if(EXBuffer.rs > 0 && EXBuffer.opcode != lui && EXBuffer.rs == MEMBuffer.rt){
                    Forwarding.forwardingRs_EX = EXBuffer.rs;
                    EXBuffer.a = tmpMEM;
                }
                if(between(EXBuffer.opcode, 40, 43) && EXBuffer.rt > 0 && EXBuffer.rt == MEMBuffer.rt){
                    Forwarding.forwardingRt_EX = EXBuffer.rt;
                }
            }

    }
    Ins(EXBuffer.instruction, EXBuffer.out, 2);

    //printf("EX,cycle%d: %08X %s\n", cycle,EXBuffer.instruction, EXBuffer.out);
}

void MEM(){
    bufferCopy(&MEMBuffer, &EXBuffer);
    //strcpy(outMEM, outEX);
    Ins(MEMBuffer.instruction, MEMBuffer.out, 3);

}

void WB(){
    bufferCopy(&WBBuffer, &MEMBuffer);
    //strcpy(outWB, outMEM);
    Ins(WBBuffer.instruction, WBBuffer.out, 4);

}

void simulate(){
    bufferClear(&WBBuffer);
    bufferClear(&MEMBuffer);
    bufferClear(&EXBuffer);
    bufferClear(&IDBuffer);
    bufferClear(&IFBuffer);
    initForwarding();
    while(1){

        if(!strcmp(WBBuffer.out, "HALT")) break;

        if(misalignment || memOverflow){
            printError();
            break;
        }
        printError();

        WB();
        MEM();
        EX();
        ID();
        IF();
    }
}


int main(){
    openFile();
    dMemory();
    iMemory();
    simulate();
    fclose(err);
    fclose(snap);
    return 0;
}

