#include "linked.h"
#include<stdlib.h>
#include<stdio.h>

/*Linked List implementation*/
LINKEDLIST * createLinkedList() {
    LINKEDLIST * list = (LINKEDLIST *) malloc(sizeof(LINKEDLIST));
    list->head = NULL;
    list->tail = NULL;
    return list;
}


void insertLast(LINKEDLIST * list, void * newData) {

    NODE * newNode =  (NODE *) malloc(sizeof(NODE));
    newNode->data = newData;
    newNode->next = NULL;

    if(list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }

    
}

void removeLast(LINKEDLIST * list, void(*freeData)(void *)) {
    NODE* current;
    if(list->head == NULL) {
        return;
    }

    if(list->head->next == NULL) {
        freeData(list->head->data);
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        return;
    }

    current = list -> head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    freeData(current->next->data);
    free(current->next);
    current->next = NULL;
    list->tail = current;
}



void freeList(LINKEDLIST * list,  void(*fp)(void *)  ) {
    NODE * current = list ->head;
    NODE * nextNode;

    while(current != NULL) {
        nextNode = current->next;
        (*fp)(current->data); /* do the printing */
        free(current);
        current = nextNode;
    }
    list->head = NULL;
    list->tail = NULL;
    
}



void freePosition(void *data) {
    free((Position *)data);
}