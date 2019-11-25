#include <stdlib.h>
#include <stdio.h>
#define NUM_NODES 10

typedef struct _LLNODE
{
    double dRandom01;
    struct _LLNODE *pNext;//tree pointers
    struct _LLNODE *pPrevious
}LLNODE, *PLLNODE;
//defining LLNODE (the struct) and PLLNODE: the pointer to that kind of struct
//Linter: intellisense tells you where there is potential wrong syntax

PLLNODE ranNodeGen()
{
    PLLNODE pNode;
    pNode=malloc(sizeof(LLNODE));
    if (NULL == pNode) {  //!pNode
        printf("ERROR, out of memory");
        return NULL;
    }
    pNode->dRandom01=(double)random()/RAND_MAX;
    pNode->pNext = NULL;
    pNode->pPrevious = NULL;
    return pNode;
} //ranNodeGen

void addNodeToTree(PLLNODE* ppRoot, PLLNODE pNode, PLLNODE* ppTail)
{    
    PLLNODE pInsertBefore= *ppRoot, pInsertAfter=NULL;
    if (NULL == pInsertBefore){
        //tree was empty now not. pNode is now the only node in list, also root
        *ppRoot = pNode;
        *ppTail = pNode;
        //return 1;//pNode is now the root and the tail 
    }
    while (NULL != pInsertBefore && pInsertBefore->dRandom01 < pNode->dRandom01){
        pInsertAfter = pInsertBefore;
        pInsertBefore = pInsertBefore->pNext;    
    } //Now the sequence is after -> pNode -> before
    
    //insert node before root
    pNode->pNext=pInsertBefore;
    pNode->pPrevious =pInsertAfter;
    if (NULL == pInsertAfter){
        *ppRoot = pNode;
    } else {
        pInsertAfter->pNext = pNode;
    }
    if (NULL == pInsertBefore){
        *ppTail = pNode;
    } else {
        pInsertBefore->pPrevious = pNode;
        while (NULL != pInsertBefore) {
            *ppTail = pInsertBefore;
            pInsertBefore = pInsertBefore->pNext;
        }
    }
    return 0;
}//addNodeToTree

void printList(PLLNODE root){
    PLLNODE pNode = root;
    while (NULL != pNode) {
        printf(" %.2f", pNode->dRandom01);
        if (NULL != pNode->pNext)
            printf(",");
        pNode = pNode->pNext;
    }
    printf("\n");
}

void clean(PLLNODE* pRoot)
{
    PLLNODE current = *pRoot;
    PLLNODE next;
    while (current != NULL){
        next = current->pNext;
        free(current); //pass a pointer to free, memory pointed will be free
        current = next;//pointer point somewhere else
    }
    *pRoot = NULL;
}

void printToFile(const PLLNODE root, const PLLNODE tail, int startOption, FILE *out){
    PLLNODE pNode;
    if (startOption == 0){ //start from root
        out = fopen("week9/llForward.txt", "w");
        pNode = root;
        while(NULL != pNode) {
            fprintf(out, " %.2f", pNode->dRandom01); 
            if (NULL != pNode->pNext){
                fprintf(out,",");
            } 
            pNode = pNode->pNext;
        }
    } else if (startOption == 1){ //start from tail
        out = fopen("week9/llBackward.txt", "w");
        pNode = tail;
        while(NULL !=pNode) {
            fprintf(out, " %.2f", pNode->dRandom01); 
            if (NULL != pNode->pNext){
                printf(",");
            }
            pNode = pNode->pPrevious;
        }
    }
    fclose(out);
}


int main(int argc, char * argv[]){
    srand(time(0));
    PLLNODE root=NULL, tail, pNode; //allocated on the stack, local to main
    FILE *out; 
    enum {ROOT, TAIL} option;
    
    for (int i=0; i<NUM_NODES; i++){
        //add random node
        pNode = ranNodeGen();
        addNodeToTree(&root, pNode, &tail);
    }
    printList(root);
    printToFile(root, tail, ROOT, out);
    printToFile(root, tail, TAIL, out);
    clean(&root);
    return 0;
}