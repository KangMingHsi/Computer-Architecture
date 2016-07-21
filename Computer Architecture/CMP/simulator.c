#include "define.h"
#include "IO.h"
#include "Var.h"
#include "ToFile.h"
#include "Memory.h"
#include "translate.h"
#include "CMP.h"

void Execute(){
    while(1){
        unsigned char opcode = iDisk[PC];
        opcode = (opcode >> 2);
        checkCMP(1);
        flag = 0;
        printSnapShot();

        if(opcode == halt){
            return;
        }else if(opcode == jal){
            getAddr();
            reg[31] = PC + 4;
            PC = ((PC + 4) >> 28 << 28) | (addr << 2);

        }else if(opcode == j){
            getAddr();
            PC = ((PC + 4) >> 28 << 28) | (addr << 2);

        }else{
            if(opcode == Rtype){
                getRsRtRd(0);
                getShamtAndFunc();

                switch(func)
                {
                case add:
                    signRS = reg[rs] >> 31;
                    signRT = reg[rt] >> 31;
                    reg[rd] = reg[rs] + reg[rt];
                    signRD = reg[rd] >> 31;
                    if(rd == 0){
                        writeMemZero = 1;
                        reg[rd] = 0;
                    }

                    if(signRS == signRT && signRS != signRD){
                        numberOverflow = 1;
                    }
                    break;
                case addu:
                    reg[rd] = reg[rs] + reg[rt];
                    if(rd == 0){
                        writeMemZero = 1;
                        reg[rd] = 0;
                    }
                    break;
                case sub:
                    signRS = reg[rs] >> 31;
                    signRT = (-reg[rt]) >> 31;
                    reg[rd] = reg[rs] - reg[rt];
                    signRD = reg[rd] >> 31;
                    if(rd == 0){
                        writeMemZero = 1;
                        reg[rd] = 0;
                    }
                    if(signRS == signRT && signRS != signRD){
                        numberOverflow = 1;
                    }

                    break;
                case And:
                    reg[rd] = reg[rs] & reg[rt];
                    if(rd == 0){
                        writeMemZero = 1;
                        reg[rd] = 0;
                    }
                    break;
                case Or:
                    reg[rd] = reg[rs] | reg[rt];
                    if(rd == 0){
                        writeMemZero = 1;
                        reg[rd] = 0;
                    }
                    break;
                case Xor:
                    reg[rd] = reg[rs] ^ reg[rt];
                    if(rd == 0){
                        writeMemZero = 1;
                        reg[rd] = 0;
                    }
                    break;
                case nor:
                    reg[rd] = ~(reg[rs] | reg[rt]);
                    if(rd == 0){
                        writeMemZero = 1;
                        reg[rd] = 0;
                    }
                    break;
                case nand:
                    reg[rd] = ~(reg[rs] & reg[rt]);
                    if(rd == 0){
                        writeMemZero = 1;
                        reg[rd] = 0;
                    }
                    break;
                case slt:
                    RS = reg[rs], RT = reg[rt];
                    reg[rd] = RS < RT;
                    if(rd == 0){
                        writeMemZero = 1;
                        reg[rd] = 0;
                    }
                    break;
                case sll:
                    reg[rd] = reg[rt] << shamt;
                    if(rd == 0){
                        if((shamt || rt)){
                            writeMemZero = 1;
                            reg[rd] = 0;
                        }
                    }
                    break;
                case srl:
                    reg[rd] = reg[rt] >> shamt;
                    if(rd == 0){
                        writeMemZero = 1;
                        reg[rd] = 0;
                    }
                    break;
                case sra:
                    RT = reg[rt];
                    reg[rd] = RT >> shamt;
                    if(rd == 0){
                        writeMemZero = 1;
                        reg[rd] = 0;
                    }
                    break;
                case jr:
                    PC = reg[rs];
                    flag = 1;
                    break;
                default:
                    //Pos = ;
                    break;
                }
            }else{
                getRsRtRd(1);
                getImmediateBoth();
                RS = reg[rs];

                switch(opcode){
                case addi:
                    signRS = reg[rs] >> 31; signCons = constant >> 15;
                    reg[rt] = RS + constant2;
                    signRT = reg[rt] >> 31;
                    if(rt == 0){
                        writeMemZero = 1;
                        reg[rt] = 0;
                    }
                    if(signRS == signCons && signRS != signRT)
                        numberOverflow = 1;
                    break;
                case addiu:

                    reg[rt] = reg[rs] + constant2;

                    if(rt == 0){
                        writeMemZero = 1;
                        reg[rt] = 0;
                    }
                    break;
                case lw:
                    getPos();
                    if(rt == 0)
                        writeMemZero = 1;

                    checkCMP(2);

                    if(!checkMem(4)) return;
                    part1 = dDisk[Pos], part1 = part1 << 24;
                    part2 = dDisk[Pos + 1], part2 = part2 << 16;
                    part3 = dDisk[Pos + 2], part3 = part3 << 8;
                    part4 = dDisk[Pos + 3];
                    reg[rt] = part1 + part2 + part3 + part4 ;

                    if(rt == 0)
                        reg[rt] = 0;

                    break;
                case lh:
                    getPos();
                    if(rt == 0){
                        writeMemZero = 1;
                    }
                    checkCMP(2);
                    if(!checkMem(2)) return;
                    part1 = dDisk[Pos], part1 = part1 << 8;
                    part2 = dDisk[Pos + 1];
                    short x = part1 + part2;
                    reg[rt] = x;
                    if(rt == 0){
                        reg[rt] = 0;
                    }
                    break;
                case lhu:
                    getPos();
                    if(rt == 0){
                        writeMemZero = 1;
                    }
                    checkCMP(2);
                    if(!checkMem(2)) return;
                    part1 = dDisk[Pos], part1 = part1 << 8;
                    part2 = dDisk[Pos + 1];
                    reg[rt] = (part1 + part2);
                    if(rt == 0){
                        reg[rt] = 0;
                    }
                    break;
                case lb:
                    getPos();
                    if(rt == 0){
                        writeMemZero = 1;
                    }
                    checkCMP(2);
                    if(!checkMem(1)) return;
                    part1 = (char)dDisk[Pos];
                    reg[rt] = part1;
                    if(rt == 0){
                        reg[rt] = 0;
                    }
                    break;
                case lbu:
                    getPos();
                    if(rt == 0){
                        writeMemZero = 1;
                    }
                    checkCMP(2);
                    if(!checkMem(1)) return;
                    reg[rt] = dDisk[Pos];
                    if(rt == 0){
                        reg[rt] = 0;
                    }
                    break;
                case sw:
                    getPos();
                    checkCMP(2);
                    if(!checkMem(4)) return;

                    dDisk[Pos] = reg[rt] >> 24;
                    dDisk[Pos + 1] = reg[rt] << 8 >> 24;
                    dDisk[Pos + 2] = reg[rt] << 16 >> 24;
                    dDisk[Pos + 3] = reg[rt] << 24 >> 24;
                    break;
                case sh:
                    getPos();
                    checkCMP(2);
                    if(!checkMem(2)) return;

                    dDisk[Pos] = reg[rt] >> 8;
                    dDisk[Pos + 1] = reg[rt];
                    break;
                case sb:
                    getPos();
                    checkCMP(2);
                    if(!checkMem(1)) return;

                    dDisk[Pos] = reg[rt];
                    break;
                case lui:
                    reg[rt] = constant << 16;

                    if(rt == 0){
                        writeMemZero = 1;
                        reg[rt] = 0;
                    }
                    break;
                case andi:
                    reg[rt] = reg[rs] & constant;
                    if(rt == 0){
                        writeMemZero = 1;
                        reg[rt] = 0;
                    }
                    break;
                case ori:
                    reg[rt] = reg[rs] | constant;
                    if(rt == 0){
                        writeMemZero = 1;
                        reg[rt] = 0;
                    }
                    break;
                case nori:
                    reg[rt] = ~(reg[rs] | constant);
                    if(rt == 0){
                        writeMemZero = 1;
                        reg[rt] = 0;
                    }
                    break;
                case slti:
                    reg[rt] = (RS < constant2);
                    if(rt == 0){
                        writeMemZero = 1;
                        reg[rt] = 0;
                    }
                    break;
                case beq:
                    RT = reg[rt];
                    if(RS == RT){
                        PC = PC + 4 + (constant2 << 2);
                        flag = 1;
                    }
                    break;
                case bne:
                    RT = reg[rt];
                    if(RS != RT){
                        PC = PC + 4 + (constant2 << 2);
                        flag = 1;
                    }
                    break;
                case bgtz:
                    if(RS > 0){
                        PC = PC + 4 + (constant2 << 2);
                        flag = 1;
                    }
                    break;
                default:
                    break;
                }

            }
            if(!flag)
                PC += 4;
            //printError();
        }
    }
}

int main(int argc, char* argv[]){
    openFile();
    inDDisk();
    inIDisk();
    if(argc > 10){
        init.iMemSize = atoi(argv[1]);
        init.dMemSize = atoi(argv[2]);
        init.iMemPageSize = atoi(argv[3]);
        init.dMemPageSize = atoi(argv[4]);
        init.iCacheTotalSize = atoi(argv[5]);
        init.iCacheBlockSize = atoi(argv[6]);
        init.iCacheSet = atoi(argv[7]);
        init.dCacheTotalSize = atoi(argv[8]);
        init.dCacheBlockSize = atoi(argv[9]);
        init.dCacheSet = atoi(argv[10]);
    }else{
        init.iMemSize = 64;
        init.iMemPageSize = 8;
        init.iCacheTotalSize = 16;
        init.iCacheSet = 4;
        init.iCacheBlockSize = 4;
        init.dMemSize = 32;
        init.dMemPageSize = 16;
        init.dCacheTotalSize = 16;
        init.dCacheSet = 1;
        init.dCacheBlockSize = 4;
    }

    initCMP();

    Execute();
    //printf("SSSS");
    //printError();
    printReport();
    fclose(report);
    fclose(snap);
    return 0;
}

