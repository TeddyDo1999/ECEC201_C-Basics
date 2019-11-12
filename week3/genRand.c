#include <stdlib.h>
#include <stdio.h>

int main(int argc, char ** argv)
{

    if (3 != argc) {
        printf("USAGE: genRand <#ofRands> <filename>");
        return -1;
    }
    srand(time(0));

    float fRand, mean, fRandMin=1, fRandMax=0;
    float sum=0;
    int nRandom;
    FILE *excel;

    nRandom = atoi(argv[1]);
    excel = fopen(argv[2], "w");

    if (excel == NULL){
        printf("Failed to open file\n");
        exit(EXIT_FAILURE);
    }

    for (int i=0; i<nRandom; i++){
        
        fRand=(float)rand()/RAND_MAX;
        
        if (fRand < fRandMin) fRandMin=fRand;
        
        if (fRand>fRandMax) fRandMax = fRand;
        //printf("%f \n", fRand);
        sum += fRand;
        
        if (i < nRandom - 1) fprintf(excel, "%f, ", fRand);
        else fprintf(excel, "%f\n", fRand);
    
    } //i==nRandom
    mean = sum/nRandom;
    fprintf(excel, "sum is %f\n", sum);
    fprintf(excel, "mean is %f\n", mean);
    fclose(excel);

    return 0;
}