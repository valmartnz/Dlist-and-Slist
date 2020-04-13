//
//  dlist_test.c
//  linked_list
//
//  Created by William McCarthy on 094//20.
//  Copyright © 2020 William McCarthy. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "dlist.h"
#include "utils.h"

//-------------------------------------------------
static void dlist_check_frontback(dlist* list, int front, int back) {
  printf("assert front of list is: %d\n", front);
  assert(dlist_front(list) == front);
  printf("assert back of list is: %d\n", back);
  assert(dlist_back(list) == back);
}

//-------------------------------------------------
static void dlist_test_once(dlist* list, int start, int end, int step, void (*fp)(dlist*, int)) {
  for (int i = start; i < end; i += step) {
    fp(list, i);
  }
  dlist_print(list, "list is created and is...");
  printf("list size is: %zu\n", dlist_size(list));
  printf("list is empty? %s\n", yesorno(dlist_empty(list)));

  int firstadded = start;
  int lastadded = start;
  while (lastadded + step < end) {
    lastadded += step;
  }
  if (fp == dlist_pushback)  { dlist_check_frontback(list, firstadded, lastadded);  }
  if (fp == dlist_pushfront) { dlist_check_frontback(list, lastadded, firstadded ); }

  dlist_clear(list);
  printf("after clearing the list, is the list is now empty? %s\n\n", yesorno(dlist_empty(list)));
}

//-------------------------------------------------
void dlist_test() {
  printf("//===================== TESTING DLIST =========================\n\n");
  dlist* list = dlist_create();
  dlist_test_once(list, 10, 50, 10, dlist_pushfront);
  dlist_test_once(list, 10, 100, 20, dlist_pushback);
  dlist_test_once(list, 0, 100, 1, dlist_pushback);

  printf("      All Assertions passed!...\n");
  free(list);
  printf("//===================== END TESTING DLIST =========================\n\n");
}

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