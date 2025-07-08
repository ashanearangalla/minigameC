#ifndef LINKED_H
#define LINKED_H

typedef struct node {
    void *        data;
    struct node * next;
}NODE;

typedef struct {
    NODE * head;
    NODE * tail;
}LINKEDLIST;

typedef struct {
    int row;
    int col;
} Position;



LINKEDLIST * createLinkedList();

void insertLast();
void removeLast();
void freePosition();
void freeList();



#endif