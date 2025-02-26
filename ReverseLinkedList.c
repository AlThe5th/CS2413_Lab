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
    newNode->next = NULL;           //New node is linked to nothing

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

//Function to reverse order of Linked List elements
void reverseList(struct Node** head){
    struct Node* current = *head;   //Initializing current also point to head
    struct Node* prev = NULL;       //Initializing prev link to nothing
    struct Node* next = NULL;       //Initializing next link to nothing

    while(current != NULL){         //Interating through Linked List elements
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

int main(){
    //Initialize Linked List
    struct Node* head = NULL;
    int values[] = {1,2,6,3,4,5,6};

    for(int i = 0; i < (sizeof(values)/sizeof(values[0])); i++){
        append(&head, values[i]);
    }
    print(head);

    //Reverse Linked List
    reverseList(&head);
    print(head);

    return 0;
}
