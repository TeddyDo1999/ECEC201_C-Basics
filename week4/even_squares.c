#include <stdlib.h>
#include <stdio.h>

int main(int argc, char ** argv)
{
    int n=atoi(argv[1]);
    for (int i=1; (i*i)<=n; i++) {
        if (i%2==0) 
            printf("%d\n", i*i);
    }
    return 0;
}