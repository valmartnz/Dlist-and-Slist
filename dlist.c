#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "dlist.h"

dnode* dnode_create(int data, dnode* prev, dnode* next) {
  dnode* p = (dnode*)malloc(sizeof(dnode));
  p->data = data;
  p->next = next;
  p->prev = prev;
  return p;
}
dlist* dlist_create(void) {
  dlist* p = (dlist*)malloc(sizeof(dlist));
  p->head = NULL;
  p->tail = NULL;
  p->size = 0;
  return p;
}

bool dlist_empty(dlist* list) { return list->size == 0; }
size_t dlist_size(dlist* list) { return list->size; }

void dlist_popfront(dlist* list) {
  if(dlist_empty(list)) { fprintf(stderr, "list is empty\n"); exit(1); }

  dnode* p = list->head;
  list->head = list->head->next;
  if(list->size != 1) { list->head->prev = NULL; }
  free(p);
  --list->size;
}
void dlist_popback(dlist* list) {
  if(dlist_empty(list)) { fprintf(stderr, "list is empty\n"); exit(1); }
  if(list->size == 1) { dlist_popfront(list); return; }

  dnode* prev = list->tail->prev;
  prev->next = NULL;
  free(list->tail);
  list->tail = prev;
  --list->size;
}

void dlist_pushfront(dlist* list, int data) {
  dnode* p = dnode_create(data, NULL, list->head);
  if(list->size != 0) { list->head->prev = p; }
  list->head = p;
  if(list->size == 0) {
    list->tail = p;
    list->tail->prev = p;
  }
  ++list->size;
}
void dlist_pushback(dlist* list, int data) {
  if(list->size == 0) { dlist_pushfront(list, data); return; }

  dnode* p = dnode_create(data, list->tail, NULL);
  list->tail->next = p;
  list->tail = p;
  ++list->size;
}

void dlist_clear(dlist* list) {
  while(!dlist_empty(list)) {
    dlist_popfront(list);
  }
}
void dlist_print(dlist* list, const char* msg) {
  printf("%s\n", msg);
  if(dlist_empty(list)) { printf("list is empty\n"); return; }

  dnode* p = list->head;
  while(p != NULL) {
    printf("%11p <-- %d (%p) --> %p\n", p->prev, p->data, p, p->next);
    p = p->next;
  }
}

int dlist_front(dlist* list) {
  if(dlist_empty(list)) { fprintf(stderr, "list is empty\n"); exit(1); }
  return list->head->data;
}
int dlist_back(dlist* list) {
  if(dlist_empty(list)) { fprintf(stderr, "list is empty\n"); exit(1); }
  return list->tail->data;
}
