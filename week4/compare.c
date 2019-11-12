#include <stdlib.h>
#include <stdio.h>

int main(int argc, char ** argv)
{
    // if (3 != argc) {
    //     printf("USAGE: genRand <#ofRands> <filename>");
    //     return -1;
    // }
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    int num3 = atoi(argv[3]);
    int num4 = atoi(argv[4]);
    int min1, min3, min;
    int max3, max1, max;

    if (num1>= num2) {
        max1 = num1;
        min1 = num2;
    }
    else
    {
        max1 = num2; min1 = num1;
    }
    

    if (num3 >= num4) {
        max3 = num3;
        min3 = num4;
    }
    else {
        min3=num3; max3 =num4;
    } 
    
    if (min3 > min1)
        min = min1;
    else
        min = min3;
    
    if (max3 > max1)
        max = max3;
    else
        max = max1;
    printf("Largest number is %d \n Smallest number is %d \n", max, min);
    
    return 0;
}