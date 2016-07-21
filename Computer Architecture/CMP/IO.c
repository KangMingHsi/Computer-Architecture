#include "define.h"
#include "Var.h"
#include "IO.h"
void openFile(){
    unsigned int iImLen, iImRLen, dImLen, dImRLen;

    iIm = fopen("iimage.bin", "rb");
    dIm = fopen("dimage.bin", "rb");
    snap = fopen("snapshot.rpt", "wb");
    report = fopen("report.rpt", "wb");

    if(iIm == NULL || dIm == NULL){
        printf("E1\n");
        return;
    }

    fseek(iIm,0,SEEK_END);
    fseek(dIm,0,SEEK_END);
    iImLen = ftell(iIm);
    dImLen = ftell(dIm);
    rewind(iIm);
    rewind(dIm);

    iBuf = (unsigned char*)malloc(iImLen * sizeof(unsigned char));
    dBuf = (unsigned char*)malloc(dImLen * sizeof(unsigned char));

    if(iBuf == NULL || dBuf == NULL){
        printf("E2\n");
        return;
    }

    iImRLen = fread(iBuf,1,iImLen,iIm);
    dImRLen = fread(dBuf,1,dImLen,dIm);

    if(iImRLen != iImLen || dImRLen != dImLen){
        printf("E3\n");
        return;
    }

    fclose(iIm);
    fclose(dIm);
}
void inDDisk(){
    unsigned int temp = 0, index = 0, i;
    for(i = 0; i < 4; i++){
        temp = (temp << 8) + dBuf[i];
    }

    reg[$sp] = temp;
    temp = 0;
    for(i = 4; i < 8; i++){
        temp = (temp << 8) + dBuf[i];
    }

    for(i = 8; i < 8+ temp*4; i++){
        dDisk[index++] = dBuf[i];
    }
}
void inIDisk(){
    unsigned int temp = 0, index, i;

    for(i = 0; i < 4; i++){
        temp = (temp << 8) + iBuf[i];
    }
    PC = temp;
    temp = 0;
    for(i = 4; i < 8; i++){
        temp = (temp << 8) + iBuf[i];
    }

    index = PC;
    for(i = 8; i < 8 + temp*4; i++){
        iDisk[index++] = iBuf[i];
    }
}

void printSnapShot(){
    int i = 0;
    fprintf(snap,"cycle %u\n", cycle++);
    for(i = 0; i < 32; i++){
        fprintf(snap,"$%02d: 0x%08X\n", i, reg[i]);
    }
    fprintf(snap,"PC: 0x%08X\n\n\n", PC);
}

void printReport(){
    fprintf( report, "ICache :\n");
    fprintf( report, "# hits: %u\n", ICache.hitNum );
    fprintf( report, "# misses: %u\n\n", ICache.missNum );
    fprintf( report, "DCache :\n");
    fprintf( report, "# hits: %u\n", DCache.hitNum );
    fprintf( report, "# misses: %u\n\n", DCache.missNum );
    fprintf( report, "ITLB :\n");
    fprintf( report, "# hits: %u\n", ITLB.hitNum );
    fprintf( report, "# misses: %u\n\n", ITLB.missNum );
    fprintf( report, "DTLB :\n");
    fprintf( report, "# hits: %u\n", DTLB.hitNum );
    fprintf( report, "# misses: %u\n\n", DTLB.missNum );
    fprintf( report, "IPageTable :\n");
    fprintf( report, "# hits: %u\n", IPageTable.hitNum );
    fprintf( report, "# misses: %u\n\n", IPageTable.missNum );
    fprintf( report, "DPageTable :\n");
    fprintf( report, "# hits: %u\n", DPageTable.hitNum );
    fprintf( report, "# misses: %u\n\n", DPageTable.missNum );
}
