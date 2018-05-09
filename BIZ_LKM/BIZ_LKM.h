#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define LKM_A 36261
#define LKM_C 66037
#define LKM_M 312500

typedef struct LKMSet {
    unsigned long long a;
    unsigned long long c;
    unsigned long long m;
} LKMSet;

typedef struct LKMrand {
    unsigned long long seed;
    LKMSet set;
} LKMrand;

LKMrand lkm_def;

const LKMSet def_set[] = {
    {106, 1283, 6075},
    {211, 1663, 7875},
    {421, 1663, 7875},
    {430, 2531, 11979},
    {936, 1399, 6655},
    {1366, 1283, 6075},
    {171, 11213, 53125},            //Values, that show great results
    {859, 2531, 11979},
    {419, 6173, 29282},
    {967, 3041, 14406},
    {141, 28411, 134456},
    {625, 6571, 31104},
    {1541, 2957, 14000},
    {1741, 2731, 12960},
    {1291, 4621, 21870}
};

#define SIZE 15

void lkmRandInit(LKMrand * rand);
unsigned long long lkmDefRand();

void lkmTestParam(LKMSet * set);
void lkmCrack(unsigned long long x1, unsigned long long x2);
