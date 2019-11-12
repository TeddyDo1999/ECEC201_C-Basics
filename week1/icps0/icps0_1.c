#include <stdio.h>
#define pi (22/7.0f)  //comment still work here

int main(void) {
    int r;
    float area;

    printf("Enter radius: \n");
    scanf("%d", &r);
    area = r * r * pi; 
    printf("Area is %f", area);
    return 0;
    }

        //when allocating a variable (for ex int), max value will be stored 
    //(with int, it will be 32767, which is 2**15 -1 which is 32KB) 