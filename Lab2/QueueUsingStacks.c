#include<stdio.h>
#include<stdlib.h>

//Creating single node structure
struct node{
    int data;
    struct node* next;
};

//Creating single stack structure
struct stack{
    struct node* top;
};

//Creating queue structure with two stacks
struct queue{
    struct stack* stack2;   //Front - dequeue
    struct stack* stack1;   //Rear - enqueue
};

//Function to insert new top node in the stack
void push(struct stack** stack, int newData){
    struct node* newNode = (struct node*)malloc(sizeof(struct node));   //Allocating memory for node

    newNode->data = newData;        //Giving new node data

    newNode->next = (*stack)->top;  //Making new node the new top
    (*stack)->top = newNode;

    return;
}

//Function to delete the top node in the stack
int pop(struct stack** stack){
    if((*stack)->top == NULL){                  //Exiting function if stack empty
        return -1;
    } else{                                     //Deleting top element
        struct node* temp = (*stack)->top;
        int popData = temp->data;
        (*stack)->top = ((*stack)->top)->next;
        free(temp);

        return popData;                         //Returning deleted element data
    }
}

//Function to simulate enqueue (push into stack1 directly)
void enqueue(struct queue* Queue, int newData){
    push(&(Queue->stack1), newData);    //Enqueuing data with push
    return;
}

//Function to simulate dequeue (pop from stack2)
int dequeue(struct queue* Queue){
    if((Queue->stack1)->top == NULL && (Queue->stack2)->top == NULL){   //Exit if queue is empty
        return -1;
    }

    if ((Queue->stack2)->top == NULL) {                               //If stack2 empty, move elements from stack1 to stack2
        while ((Queue->stack1)->top != NULL) {
            push(&(Queue->stack2), pop(&(Queue->stack1)));          //Push top of stack1 to dequeuing stack2
        }
    }

    return pop(&(Queue->stack2));                                   //Pop from stack2 (front of queue)
}


//Funciton to print elements in queue order
void print(struct queue* Queue){
    struct node* current = Queue->stack2->top;  

    while(current != NULL){                 //If elements in stack2, print normal way
        printf("%d ", current->data);
        current = current->next;
    }

    struct stack* tempStack = (struct stack*)malloc(sizeof(struct stack));
    tempStack->top = NULL;
    current = (Queue->stack1)->top;
    while(current != NULL){                 //If elements in stack1, prepare reverse linked list
        push(&tempStack, current->data);
        current = current->next;
    }
    while (tempStack->top != NULL){         //Print new reversed stack 
        printf("%d ", pop(&tempStack));
    }

    printf("\n");
    free(tempStack);

    return;
}


void main() {
    //Initialize Queue (with its two stacks)
    struct queue *Queue = (struct queue *)malloc(sizeof(struct queue));
    Queue->stack1 = (struct stack *)malloc(sizeof(struct stack));
    Queue->stack2 = (struct stack *)malloc(sizeof(struct stack));
    Queue->stack1->top = NULL;
    Queue->stack2->top = NULL;

    //Enqueue values into the queue
    int values[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < (sizeof(values) / sizeof(values[0])); i++) {
        enqueue(Queue, values[i]);
    }

    print(Queue);           //Print queue elements in proper FIFO order

    dequeue(Queue);         //Perform some dequeuing
    dequeue(Queue);
    dequeue(Queue);

    print(Queue);

    enqueue(Queue, 6);      //Enqueue new values
    enqueue(Queue, 7);
    enqueue(Queue, 8);

    print(Queue);
}
