
#include <stdio.h>
#include <stdlib.h>
#define NUM_NODES 10
#define TEXT_BUFFER 100


typedef struct _BTN
{
    // user provided tag for each node and child. valid ID’s >=0
    int nodeID, leftChildID, rightChildID;
     // array index of my parent and children. -1 for empty
    struct _BTN *btParent, *btLeftChild, *btRightChild;//tree pointers
} BinaryTreeNode;


int readBinaryTree(BinaryTreeNode* bt, FILE *btInputFile){
    char temp[TEXT_BUFFER];
    int inNumbers[TEXT_BUFFER];
    int num, count_load=0, count_treebuild=0;
    
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
            bt[count_treebuild].nodeID = inNumbers[i];
        } else if (1==i%3){
            bt[count_treebuild].leftChildID = inNumbers[i];
        } else if (2==i%3) {
            bt[count_treebuild].rightChildID = inNumbers[i];
            count_treebuild++;
        }
    }
    fclose(btInputFile);
    
    // for (int i=0; i<count_treebuild; i++){
    //     printf("nodeID(%d) -> leftChildID(%d), rightChildID(%d)\n", 
    //     bt[i].nodeID, bt[i].leftChildID, bt[i].rightChildID);    
    // }
    return count_treebuild;
}

BinaryTreeNode* setTreePointers(BinaryTreeNode* bt, int numNodes){
    int count_treebuild= numNodes;

    /** LOOK UP AND LINK LOOP **/
    for (int i=0; i<count_treebuild; i++){
        if (bt[i].leftChildID == -1){
            bt[i].btLeftChild = NULL;
        } 
        if (bt[i].rightChildID == -1) {
            bt[i].btRightChild = NULL;
        }
        for (int j=0; j<count_treebuild; j++){
            if (bt[i].nodeID == bt[j].leftChildID){
                bt[i].btParent = &bt[j];
                bt[j].btLeftChild = &bt[i];
            } else if  (bt[i].nodeID == bt[j].rightChildID) {
                bt[i].btParent = &bt[j];
                bt[j].btRightChild = &bt[i];
            } 
        }
    }

    for (int i=0; i<count_treebuild; i++){
        if (bt[i].btParent == NULL) {
            return &bt[i];
        }
    }

}

int printTreeArray(BinaryTreeNode* bt, int numNodes){
    printf("(%d): (%d), (%d)\n",
        bt[0].nodeID, bt[0].leftChildID, bt[0].rightChildID);
    for (int i=1; i<numNodes; i++){
        printf("(%d) -> (%d): (%d), (%d)\n", 
        bt[i].btParent->nodeID, bt[i].nodeID, bt[i].leftChildID, bt[i].rightChildID);
        // printf(" -> nodeID(%d): leftChildID(%d), rightChildID(%d)\n", 
        // bt[i].nodeID, bt[i].leftChildID, bt[i].rightChildID);

    }       
}

int printTreeDFS(BinaryTreeNode* bt){
    char parent[5];
    char node[5];
    int leftChildExist, rightChildExist;

    if (bt->btParent == NULL){
        sprintf(parent, "%d *", bt->btParent->nodeID); 
    } else { 
        sprintf(parent, "%d", bt->btParent->nodeID); 
    }

    if (bt->btLeftChild == NULL){
        leftChildExist = 0;
        if  (bt->btRightChild == NULL) {
            rightChildExist = 0;
            sprintf(node, "%d +", bt->nodeID);
        } else {
            rightChildExist = 1;
        } 
    } else {
        if  (bt->btRightChild == NULL) {
            sprintf(node, "%d", bt->nodeID);
            rightChildExist = 0; 
        } else {
            rightChildExist = 1;
        }
    }

    if (rightChildExist == 1){
        printTreeDFS(bt->btRightChild);
    }
    if (leftChildExist == 1){
        printTreeDFS(bt->btLeftChild);
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
    //ATTENTION: BT IS THE POINTER TO 1ST ELEMENT OF ARRAY. BT = &BT[0]
    BinaryTreeNode bt[NUM_NODES] = {[0 ... NUM_NODES-1].nodeID=-1};    
    
    

    // bt = InitNode(NUM_NODES);
    int numNodes = readBinaryTree(bt, btInputFile);
    BinaryTreeNode* root = setTreePointers(bt, numNodes);
    printTreeArray(bt, numNodes);
    printf("%d", root->nodeID);

    
    return 0;
}