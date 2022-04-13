#include "Queue.h"
#include <stdlib.h>

Queue newQueue(){
    Queue queue= (Queue) malloc(sizeof(QueueImp));
    queue->head = NULL;
    queue->foot = NULL;
    return queue;
};

void freeQueue(Queue q){
    NodeLL *temp = q->head;
    while(temp!=NULL){
        NodeLL *temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
    q->head = NULL;
    q->foot = NULL;
}

NodeLL *allocateNode(Element value){
    NodeLL * node = (NodeLL*) malloc(sizeof(NodeLL));
    node->next = NULL;
    node->element = value;
    return node;
}

void enqueue(Queue q, Element value){
    NodeLL *node = allocateNode(value);
    if(isEmpty(q)){
        q->head = node;
        q->foot = node;
    }
    else{
        q->foot->next = node;
        q->foot = q->foot->next;
    }
}

int dequeue(Queue q, Element *e){
    if(isEmpty(q))
        return FALSE;
    NodeLL * node = q->head;
    if(q->head == q->foot){
        q->head = NULL;
        q->foot = NULL;
    }
    else{
        q->head = q->head->next;
    }
    *e =  node->element;
    free(node);
    return TRUE;
}

int frontElement(Queue q, Element *e){
    if(isEmpty(q)){
        return FALSE;
    }
    *e = q->head->element;
    return TRUE;
}

int isEmpty(Queue q){
    return q->head == NULL;
}