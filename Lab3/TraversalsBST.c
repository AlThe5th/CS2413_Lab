#include<stdio.h>
#include<stdlib.h>

//Create the binary tree node structure
struct node{
    int data;
    struct node* left;
    struct node* right;
};

/*Recursive function that prints parent, 
visits Left child sub-tree, then visits Right child sub-tree
P -> L -> R */
void preorder(struct node *tree){
    if(tree != NULL){
        printf("%d  ", tree->data); //Base Case
        preorder(tree->left);       //Recursive Case 1
        preorder(tree->right);      //Recursive Case 2
    }
}

/*Recursive function that visits Left child sub-tree, 
prints parent, then visits Right child sub-tree
L -> P -> R */
void inorder(struct node *tree){
    if(tree != NULL){
        inorder(tree->left);        //Recursive Case 1
        printf("%d  ", tree->data); //Base Case
        inorder(tree->right);       //Recursive Case 2
    }
}

/*Recursive function that visits Left child sub-tree, 
visits Right child sub-tree, then prints parent
L -> R -> P */
void postorder(struct node *tree){
    if(tree != NULL){
        postorder(tree->left);      //Recursive Case 1
        postorder(tree->right);     //Recursive Case 2
        printf("%d  ", tree->data); //Base Case
    }
}

//Recursive function that inserts a new data into a BST
struct node *insert(struct node *tree, int newData){
    if(tree == NULL){               //Base Case: Checks if node is a leaf node
        struct node* newNode = (struct node*)malloc(sizeof(struct node));
        newNode->data = newData;
        newNode->left = NULL;
        newNode->right = NULL;
        
        return newNode;
    } else{                         //Recursive Case: If node has children
        if(newData < tree->data){   //If data less than parent node, go to left sub-tree
            tree->left = insert(tree->left, newData);
        } else{                     //If data greater than parent node, go to right sub-tree
            tree->right = insert(tree->right, newData);
        }
        return tree;
    }
}


int main(){
    //Initialize tree
    struct node *tree = NULL;

    tree = insert(tree, 5);
    int values1[] = {2,7,7,9,1,3,4,8,6};
    for (int i = 0; i < (sizeof(values1) / sizeof(values1[0])); i++){
        insert(tree, values1[i]);
    }
    
    //Print traversal orders
    printf("Traversals\n  Pre-Order: ");
    preorder(tree);
    printf("\n  In-Order: ");
    inorder(tree);
}
