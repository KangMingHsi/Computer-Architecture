#include "Var.h"
#include "translate.h"

void getAddr(){
    part1 = iM[PC], part2 = iM[PC+1], part3 = iM[PC+2], part4 = iM[PC+3];
    part1 = (part1 << 30) >> 6;
    part2 = (part2 << 16);
    part3 = (part3 << 8);

    addr = (part1 + part2 + part3 + part4);
}
void getRsRtRd(int mode){
    part1 = iM[PC], part1 = part1 << 30 >> 27;
    part2 = iM[PC+1], part2 = part2 >> 5;
    part3 = iM[PC+1], part3 = part3 << 27 >> 27;
    rs = part1 + part2;
    rt = part3;
    if(mode == 0){
        rd = iM[PC+2] >> 3;
    }
}
void getShamtAndFunc(){
    part1 = iM[PC+2], part1 = part1 << 29 >> 27;
    part2 = iM[PC+3], part2 = part2 >> 6;
    part3 = iM[PC+3], part3 = part3 << 26 >> 26;

    shamt = part1 + part2;
    func = part3;
}
void getImmediateBoth(){
    part1 = iM[PC+2], part1 = part1 << 8;
    part2 = iM[PC+3];
    constant = part1 + part2;
    constant2 = part1 + part2;
    constant2 = constant2 << 16 >> 16;
}
void getPos(){
    signRS = RS >> 31; signCons = constant2 >> 31;
    Pos = RS + constant2;
    signRD = Pos >> 31;
    if(signRS == signCons && signRS != signRD)
        numberOverflow = 1;
}
