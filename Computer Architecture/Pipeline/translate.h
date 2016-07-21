void getAddr();
void getRs(unsigned int,unsigned char*);
void getRt(unsigned int,unsigned char*);
void getRd(unsigned int,unsigned char*);
void getShamt(unsigned int, unsigned char*);
void getImmediateBoth(unsigned int);
void getPos();
void Decode();
void bufferCopy(buffer*, buffer*);
void bufferClear(buffer*);

int between(unsigned char, unsigned char, unsigned char);
