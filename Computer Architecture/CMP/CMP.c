#include "CMP.h"
#include "Var.h"

void initCMP(){
    int i, j;
    iPTEntry = 1024 / init.iMemPageSize;
    dPTEntry = 1024 / init.dMemPageSize;

    iTLBEntry = iPTEntry / 4;
    dTLBEntry = dPTEntry / 4;

    iMEMEntry = init.iMemSize / init.iMemPageSize;
    dMEMEntry = init.dMemSize / init.dMemPageSize;

    iCacheEntry.row = init.iCacheTotalSize / init.iCacheSet / init.iCacheBlockSize;
    iCacheEntry.col = init.iCacheSet;

    dCacheEntry.row = init.dCacheTotalSize / init.dCacheSet / init.dCacheBlockSize;
    dCacheEntry.col = init.dCacheSet;

    iTLB = (TLB*)malloc(sizeof(TLB) * iTLBEntry);
    dTLB = (TLB*)malloc(sizeof(TLB) * dTLBEntry);

    iPT = (PageTable*)malloc(sizeof(PageTable) * iPTEntry);
    dPT = (PageTable*)malloc(sizeof(PageTable) * dPTEntry);

    iMem = (Memory*)malloc(sizeof(Memory) * iMEMEntry);
    dMem = (Memory*)malloc(sizeof(Memory) * dMEMEntry);

    iCache = (Cache**)malloc(sizeof(Cache*) * iCacheEntry.row);
    for(i = 0; i < iCacheEntry.row; i++){
        iCache[i] = (Cache*)malloc(sizeof(Cache) * iCacheEntry.col);
        for(j = 0; j < iCacheEntry.col; j++){
            iCache[i][j].valid = 0;
            iCache[i][j].MRU = 0;
        }
    }

    dCache = (Cache**)malloc(sizeof(Cache*) * dCacheEntry.row);
    for(i = 0; i < dCacheEntry.row; i++){
        dCache[i] = (Cache*)malloc(sizeof(Cache) * dCacheEntry.col);
        for(j = 0; j < dCacheEntry.col; j++){
            dCache[i][j].valid = 0;
            dCache[i][j].MRU = 0;
        }
    }

    for(i = 0; i < iTLBEntry; i++){
        iTLB[i].PutInCycle = -1;
        iTLB[i].valid = 0;
    }
    for(i = 0; i < dTLBEntry; i++){
        dTLB[i].PutInCycle = -1;
        dTLB[i].valid = 0;
    }
    for(i = 0; i < iPTEntry; i++){
        iPT[i].valid = 0;
    }
    for(i = 0; i < dPTEntry; i++){
        dPT[i].valid = 0;
    }
    for(i = 0; i < iMEMEntry; i++){
        iMem[i].valid = 0;
    }
    for(i = 0; i < dMEMEntry; i++){
        dMem[i].valid = 0;
    }

    IPageTable.hitNum = IPageTable.missNum = 0;
    DPageTable.hitNum = DPageTable.missNum = 0;
    ICache.hitNum = ICache.missNum = 0;
    DCache.hitNum = DCache.missNum;
    ITLB.hitNum = ITLB.missNum = 0;
    DTLB.hitNum = DTLB.missNum = 0;
}

void checkCMP(int mode){
    if(mode == 1){
        checkTLB(iTLB, iTLBEntry, mode);
    }else{
        checkTLB(dTLB, dTLBEntry, mode);
    }
}

