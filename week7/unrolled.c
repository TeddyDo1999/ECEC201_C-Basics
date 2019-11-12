
#include <stdio.h>
#include <stdlib.h>
#define MAX_ORDER 50

long int fi(int target){
    long int nums[MAX_ORDER];
    nums[0] = 0;
    nums[1] = 1;
    for (int i=2; i<=target; i++) {
        nums[i] = nums[i-1] + nums[i-2];
    } 
    return nums[target];
}


int main(){
    long int t, num;
    printf("Enter the terminate \
    number for Fibonacci sequence \n");
    scanf("%d", &num);
    t = fi(num);
    printf("The %dth Fibonacci number is %ld\n\n", num, t);
    return 0;
}