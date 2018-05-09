#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <inttypes.h>

#define W 32
#define P 624
#define Q 397
#define R 31
#define A 2567483615
#define U 11
#define S 7
#define T 15
#define L 18
#define B 2636928640
#define C 4022730752
#define H_MASK 2147483647
#define L_MASK 2147483648

typedef struct MTUserArray {
    int32_t * ptr;
    unsigned int len;
} MTUserArray;

typedef struct MTRand {
    int32_t * newX;
    unsigned int arr_len;
    unsigned int offset;
    
    unsigned int hardening0;
    unsigned int hardening1;
    int32_t hardening2;
    unsigned int hardening3;
    int32_t hardening4;
    unsigned int hardening5;

    int32_t * x;
    int32_t lower_mask;
    int32_t higher_mask;
    int32_t matrix_row;
} MTRand;


MTRand mt_def;

MTUserArray * mtRandInit(MTRand * rand);
void mtDefRand();
void mtDefKill();