#include <stdio.h>
#include<stdlib.h>

//Creaing binary tree node structure
struct node{
	int data;
	struct node *left;
	struct node *right;
};

//Function to insert node into a binary tree (no sorting)
struct node* insert(struct node* tree, int newData){
    //Make a new node with the new data
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = newData;
    newNode->left = NULL;
    newNode->right = NULL;

    //Return new node as root if tree is empty
    if (tree == NULL)
        return newNode;


    //Initialize queue for level-order insertion
    struct node* queue[25];
    int front = 0, rear = 0;

    queue[rear++] = tree;

    //BFS traversal to find insertion point
    while(front < rear){
        struct node* temp = queue[front++];

        if(temp->left == NULL){     //If the left child is NULL, insert there
            temp->left = newNode;
            return tree;
        } else                      //Else, enqueue left child to be checked later
            queue[rear++] = temp->left;

        
        if(temp->right == NULL){    //If the right child is NULL, insert there
            temp->right = newNode;
            return tree;
        } else                      //Else, enqueue right child to be checked later
            queue[rear++] = temp->right;
    }
    return tree;
}

//Function to recersively check binary tree symmetry 
int isSymmetric(struct node* left, struct node* right){
	if(left == NULL && right == NULL)   //Symmetric if children are both empty
		return 1;
    if(left == NULL || right == NULL)   //Non-symmetric if only 1 child is empty
		return 0;
    if(left->data != right->data)       //Non-symmetric if children's data does not match
		return 0;
	

    //Recursively check mirroring of left's left w/ right's right, and left's right w/ right's left
	return isSymmetric(left->left, right->right) && isSymmetric(left->right, right->left);
}


int main(){
    //Initialize tree
    struct node *tree = NULL;

    tree = insert(tree, 1);
    int values1[] = {2,2,3,4,4,3};
    for (int i = 0; i < (sizeof(values1) / sizeof(values1[0])); i++)
        insert(tree, values1[i]);
    

    //Determine symmetry
	if(isSymmetric(tree->left, tree->right) == 1)
		printf("True, tree is symmetric");
	else
        printf("False, tree is not symmetric");
   
}
