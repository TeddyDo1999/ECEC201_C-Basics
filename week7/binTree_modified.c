
#include <stdio.h>
#include <stdlib.h>
#define NUM_NODES 10
#define TEXT_BUFFER 100


typedef struct 
{
    // user provided tag for each node and child. valid ID’s >=0
    int nodeID, leftChildID, rightChildID;
     // array index of my parent and children. -1 for empty
    int idxParent, idxLeftChild,idxRightChild;
} BinaryTreeNode;

void parseTexttoTree(FILE *btInputFile, char* temp, int num, int count_load,\
 int count_treebuild, int* inNumbers, BinaryTreeNode* bt) {
    /** INPUT PROCESS LOOP **/
    fscanf(btInputFile, "%s", &temp);
    for (int i=0; i <= TEXT_BUFFER;  i++){
        if (isdigit(temp[i])){
            if (temp[i-1] == '-'){
                num = -atoi(&temp[i]);
            }
            else{
                num = atoi(&temp[i]);
            }
            inNumbers[count_load] = num;
            count_load++;
        } 
    }

    for (int i=0; i<count_load; i++){
        if (0==i%3){
            bt[count_treebuild].nodeID =inNumbers[i];
        } else if (1==i%3){
            bt[count_treebuild].leftChildID = inNumbers[i];
        } else if (2==i%3) {
            bt[count_treebuild].rightChildID = inNumbers[i];
            count_treebuild++;
        }
    }

    /** LOOK UP AND LINK LOOP **/
    for (int i=0; i<count_treebuild; i++){
        // bt[i].idxLeftChild = bt[i].leftChildID;
        // bt[i].idxRightChild = bt[i].rightChildID;
        if (bt[i].leftChildID == -1){
            bt[i].idxLeftChild = -99;
        } 
        if (bt[i].rightChildID == -1) {
            bt[i].idxRightChild = -99;
        }
        for (int j=0; j<count_treebuild; j++){
            if (bt[i].nodeID == bt[j].leftChildID){
                bt[i].idxParent = j;
                bt[j].idxLeftChild = i;
            } else if  (bt[i].nodeID == bt[j].rightChildID) {
                bt[i].idxParent = j;
                bt[j].idxRightChild = i;
            } 
        }
    }
}




int main(int argc, char ** argv){
    
    //Check number of arguments 
    if (2 != argc) {
    printf("No file path was provided to be read from\n \
            USAGE: binTree <filename>");
    return -1;    
    }

    //Open and check if file path exists and valid
    FILE *btInputFile;
    btInputFile = fopen(argv[1], "r");
    if (btInputFile == NULL) {
        printf("Invalid file path!!!! \n \
        Please enter another file path");
        return -2;
    }

    /* INITIALIZATION */
    BinaryTreeNode bt[NUM_NODES] = {[0 ... NUM_NODES-1].nodeID=-1};    
    char temp[TEXT_BUFFER];
    int inNumbers[TEXT_BUFFER];
    int num, count_load=0, count_treebuild=0;
    //Another way to initialize:
    //  BinaryTreeNode bt[NUM_NODES];
    // for (int i=0; i<=NUM_NODES; i++) {
    //     bt[i].nodeID = -1;     
    // }

    parseTexttoTree(btInputFile, temp, num, count_load, count_treebuild, inNumbers, bt);
    
    close(btInputFile);

    /** OUTPUT LOOP **/
    for (int i=0; i<count_treebuild; i++){
        printf("nodeID(%d) -> leftChildID(%d), rightChildID(%d), ParentID(%d)\n", 
        bt[i].nodeID, bt[i].leftChildID, bt[i].rightChildID, bt[bt[i].idxParent].nodeID);    
        printf("nodeID(%d) -> leftChildIdx(%d), rightChildIdx(%d), ParentIdx(%d)\n\n", 
        bt[i].nodeID, bt[i].idxLeftChild, bt[i].idxRightChild, bt[i].idxParent);
    }
    return 0;
}
