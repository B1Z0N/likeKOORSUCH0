#include "RandomFunctions.h"
#include <inttypes.h>

#ifdef __linux__
    #include <sys/random.h>
    #include <fcntl.h>
    #include <unistd.h>
#elif _WIN32 
    #include <Wincrypt.h>
#endif



int64_t mod(int64_t a, int64_t b) {
    if(a > 0 && b > 0) return (a % b);
    else return(b + a % b);
}
int64_t gcd( int64_t a,  int64_t b) {
    a = ( a > 0) ? a : -a;
    b = ( b > 0) ? b : -b;

    while(a!=b)
    {
        if(a > b)
            a -= b;
        else
            b -= a;
    }

    return a;
}
 int64_t lcd(int64_t a, int64_t b) {
    return(a * b / gcd(a, b));
}
 int64_t max4ll(int64_t a, int64_t b, int64_t c, int64_t d) {
    int64_t max1, max2;
    
    if(a > b) max1 = a; else max1 = b;
    
    if(c > d) max2 = c; else max2 = d;

    if(max1 > max2) return(max1); else return(max2);
}
int is_simple(unsigned long long x1) {
    for(unsigned long long i = 2; i < sqrt(x1); i++) {
        if(x1 % i == 0) return(0);
    }

    return(1);
}

void print_byte(int32_t var, int size) {
    int t = 0;
    for(int i = size * 8 - 1; i >= 0; i--, t++) {
        if(t % 4 == 0) printf("|");
        printf("%d", (var >> i) & 1);
    }
    printf("\n");
}
int getAbsStartRand() {
    int randomNumber;
    #ifdef __linux__
        int test = getrandom(&randomNumber, sizeof(randomNumber), 0);
        if(test == -1) return(clock());
    #elif _WIN32
        HCRYPTPROV   hCryptProv;
        BYTE pbData[sizeof(int)];
        if(CryptGenRandom(hCryptProv, sizeof(int), pbData) == 0) return(clock());

        randomNumber = (int) pbData;
    #else
        return(clock());
    #endif

    return(abs(randomNumber));
}