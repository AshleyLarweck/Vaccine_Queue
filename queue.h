/************************************************************************
Queue.h

Purpose:
    Define constants used in the project
    Struct definitions for a Queue.
    Define function prototypes used by Queues.
************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//#define constant values
#define TRUE 1
#define FALSE 0


//typedef for the Patient struct which contains three integers: an ID number, arrival time, and whether they checked in electronically (TRUE or FALSE).
typedef struct
{
    int patientID;
	int arrivalTime;
	int eCheckIn;
} Patient;


//Typedef so that the Element that we will use in the Queue is the Patient struct.
typedef Patient Element;

//Typedef for a node a linked list.
typedef struct NodeLL
{
    Element element;
    struct NodeLL *next;
} NodeLL;

//Typedef for a queue implementation.  
//Contains a pointer to the first node in the list and the last node in the list (head and foot respectively).
typedef struct
{
    NodeLL *head;
    NodeLL *foot;
} QueueImp;

typedef QueueImp *Queue;


/*****Prototypes*******/

//Malloc a new QueueImp, set the head and foot pointers to NULL, and return it's address.
Queue newQueue();


//Free each node that remains in the Queue and then free q itself.
void freeQueue(Queue q);


//Allocate a new node and store "value" as the Element in the node.  Return the address of the node. 
NodeLL *allocateNode(Element value);


//Call allocateNode() to get a new node that contains "value" and append it to the "foot end" of the queue.  Make sure to consider "edge cases" (e.g., when the queue is currently empty).
void enqueue(Queue q, Element value);


//Remove the node at the "head" end of the queue, and return the value of the element stored in this node through an element e that is passed by reference.
//Functionally return TRUE (1) if the dequeue was successful and return FALSE (0) if it was not successful (i.e., the queue was empty).
//Remember to consider any "edge cases" (e.g., when the queue becomes empty after this dequeue).
int dequeue(Queue q, Element *e);


//Return the value of the element stored in the first node of the queue without removing the node itself (similar to topElement() for Stacks).
//Return the value through e that is passed by reference, and return TRUE (1) if the call was successful and return FALSE (0) if it was not successful (i.e., the queue was empty).
int frontElement(Queue q, Element *e);


//Return TRUE (1) if the queue is empty, otherwise return FALSE (0).
int isEmpty(Queue q);
