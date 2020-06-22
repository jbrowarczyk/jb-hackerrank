#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() 
{

    int n, central, a, b;
    scanf("%d", &n);
    central =  (2*n - 2) / 2;
    for(int i = 0; i < 2*n - 1; i++){
        for(int j = 0; j < 2*n - 1; j++){
            a = abs(i - central);
            b = abs(j - central);
            printf("%d ", a >= b ? a+1 : b+1);
        }
        printf("\n");
    }
    return 0;
}