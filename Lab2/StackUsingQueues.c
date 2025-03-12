#include <stdio.h>
#include <stdlib.h>

//Creating a single queue node structure
struct node{
    int data;
    struct node* next;
};

//Creating single queue structure
struct queue{
    struct node* front;
    struct node* rear;
};

//Creating stack structure with two queues
struct stack{
    struct queue* queue1;  //Active queue for push
    struct queue* queue2;  //Temporary queue for pop
};

//Function to insert a new rear node in the queue (enqueue)
void enqueue(struct queue** queue, int newData){
    struct node* newNode = (struct node*)malloc(sizeof(struct node));   //Allocate memory for node
    newNode->data = newData;
    newNode->next = NULL;

    if((*queue)->rear == NULL){             //If queue is empty, update front as well
        (*queue)->front = newNode;
        (*queue)->rear = newNode;
        return;
    }

    ((*queue)->rear)->next = newNode;      //Enqueue new node at rear
    (*queue)->rear = newNode;
}

//Function to delete the front node in the queue (dequeue)
int dequeue(struct queue** queue){
    if((*queue)->front == NULL){                    //Exiting function if queue is empty
        return -1;
    } else{                                         //Deleting element at front
        struct node* temp = (*queue)->front;
        int dequeuedData = temp->data;
        (*queue)->front = ((*queue)->front)->next;

        if((*queue)->front == NULL){                //If queue becomes empty, update rear
            (*queue)->rear = NULL;
        }
        free(temp);

        return dequeuedData;                        //Returning deleted element data
    }
}

//Function to simulate pushing an element onto the stack
void push(struct stack* Stack, int data){
    enqueue(&(Stack->queue1), data); // Always enqueue to queue1
}

//Function to simulate popping the top element from the stack
int pop(struct stack* Stack){
    if((Stack->queue1)->front == NULL){                         //Exiting if stack empty
        return -1;
    }

    while(((Stack->queue1)->front)->next != NULL){              //Moving all elements except the last one from queue1 to queue2
        enqueue(&(Stack->queue2), dequeue(&(Stack->queue1)));
    }

    int poppedData = dequeue(&(Stack->queue1));                 //Removing the last element ("top" of the stack)

    struct queue* temp = Stack->queue1;                         //Swap queue1 and queue2 to maintain the correct order
    Stack->queue1 = Stack->queue2;
    Stack->queue2 = temp;

    return poppedData;                                          //Returning popped data
}

//Function to print stack elements (top to bottom order)
void print(struct stack* Stack){
    struct node* prev = NULL;
    struct node* current = (Stack->queue1)->front;
    struct node* next = NULL;

    while(current != NULL){         //Reversing the linked list
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    printf("\n");                   //Printing elements
    struct node* temp = prev;       //prev now points to the top element
    while(temp != NULL){
        printf("| %d |\n", temp->data);
        temp = temp->next;
    }
    printf("-----\n");

    current = prev;                 //Restoring original order by reversing again
    prev = NULL;
    while(current != NULL){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    Stack->queue1->front = prev;    //Restoring original front
}


void main(){
    //Initialize Stack (and its 2 queues)
    struct stack* Stack = (struct stack*)malloc(sizeof(struct stack));
    Stack->queue1 = (struct queue*)malloc(sizeof(struct queue));
    Stack->queue2 = (struct queue*)malloc(sizeof(struct queue));
    Stack->queue1->front = Stack->queue1->rear = NULL;
    Stack->queue2->front = Stack->queue2->rear = NULL;

    //Pushing elements onto the stack
    int values[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < (sizeof(values) / sizeof(values[0])); i++) {
        push(Stack, values[i]);
    }

    print(Stack);       //Printing stack elements in proper LIFO order

    pop(Stack);         //Popping top elements
    pop(Stack);
    pop(Stack);

    print(Stack);

    push(Stack, 6);     //Pushing more elements
    push(Stack, 7);
    push(Stack, 8);

    print(Stack);

    return;
}
