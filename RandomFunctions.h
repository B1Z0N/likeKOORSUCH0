#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define IS_EQUAL(x, m) x >= 0 ? x : x + m

int64_t gcd( int64_t a,  int64_t b);
int64_t lcd(int64_t a, int64_t b);
int64_t max4ll(int64_t a, int64_t b, int64_t c, int64_t d);
int64_t mod(int64_t a, int64_t b);

int is_simple(unsigned long long x1);
void print_byte(int32_t var, int size);
int getAbsStartRand();