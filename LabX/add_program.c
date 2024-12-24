#include <stdio.h>

int add(int *a, int *b, int *c){
    return *a + *b + *c;
}

int main(){
    int a = 1;
    int b = 2;
    int c = 3;
    printf("The sum of 1, 2, and 3 is %d\n", add(&a, &b, &c));
    return 0;
}