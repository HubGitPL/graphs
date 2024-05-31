//
// Created by Mateusz on 23/03/2024.
//
//
#pragma once
#pragma warning(disable:4996)
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#ifndef VECTOR_MYLIST_H
#define VECTOR_MYLIST_H

#include <stdlib.h>
#include <cstdio>
struct ListNode;

typedef struct ListNode{
    void *value;
    struct ListNode *next;
    struct ListNode *prev;
} ListNode;

typedef struct List{
    int counter;
    ListNode *first;
    ListNode *last;
} List;

List *createList();
int sizeList(List *list);
void deleteList(List *list);
void clearList(List *list);
void destroyClearList(List *list);
void deleteListNode(ListNode *node);
void *removeFromList(List *list, ListNode *node);
long long int getElement(List *list, int index);
void* getElementVoid(List *list, int index);
char* getLastElement(List *list);

void pushFront(List *list, void *value);
void *popFront(List *list);
void pushBack(List *list, void *value);
void *popBack(List *list);
int findInList(List *list, void *value);

void printList(List *list);

#endif //VECTOR_MYLIST_H