#include "BIZ_MT.h"
#include "../RandomFunctions.h"

MTUserArray * mtRandInit(MTRand * rand) {
    if(rand == NULL) {
        mt_def.arr_len = P;
        mt_def.offset = Q;
        mt_def.lower_mask = L_MASK;
        mt_def.higher_mask = H_MASK;
        mt_def.matrix_row = A;

        mt_def.hardening0 = U;
        mt_def.hardening1 = S;    
        mt_def.hardening2 = B;
        mt_def.hardening3 = T;
        mt_def.hardening4 = C;
        mt_def.hardening5 = L;

        mt_def.newX = (int32_t *) malloc(sizeof(int32_t) * mt_def.arr_len);
        mt_def.x = (int32_t *) malloc(sizeof(int32_t) * mt_def.arr_len);

        for(int i = 0; i < mt_def.arr_len; i++)
            mt_def.x[i] = getAbsStartRand();

    } else {
        rand->newX = (int32_t *) malloc(sizeof(int32_t) * mt_def.arr_len);

        mt_def.newX = rand->newX;

        mt_def.arr_len = rand->arr_len;
        mt_def.offset = rand->offset;
        mt_def.lower_mask = rand->lower_mask;
        mt_def.higher_mask = rand->higher_mask;
        mt_def.matrix_row = rand->matrix_row;

        mt_def.hardening0 = rand->hardening0;
        mt_def.hardening1 = rand->hardening1;    
        mt_def.hardening2 = rand->hardening2;
        mt_def.hardening3 = rand->hardening3;
        mt_def.hardening4 = rand->hardening4;
        mt_def.hardening5 = rand->hardening5;

        mt_def.x = rand->x;
    }

    MTUserArray * MTArr = (MTUserArray *) malloc(sizeof(MTUserArray)); 
    MTArr->ptr = mt_def.newX;
    MTArr->len = mt_def.arr_len;

    return(MTArr);
}
void mtDefRand() {
    for(int i = 0; i < mt_def.arr_len; i++) {
        int32_t y = 
            (mt_def.x[i] & mt_def.lower_mask) | (mt_def.x[(i + 1) % mt_def.arr_len] & mt_def.higher_mask); 
        if(mt_def.x[i] & 1) 
            mt_def.x[i] = mt_def.x[(i + mt_def.offset) % mt_def.arr_len] ^ (y >> 1) ^ mt_def.matrix_row;
        else 
            mt_def.x[i] = mt_def.x[(i + mt_def.offset) % mt_def.arr_len] ^ (y >> 1) ^ 0;

        y = mt_def.x[i];
        y = y ^ (y >> mt_def.hardening0);
        y = y ^ ((y << mt_def.hardening1) & mt_def.hardening2);
        y = y ^ ((y << mt_def.hardening3) & mt_def.hardening4);
        mt_def.newX[i] = y ^ (y >> mt_def.hardening5); 
    }
}
void mtDefKill(MTUserArray * MTArr) {
    if(MTArr != NULL) free(MTArr);
    
    free(mt_def.newX);
    free(mt_def.x);
}
int main() {
    MTUserArray * arr = mtRandInit(NULL);
    mtDefRand();

    for(int i = 0; i < arr->len; i++)
        printf("\n%d", arr->ptr[i]);

    mtDefKill(NULL);

    return(0);
}