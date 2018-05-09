#include "BIZ_LKM.h"
#include "../RandomFunctions.h"

int main() {
    unsigned long long a, c, m;
    int test;
    scanf("%llu", &a);
    scanf("%llu", &c);
    scanf("%llu", &m);
    
    LKMSet set = {a, c, m};

    lkmTestParam(&set);

    LKMrand my_rand = {getAbsStartRand(), set};
    lkmRandInit(NULL);

    unsigned long long i, my_seed = lkm_def.seed;
    lkmDefRand();
    for(i = 1; my_seed != lkm_def.seed; i++) {
        printf("\n%llu", lkmDefRand());
    }

    printf("\n\n%llu", i);

    return(0);
}

void lkmRandInit(LKMrand * rand) {
    if(rand == NULL) {
        lkm_def.set.a = LKM_A;
        lkm_def.set.c = LKM_C;
        lkm_def.set.m = LKM_M;

        lkm_def.seed = getAbsStartRand() % lkm_def.set.m;
    } else {
        lkm_def.seed = rand->seed % rand->set.m;
        lkm_def.set = rand->set;
    }
}
unsigned long long lkmDefRand() {
    lkm_def.seed = (lkm_def.seed * lkm_def.set.a + lkm_def.set.c) % lkm_def.set.m;

    return(lkm_def.seed);
}
void lkmTestParam(LKMSet * set) { 
    int test;
    unsigned long per;
    _Bool flag;
    START:
    flag = 0;

    if(set->a >= set->m || set->c >= set->m) { printf("\nс і а мусять бути менші за m!"); flag = 1; }

    printf("\nВведіть приблизне значення періоду, якого ви хочете досягнути: ");
    scanf("%lu", &per);

    if(per > (set->m) && (per - (set->m)) > 500) { printf("\nНедостатньо велике значення m - через це період буде малим\n"); };

    if(set->a == 0 || set->a == 1) { printf("Потрібно вибирати нетривіальне a\n"); flag = 1; }
    if(set->c == 0 || set->c == 1) { printf("Потрібно вибирати нетривіальне c\n"); flag = 1; }
    

    if((set->m) != __UINT64_MAX__) {
        printf("\nКраще обирати параметр m таким, щоб він був 2^q, де q - розмір машинного слова в бітах.");
        printf("\nУ вашому випадку q = %d", 8 * sizeof(long));
    }
    
    if(gcd(set->c, set->m) != 1) { 
        printf("\nЧисла c і m мусять бути взаємно-простими.");
        flag = 1;
    }

    if(((set->m) % 4) == 0 && ( ((set->a) - 1) % 4 ) != 0) {
        printf("\nОскільки m кратно 4, необхідно, щоб (a - 1) був кратним 4.\n");
        flag = 1;
    }

    int temp_flag = 0;

    for(unsigned long long i = 2; i <= (set->a - 1) / 2; i++) {
        if(( ( (((set->a) - 1) % i) == 0 ) && ( ((set->m) % i) == 0 ) && (is_simple(i)) )) {
            temp_flag = 1;
            break;
        }
    }
    if(temp_flag == 0) { printf("\na - 1 мусить бути кратним p, для деякого простого p, яке є дільником m\n"); flag = 1;}

    if(flag == 1) {
        printf("\nДані можна покращити, бажаєте обрати з уже перевірених значень?. '1' - так, '0' - ні\n");
        scanf("%d", &test);
        if(test == 1) {
            for(int i = 0; i < SIZE; i++) {
                printf("\n%d) a: %llu", i + 1, def_set[i].a);
                printf("\n    c: %llu",        def_set[i].c);
                printf("\n    m: %llu",        def_set[i].m);            
            }

            printf("\nОберіть номер який бажаєте використати: ");
            scanf("%d", &test);

            (set->a) = def_set[test - 1].a;
            (set->c) = def_set[test - 1].c;
            (set->m) = def_set[test - 1].m;
        } else if(test == 0) 
        {
            printf("Нехай вони залишаться такими ж!\n");
            printf("\nДивлячись на зауваження змініть їх самостійно!. '1' - так, '0' - ні\n");
            scanf("%d", &test);
            if(test == 1) 
            {
                printf("Введіть а, c, m: \n");
                scanf("%llu", &set->a);
                scanf("%llu", &set->c);
                scanf("%llu", &set->m);
                goto START;             //Початок функції, використовую goto, бо при рекурсії були б наслідки, а goto виручає в цьому разі
            } else if(test == 0) printf("\nЯк забажаєте!\n");
        }
    }

    if(flag == 0) printf("\n\nВхідні дані - чудовий вибір!\n");


    printf("\nВаші значення: ");
    printf("\na: %llu", (set->a));
    printf("\nc: %llu", (set->c));
    printf("\nm: %llu\n", (set->m));

}
void lkmCrack(unsigned long long x1, unsigned long long x2) {

}