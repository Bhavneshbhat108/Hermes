#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <unistd.h>

#define MAXBLKS 16
#define HDRKEY 3031
#define BUFKEY 3032
#define BLKSIZE (32*512*4096)

typedef struct {
    unsigned int flag;
    unsigned int curr_blk, curr_rec, blk_size;
    int overflow;
    double comptime[MAXBLKS];
    double datatime[MAXBLKS];
    unsigned char data[(long)(BLKSIZE) * (long)(MAXBLKS)];
} Buffer;

typedef struct {
    unsigned int active, status;
    double comptime, datatime, reftime;
    struct timeval timestamp[MAXBLKS];
    struct timeval timestamp_gps[MAXBLKS];
    double blk_nano[MAXBLKS];
} Header;

static volatile sig_atomic_t keep = 1;
static void handler(int _) {
    (void)_;
    keep = 0;
    exit(_);
}

unsigned char* get_raw_data(int n1, int n2,int *block_size) {
    int idhdr;
    int idbuf;
    Header *HdrRead;
    Buffer *BufRead;

    signal(SIGINT, handler);

    idhdr = shmget(HDRKEY, sizeof(Header), SHM_RDONLY);
    idbuf = shmget(BUFKEY, sizeof(Buffer), SHM_RDONLY);
    if (idhdr < 0 || idbuf < 0) {
        printf("\nShared memory does not exist.\n");
        return NULL;
    }

    HdrRead = (Header *)shmat(idhdr, 0, SHM_RDONLY);
    BufRead = (Buffer *)shmat(idbuf, 0, SHM_RDONLY);
    if ((BufRead) == (Buffer *)-1) {
        printf("\nCould not attach to shared memory.\n");
        return NULL;
    }
    int i;
    int block = n2 - n1 + 1;
    *block_size = block * BLKSIZE;
    unsigned char *raw = (unsigned char *)malloc(*block_size);

    //int n_i = n1 % MAXBLKS;
        if (n1 + MAXBLKS >= BufRead->curr_blk) {
        printf("The block is not overwritten \n");
        printf("Current block %d\n", BufRead->curr_blk);
        printf("Block to read %d \n", n1);
        for ( i=0; i<block; i++){
        int curr_ni = (n1+i) % MAXBLKS;
        //printf("Record block to Read%d\n", curr_ni);
        memcpy(raw + (i*BLKSIZE), BufRead->data + ((long)BLKSIZE * (long)curr_ni),BLKSIZE);
    }} else {
        printf("Data is not here sadly !! \n");
        free(raw);
        return NULL;
       }
    
    return raw;

}
void free_raw_data(unsigned char *raw) {
    free(raw);
}