void checkCache(int ppn, int mode){
    int offset, PA, index, tag, i, j, count, choose = 0;
    if(mode == 1){
        offset = PC % init.iMemPageSize;
        PA = ppn * init.iMemPageSize + offset;
        index = (PA / init.iCacheBlockSize) % iCacheEntry.row;
        tag = (PA / init.iCacheBlockSize) / iCacheEntry.row;

        for(i = 0; i < iCacheEntry.col; i++){
            if(iCache[index][i].valid > 0 && iCache[index][i].tag == tag){
                //printf("%d %d\n",PC, cycle);
                ICache.hitNum++;
                //printf("~~%d %d\n", cycle, ICache.hitNum);
                count = 0;
                for(j = 0; j < iCacheEntry.col; j++)
                    if(iCache[index][j].MRU == 0) count++;

                if(count == 1 && iCache[index][i].MRU == 0)
                    for(j = 0; j < iCacheEntry.col; j++) iCache[index][j].MRU = 0;
                iCache[index][i].MRU = 1;
                return;
            }
        }
        ICache.missNum++;

        if(iCacheEntry.col > 1){

            for(i = 0; i < iCacheEntry.col;i++)
                if(iCache[index][i].valid == 0){
                    choose = i;
                    break;
                }

            if(i == iCacheEntry.col)
                for(i = 0; i < iCacheEntry.col;i++)
                    if(iCache[index][i].MRU == 0){
                        choose = i;
                        break;
                    }
            iCache[index][choose].tag = tag;
            iCache[index][choose].valid = 1;

            count = 0;
            for(j = 0; j < iCacheEntry.col; j++){
                if(iCache[index][j].MRU == 0) count++;
            }

            if(count == 1 && iCache[index][choose].MRU == 0){
                for(j = 0; j < iCacheEntry.col; j++)
                    iCache[index][j].MRU = 0;
            }

            iCache[index][choose].MRU = 1;

        }else{
            iCache[index][choose].MRU = 1;
            iCache[index][choose].tag = tag;
            iCache[index][choose].valid = 1;
        }

    }else{

        offset = Pos % init.dMemPageSize;
        PA = ppn * init.dMemPageSize + offset;
        index = (PA / init.dCacheBlockSize) % dCacheEntry.row;
        tag = (PA / init.dCacheBlockSize) / dCacheEntry.row;

        for(i = 0; i < dCacheEntry.col;i++){

            if(dCache[index][i].valid > 0 && dCache[index][i].tag == tag){

                DCache.hitNum++;
                count = 0;
                for(j = 0; j < dCacheEntry.col; j++)
                    if(dCache[index][j].MRU == 0)count++;

                if(count == 1 && dCache[index][i].MRU == 0){
                    for(j = 0; j < dCacheEntry.col; j++)
                        dCache[index][j].MRU = 0;
                }
                dCache[index][i].MRU = 1;
                return;
            }
        }
        DCache.missNum++;

        if(dCacheEntry.col > 1){
            for(i = 0; i < dCacheEntry.col;i++)
                if(dCache[index][i].valid == 0){
                    choose = i;
                    break;
                }

            if(i == dCacheEntry.col)
                for(i = 0; i < dCacheEntry.col;i++)
                    if(dCache[index][i].MRU == 0){
                        choose = i;
                        break;
                    }
            dCache[index][choose].tag = tag;
            dCache[index][choose].valid = 1;

            count = 0;
            for(j = 0; j < dCacheEntry.col; j++){
                if(dCache[index][j].MRU == 0) count++;
            }

            if(count == 1 && dCache[index][choose].MRU == 0){
                for(j = 0; j < dCacheEntry.col; j++) dCache[index][j].MRU = 0;
            }
            dCache[index][choose].MRU = 1;
        }else{
            dCache[index][choose].MRU = 1;
            dCache[index][choose].tag = tag;
            dCache[index][choose].valid = 1;
        }
    }
}

int checkPT(PageTable pt[], int n, int mode, int vpn){
    if(mode == 1){
        if(pt[vpn].valid > 0){
            IPageTable.hitNum++;
            UpdateMemory(iMem,pt[vpn].PPN);
            return pt[vpn].PPN;
        }else{
            IPageTable.missNum++;
            pt[vpn].PPN = Pagefault(iMem,iMEMEntry,mode);
            pt[vpn].valid = 1;
            return pt[vpn].PPN;
        }

    }else{
        if(pt[vpn].valid > 0){
            DPageTable.hitNum++;
            UpdateMemory(dMem,pt[vpn].PPN);
            return pt[vpn].PPN;
        }else{
            DPageTable.missNum++;
            pt[vpn].PPN = Pagefault(dMem,dMEMEntry,mode);
            pt[vpn].valid = 1;
            return pt[vpn].PPN;
        }
    }
}

int Pagefault(Memory memory[], int n, int mode){
    int i = 0, update = 1, earliest = 0;
    if(mode == 1){

        if(memory[earliest].valid != 0){
            for(i = 1; i < n; i++){
                if(memory[i].valid == 0){
                    earliest = i;
                    update = 0;
                    break;
                }else if(memory[i].PutInCycle < memory[earliest].PutInCycle){
                    earliest = i;
                    update = 1;
                }
            }
        }else{
            update = 0;
        }

        if(update > 0){
            UpdatePT(iPT, iPTEntry, earliest);
            UpdateTLB(iTLB, earliest, iTLBEntry, mode);
            UpdateCache(earliest, mode);
        }

        memory[earliest].valid = 1;
        memory[earliest].PutInCycle = cycle;
        return earliest;

    }else{

        if(memory[earliest].valid != 0){
            for(i = 1; i < n; i++){
                if(memory[i].valid == 0){
                    earliest = i;
                    update = 0;
                    break;
                }else if(memory[i].PutInCycle < memory[earliest].PutInCycle){
                    earliest = i;
                    update = 1;
                }
            }
        }else{
            update = 0;
        }
        if(update){
            UpdatePT(dPT, dPTEntry, earliest);
            UpdateTLB(dTLB, earliest, dTLBEntry, mode);
            UpdateCache(earliest, mode);
        }

        memory[earliest].valid = 1;
        memory[earliest].PutInCycle = cycle;
        return earliest;
    }
}

