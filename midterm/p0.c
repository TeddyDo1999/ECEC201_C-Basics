

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char ** argv){
    int lenString;
    char currentChar;
    char firstChar;
    char lastChar;
 

    for (int i=1; i < argc; i++){
        
        
        lenString = strlen(argv[i]);
        // firstChar = argv[i][0];
        // lastChar = argv[i][lenString-1];
        char array[lenString];
        for (int j=0; lenString-j >= 0; j++){
            array[j] = argv[i][lenString-j];
            printf("%c", array[j]);
        }
        printf("\n");
    }
    return 0;
}
