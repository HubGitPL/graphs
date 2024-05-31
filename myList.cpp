//
// Created by Mateusz on 23/03/2024.
//
#pragma once
#pragma warning(disable:4996)
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "myList.h"
List *createList(){
    //returns a void* pointer

    return (List*)calloc(1, sizeof(List));
}
int sizeList(List *list){
    return list->counter;
}
void deleteList(List *list){
    free(list->first);
    free(list->last);
    free(list);
}
void clearList(List *list){
    ListNode *current = list->first;
    while(current != nullptr){
        ListNode *next = current->next;
        free(current);
        current = next;
    }
    list->first = nullptr;
    list->last = nullptr;
    list->counter = 0;
}
void destroyClearList(List *list){
    clearList(list);
    deleteList(list);
}
void deleteListNode(ListNode *node){
    free(node);
}
void *removeFromList(List *list, ListNode *node){
    void *result = nullptr;

    if(list->first == nullptr || list->last == nullptr
       || node == nullptr){
        return nullptr;
    }
    if(node == list->first && node == list->last){
        list->first = nullptr;
        list->last = nullptr;
    } else if(node == list->first){
        list->first = node->next;
        list->first->prev = nullptr;
    } else if(node == list->last){
        list->last = node->prev;
        list->last->next = nullptr;
    } else {
        ListNode *after = node->next;
        ListNode *before = node->prev;
        after->prev = before;
        before->next = after;
    }
    list->counter--;
    result = node->value;
    free(node);

    return result;

}
long long int getElement(List *list, int index){
    ListNode *node = list->first;
    for(int i=0;i<index;i++){
        if(node == nullptr){
            return -1;
        }
        node = node->next;
    }
    return (long long int)(node->value);
}

void* getElementVoid(List *list, int index){
    ListNode *node = list->first;
    for(int i=0;i<index;i++){
        if(node == nullptr){
            return nullptr;
        }
        node = node->next;
    }
    return (void*)(node->value);
}
char* getLastElement(List *list){
    return (char*)(list->last->value);
}

void pushFront(List *list, void *value){
    ListNode *node = (ListNode*)calloc(1, sizeof(ListNode));

    node->value = value;

    if(list->first == nullptr){
        list->first = node;
        list->last = node;
    } else {
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }

    list->counter++;
    return;
}
void *popFront(List *list){
    ListNode *node = list->first;
    return node != nullptr ? removeFromList(list, node) : nullptr;
}
void pushBack(List *list, void *value){
    ListNode *node = (ListNode*)calloc(1, sizeof(ListNode));
    node->value = value;
    if(list->last == nullptr){
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }
    list->counter++;
    return;
}
void *popBack(List *list){
    ListNode *node = list->last;
    return node != nullptr ? removeFromList(list, node) : nullptr;
}

int findIndex(List* list, void* value) {
    ListNode* node = list->first;
    int index = 0;
    while(node != NULL) {
        if(node->value == value) {
            return index;
        }
        node = node->next;
        index++;
    }
    return -1; // Zwraca -1, jeśli wartość nie jest na liście
}

void printList(List *list){
    ListNode *node = list->first;
    while(node != nullptr){
        printf("%s ", (char*)node->value);
        node = node->next;
    }
}

