#include "BIZ_LKM.h"
#include "../RandomFunctions.h"

int main() {
    int64_t x0, x1, x2, x3, x4;

    LKMSet set = {213, 324, 2617};
    LKMrand rand;
    rand.set = set;
    rand.seed = 200;

    lkmRandInit(NULL);

   /* printf("Ваша послідовність: ");

    for(int i = 0; i < 100; i++) { if(i % 4 ==0) printf("\n"); printf("%" PRId64 "   ", lkmDefRand());}
    */
    x0 = lkmDefRand();
    x1 = lkmDefRand();
    x2 = lkmDefRand();
    x3 = lkmDefRand();

    printf("%" PRId64 " %" PRId64 " %" PRId64 " %" PRId64 "\n", x0, x1, x2, x3);

    for(int i = 0; i < 20; i++) printf("%" PRId64 "\n", lkmDefRand());

    node * n;

    lkmCrack(&n, x0, x1, x2, x3);

    lkmRedList(&n);

    clear_list(&n);

    return(0);
}
void lkmCrack(node ** h, int64_t x0,  int64_t x1,  int64_t x2, int64_t x3) {
    //x1 = (a * x0 + c) mod m
    //x2 = (a * x1 + c) mod m               a, c, m ?
    //x3 = (a * x2 + c) mod m

    int64_t k1 = x1 - x2;
    int64_t k2 = x0 - x1;
    int64_t k3 = x2 - x3;
    int64_t k4 = x1 - x2;
    
    int64_t lowet_common_denominator = lcd(k2, k4);
    
    int64_t k11 = (-lowet_common_denominator * k1) / k2;    //k1 = a*k2 mod m
    int64_t k22 =  -lowet_common_denominator;
    int64_t k33 = ( lowet_common_denominator * k3) / k4;    //k3 = a*k4 mod m
    int64_t k44 =   lowet_common_denominator;
    
    int64_t m_denominator = k11 + k33; // (k11 + k33 = 0 mod m) ==> (m_denominator % m = 0)

    m_denominator = m_denominator >= 0 ? m_denominator : -m_denominator;// число дільником якого є шукане M

    if(m_denominator == 0) { 
        printf("Недостатньо інформації, введіть наступне число, (-1) щоб завершити роботу: ");
        int64_t next;
        scanf("%" PRId64 , &next);
        if(next == -1) return;
        lkmCrack(h, x1, x2, x3, next); //Якщо число на яке ділиться М буде дорівнювати нуло, тоді невизначеність
        return; 
    }
    
    int flag = 0;
    
    for(int64_t i = max4ll(x0, x1, x2, x3); i <= m_denominator / 2; i++) {
        if(m_denominator % i == 0) {
            if(flag == 0) { (*h) = init_node(-1, -1, i); flag = 1; }
            else {
                add_node(-1, -1, i, h);    
            }
        } 
    }

    if(flag == 0) { (*h) = init_node(-1, -1, m_denominator); }
    else {
        add_node(-1, -1, m_denominator, h);
    }

    node * temp = *h;

    while(temp) {
        int64_t new_k1 = IS_EQUAL(k1, temp->m);
        int64_t new_k2 = IS_EQUAL(k2, temp->m);

        for(int64_t j = 0; j <= temp->m; j++) {
        
            if(new_k1 == (j * new_k2) % temp->m) {
                int64_t temp_int = x1 - ((j * x0) % temp->m);
        
                if(temp->a == -1) {
                    temp->a = j;
                    temp->c = IS_EQUAL(temp_int, temp->m); 
                } else {
                    add_node(j, IS_EQUAL(temp_int, temp->m), temp->m, h);
                }
            }
        
        }

        temp = temp->next;
    }
}
void lkmRedList(node ** h) {
    printf("Ваш список: ");
    print_list(*h);

    int len = 2;
    int64_t * num = (int64_t *) malloc(sizeof(int64_t) * len);
    printf("Введіть x0, x1\n");
    scanf("%" PRId64, &num[0]);
    scanf("%" PRId64, &num[1]);

    printf("Продовжуйте вводити числа\n");
    printf("-1 - щоб зупинитись");

    while(1){
        node * temp = (*h);

        while(temp) {
            if(num[len - 1] != (temp->a * num[len - 2] + temp->c) % temp->m)
                del_node(temp->a, temp->c, temp->m, h);
            temp = temp->next;
        }

        printf("1Список можливих варіантів на даний момент: \n");
        print_list(*h);

        int count = list_len(*h);
        if(count == 1) {printf("2Вітаємо, залишилось лише одне рішення!\n"); return; }
        if(count <= 0) {printf("3Щось пішло не так і варіантів не залишилось, спробуйте ще раз!\n"); return; }

        int64_t test;
        scanf("%" PRId64, &test);
        if(test == -1) return;
        len++;
        num = (int64_t *) realloc(num, len * sizeof(int64_t));
        num[len - 1] = test;
    }
}
void lkmRandInit(LKMrand * rand) {
    if(rand == NULL) {
        lkm_def.set.a = LKM_A;
        lkm_def.set.c = LKM_C;
        lkm_def.set.m = LKM_M;

        lkm_def.seed = getAbsStartRand() % lkm_def.set.m;
        printf("%" PRId64 "\n\n", lkm_def.seed);
    } else {
        lkm_def.seed = rand->seed % rand->set.m;

        lkm_def.set.a = rand->set.a % rand->set.m;
        lkm_def.set.c = rand->set.c % rand->set.m;
        lkm_def.set.m = rand->set.m;

    }
}
int64_t lkmDefRand() {
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

    for(int64_t i = 2; i <= (set->a - 1) / 2; i++) {
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
                printf("\n%d) a: %" PRId64 "\n", i + 1, def_set[i].a);
                printf("\n    c: %" PRId64 "\n",        def_set[i].c);
                printf("\n    m: %" PRId64 "\n",        def_set[i].m);            
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
                scanf("%" PRId64, &set->a);
                scanf("%" PRId64, &set->c);
                scanf("%" PRId64, &set->m);
                goto START;             //Початок функції, використовую goto, бо при рекурсії 
                                                //були б наслідки, а goto виручає в цьому разі
            } else if(test == 0) printf("\nЯк забажаєте!\n");
        }
    }

    if(flag == 0) printf("\n\nВхідні дані - чудовий вибір!\n");


    printf("\nВаші значення: ");
    printf("\na: %" PRId64 "\n", (set->a));
    printf("\nc: %" PRId64 "\n", (set->c));
    printf("\nm: %" PRId64 "\n", (set->m));

}