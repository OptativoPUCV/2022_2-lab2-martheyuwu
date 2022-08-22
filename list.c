#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List *lista;
    lista=(List *)calloc(1,sizeof(List));
    lista->head=NULL;
    lista->tail=NULL;
    return lista;
}

void * firstList(List * list) {
    if (!list->head)
      return NULL;
    list->current=list->head;
    return list->head->data;
}

void * nextList(List * list) {
    if (!list->current)
      return NULL;
    list->current=list->current->next;
    if (!list->current)
      return NULL;
    return list->current->data;
}

void * lastList(List * list) {
    if (!list->tail)
      return NULL;
    list->current=list->tail;
    return list->current->data;
}

void * prevList(List * list) {
    if (!list->current)
      return NULL;
    if (!list->current->prev)
      return NULL;
    list->current=list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node *nodo=createNode(data);
    if (list->head){
      nodo->next=list->head;
      list->head->prev=nodo;
      list->head=nodo;
    }
    else{
      list->head=list->tail=nodo;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node *nodo=createNode(data);
    if (list->head){
      nodo->prev=list->current;
      if (!list->current->next){
        list->tail=nodo;
        list->current->next=list->tail;
      }
      else{
        list->current->next=nodo;
      }
    }
    else{
      list->head=list->tail=nodo;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) { 
    Node *curr=list->current;  
    Node *last=list->current->prev;     
    Node *next=list->current->next;     
    void *data=list->current->data;
    if (list->current){
      if (list->current==list->head){
        list->current=next;
        list->head=next;      
        list->current->prev=NULL; 
      }
      else if (list->current==list->tail){
        list->current=NULL;
        list->tail=last;      
      }
      else {
        list->current=next;
        if (next) 
          next->prev=last; 
      }
      free(curr);
      return data;
  }
  else{
    return NULL;
  }
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}