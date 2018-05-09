#include "RandomFunctions.h"
#include <inttypes.h>

#ifdef __linux__
    #include <sys/random.h>
    #include <fcntl.h>
    #include <unistd.h>
#endif

int gcd(unsigned long long a, unsigned long long b) {
    return b ? gcd(b, a % b) : a;
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
        /*int randomData;
        randomData = open("/dev/random",  O_RDONLY);
            if (randomData < 0) return clock();
        else {
            int test;
            ssize_t result = read(randomData, &randomNumber, sizeof(randomNumber));
            if (result < 0) {
                return clock();
            }
            close(randomData);
        }*/
    #else
        return(clock());
    #endif

    return(abs(randomNumber));
}