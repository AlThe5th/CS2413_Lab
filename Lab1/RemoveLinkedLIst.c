#include<stdio.h>
#include<stdlib.h>

//Creating single node structure
struct Node{
    int data;           //1st part
    struct Node *next;  //2nd Part
};

//Function to add a node to a Linked List
void append(struct Node** head, int newData){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));   //Allocating memory for node

    newNode->data = newData;        //Giving new node data
    newNode->next = NULL;           //Linked new node to nothing

    if(*head == NULL){              //Making new node the head (if head empty)
        *head = newNode;
        return;
    } else{                         //Adding new node to the end (if head not empty)
        struct Node* last = *head;
        while(last->next != NULL){
            last = last->next;
        }
        last->next = newNode;
        return;
    }
}

//Function to print a Linked List
void print(struct Node* current){
    while (current != NULL) {           //Interating through the list
        printf(" %d ", current->data); 
        current = current->next;
    }
    printf("\n");
    return;
}

//Function to delete all instances of target data value
void deleteTarget(struct Node** head, int targetVal){
    if(*head == NULL){              //Exiting function if list empty
        return;
    }
   
    struct Node* current = *head;           //Initialize current also point at beginning 
    struct Node* prev = NULL;               //Initialize prev link to nothing

    while(current != NULL){                 //Interating through the list
        if (current->data != targetVal){    //Moving from node to next node (if current node does not have value)
            prev = current;
            current = current->next;
        } else {                            //Deleting node (if current node has value)
            prev->next = current->next;
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    return;
}

int main(){
    //Initialize Linked List
    struct Node* head = NULL;
    int values[] = {1,2,6,3,4,5,6};

    for(int i = 0; i < (sizeof(values)/sizeof(values[0])); i++){
        append(&head, values[i]);
    }
    print(head);

    //Delete all instances of a given value
    deleteTarget(&head, 6);
    print(head);

    return 0;
}
