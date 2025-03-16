#include<stdio.h>
#include<stdlib.h>

void segfault(int *b, int l) {
    for (int i=0; i<l; i++)
        b[i] *= 2;
}

int main() {
    int* a = malloc(10*sizeof(int));
    int* b = malloc(100*sizeof(int));
    int l = 10;
    segfault(a, l);
    free(a);
    free(b);
    return 0;
}