void UpdateMemory(Memory memory[], int ppn){

    memory[ppn].PutInCycle = cycle;
}

void UpdateTLB(TLB tlb[], int replace, int n, int mode){
    int i;
    for(i = 0; i < n; i++){
        if(tlb[i].PPN == replace && tlb[i].valid > 0){
            tlb[i].valid = 0;
        }
    }
}

void UpdatePT(PageTable pt[], int n, int replace){
    int i;
    for(i = 0; i < n;i++){
        if(pt[i].PPN == replace && pt[i].valid > 0) {
            pt[i].valid = 0;
        }
    }
}

void UpdateCache(int replace, int mode){
    int offset, PA, index, tag, i;
    if(mode == 1){
        for(offset = 0; offset < init.iMemPageSize; offset++){
            PA = replace * init.iMemPageSize + offset;
            index = (PA / init.iCacheBlockSize) % iCacheEntry.row;
            tag = (PA / init.iCacheBlockSize) / iCacheEntry.row;
            //puts("K1");

            for(i = 0; i < iCacheEntry.col; i++){
                if(iCache[index][i].tag == tag && iCache[index][i].valid > 0){
                    iCache[index][i].valid = 0;
                    iCache[index][i].MRU = 0;
                    //puts("iK1");
                    break;
                }
            }
        }
    }else{
        //puts("SSS");
        for(offset = 0; offset < init.dMemPageSize; offset++){
            PA = replace * init.dMemPageSize + offset;
            index = (PA / init.dCacheBlockSize) % dCacheEntry.row;
            tag = (PA / init.dCacheBlockSize) / dCacheEntry.row;

            for(i = 0; i < dCacheEntry.col; i++){
                //printf("%d %d %d\n", index, dCache[0][0].valid, dCache[index][i].tag);
                if(dCache[index][i].tag == tag && dCache[index][i].valid > 0){
                    dCache[index][i].valid = 0;
                    dCache[index][i].MRU = 0;
                    //puts("iK2");
                    break;
                }
            }
        }
    }

}

void checkTLB(TLB tlb[], int n, int mode){
    int indexOfTLB, i = 0, vpn, ppn;
    if(mode == 1){
        vpn = PC / init.iMemPageSize;
        for(i = 0; i < n ; i++) {
            if(tlb[i].VPN == vpn && tlb[i].valid > 0){
                ITLB.hitNum++;
                tlb[i].PutInCycle = cycle;
                checkCache(tlb[i].PPN,mode);
                return;
            }
        }
        ITLB.missNum++;

        ppn = checkPT(iPT, iPTEntry, mode, vpn);

        indexOfTLB = 0;

        if(tlb[indexOfTLB].valid != 0){
            for(i = 1; i < n; i++){
                if(tlb[i].valid == 0){
                    indexOfTLB = i;
                    break;
                }else if(tlb[i].PutInCycle < tlb[indexOfTLB].PutInCycle)
                    indexOfTLB = i;
            }
        }
        tlb[indexOfTLB].PPN = ppn;
        tlb[indexOfTLB].valid = 1;
        tlb[indexOfTLB].PutInCycle = cycle;
        tlb[indexOfTLB].VPN = vpn;
        checkCache(tlb[indexOfTLB].PPN,mode);

    }else{
        vpn = Pos / init.dMemPageSize;
        for(i = 0;i < n; i++) {
            if(tlb[i].VPN == vpn && tlb[i].valid > 0){
                //printf("hit\n");
                DTLB.hitNum++;
                tlb[i].PutInCycle = cycle;
                checkCache(tlb[i].PPN,mode);
                return;
            }
        }
        DTLB.missNum++;

        ppn = checkPT(dPT, dPTEntry, mode, vpn);

        indexOfTLB = 0;

        if(tlb[indexOfTLB].valid != 0){
            for(i = 1; i < n; i++){
                if(tlb[i].valid == 0){
                    indexOfTLB = i;
                    break;
                }else if(tlb[i].PutInCycle < tlb[indexOfTLB].PutInCycle)
                    indexOfTLB = i;
            }
        }

        tlb[indexOfTLB].PPN = ppn;
        tlb[indexOfTLB].valid = 1;
        tlb[indexOfTLB].PutInCycle = cycle;
        tlb[indexOfTLB].VPN = vpn;
        checkCache(tlb[indexOfTLB].PPN,mode);
    }
}
