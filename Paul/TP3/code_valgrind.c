#include<stdio.h>
#include<stdlib.h>

void segfault(int *b, int l) {
    for (int i=0; i<l; i++)
        b[i] *= 2;
}

int main() {
    int* a = (int*) malloc(100*sizeof(int));
    int* b = (int*) malloc(100*sizeof(int));
    int l = 100;
    segfault(a, l);
    free(b);
    free(a);
    return 0;
}
