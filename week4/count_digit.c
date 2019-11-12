#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// This is for programming project 5.1 page 95
int main(int numargs, char ** argv)
{
    // if (1 != numargs) {
    //     printf("USAGE: count_digit <# to count its digit>");
    //     return -1;
    // }
    
    int num = atoi(argv[1]);
    float logTen=log10f(num);
    double numDigit=floor(logTen)+1;
    printf("%s has %.0f digits", argv[1], numDigit);
    
    return 0;
}