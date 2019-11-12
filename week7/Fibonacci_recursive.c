
#include <stdio.h>
#include <stdlib.h>

int fi(int target){
    if (target == 1) {
        return 1;
    } else if (target == 0) {
        return 0;
    } else {
        return fi(target - 1) + fi(target - 2);
    }
}
    



int main(void){
    int t, num;
    printf("Enter the terminate \
    number for Fibonacci sequence \n");
    scanf("%d", &num);
    t = fi(num);
    printf("The %dth Fibonacci number is %d\n\n", num, t);
    return 0;
}