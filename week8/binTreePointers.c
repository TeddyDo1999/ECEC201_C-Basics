#include <stdio.h>
#include <stdlib.h>
#define NUM_NODES 10
#define TEXT_BUFFER 100

/* 
Hanh Do Phung
Drexel University
11/16/2019

A full implement of a binary tree. Consists of:
--Initialization
--Text parsing and tree data loading
--Traversing and printing out nodes
*/

typedef struct _BTN
{
    // user provided tag for each node and child. valid ID’s >=0
    int nodeID, leftChildID, rightChildID;
     // array index of my parent and children. -1 for empty
    struct _BTN *btParent, *btLeftChild, *btRightChild;//tree pointers
} BinaryTreeNode;


/* readBinaryTree: function to read triplets of digits (1 char) from a csv file
then store them in a binaryTree data structure. The triplet (a,b,c) is read 
as a=nodeID, b=LeftChildID, c=RightChildID 
Arguments are: --bt: pointer to first node in node array,
               --btInputFile: csv file for parsing 
Returns number of nodes built in tree  */
int readBinaryTree(BinaryTreeNode* bt, FILE *btInputFile){
    char temp[TEXT_BUFFER]; //text array store each char comma separated 
    int inNumbers[TEXT_BUFFER]; //Array with all numbers read from text file
    int num, count_load=0, count_treebuild=0;
    
    fscanf(btInputFile, "%s", &temp);
    for (int i=0; i <= TEXT_BUFFER;  i++){
        if (isdigit(temp[i])){
            if (temp[i-1] == '-'){
                num = -atoi(&temp[i]); //negative num
            }
            else{
                num = atoi(&temp[i]);//positive num
            }
            inNumbers[count_load] = num;
            count_load++; //number of triplets from text file
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
    return count_treebuild; // count_treebuild is number of nodes in Tree
}


/* setTreePointers serves to link the nodes together in the binaryTree structure.
The array of nodes is traversed and the pointers to parent, left and right child 
nodes are set to appropriate nodes.
Arguments are: bt: pointer to 1st node of tree itself
               numNodes: number of nodes in node array
Returns pointer to root node */
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


/* Iterate through each node in node array and print to stdout its ID, 
parent, and children. 
Input: pointer to first node in node array, number of nodes in array*/
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


/* Takes pointer to root node as input, recursively print out its ID, parent 
and children. Root node is marked with a (*) mark and leaf node is marked with
a (+) mark */
int printTreeDFS(BinaryTreeNode* bt){
    char parent[5]="";
    char node[5]="";
    char leftChild[5]="", rightChild[2]="";
    int leftChildExist=1, rightChildExist;

    if (bt->btParent == NULL){
        sprintf(parent, "%s", "");
        sprintf(node, "%d *", bt->nodeID); 
    } else { 
        sprintf(parent, "%d", bt->btParent->nodeID);
        sprintf(node, "%d", bt->nodeID);  
    }

    if (bt->btLeftChild == NULL){
        leftChildExist = 0;
        if  (bt->btRightChild == NULL) { //no child at all
            rightChildExist = 0;
            sprintf(node, "%d +", bt->nodeID);
        } else { //right exists, left not
            rightChildExist = 1;
            if ((bt->btRightChild->btRightChild == NULL) && (bt->btRightChild->btLeftChild==NULL)){
                sprintf(rightChild, "%d +", bt->btRightChild->nodeID);//rightchild is leaf    
            } else {
                sprintf(rightChild, "%d", bt->btRightChild->nodeID);
            }
        } 
    } else {//left exists
        if ((bt->btLeftChild->btRightChild == NULL) && (bt->btLeftChild->btLeftChild==NULL)){
            sprintf(leftChild, "%d +", bt->btLeftChild->nodeID);//left child is leaf    
        } else {
            sprintf(leftChild, "%d", bt->btLeftChild->nodeID);
        }

        if  (bt->btRightChild == NULL) {//left exists, right not
            rightChildExist = 0; 
        } else { //both exist
            rightChildExist = 1;
            sprintf(rightChild, "%d", bt->btRightChild->nodeID);
        }
    }

    printf("(%s) -> (%s): (%s), (%s)\n", 
        parent, node, leftChild, rightChild);
    
    if (rightChildExist == 1){
        printTreeDFS(bt->btRightChild); //recursively go to left child
    }
    if (leftChildExist == 1){
        printTreeDFS(bt->btLeftChild); //recursively go to right child
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

    BinaryTreeNode bt[NUM_NODES] = {[0 ... NUM_NODES-1].nodeID=-1};    
    int numNodes = readBinaryTree(bt, btInputFile);
    BinaryTreeNode* root = setTreePointers(bt, numNodes);
    //printTreeArray(bt, numNodes);
    printTreeDFS(root);
    return 0;
}