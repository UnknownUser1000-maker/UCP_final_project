#include <stdio.h>
#include "linkedlist.h"
#include <stdlib.h>

Llist* createLlist(void){
    Llist* list;
    list = (Llist*)malloc(sizeof(Llist));
    list->head = NULL;
    return list;
}
void insertStart(Llist* llist, void* entry){
    listNd* newNode = (listNd*)malloc(sizeof(listNd));
    newNode->data = entry;
    newNode->next = llist->head;
    llist->head = newNode;
    llist->size += 1;
}
void* removeStart(Llist* list){
    listNd* dummy = list->head;
    list->head= list->head->next;
    return dummy->data; /* going to be a void pointer as the data field of the list node struct is a void* */
}
void insertLast(Llist* llist, void* entry){
    listNd* curNode = llist->head;
    listNd* newNode = (listNd*)malloc(sizeof(listNd));
    while(curNode->next != NULL){
        curNode = curNode->next;
    }
    newNode->data = entry;
    curNode->next = newNode;
    newNode->next = NULL;
}
void* removeLast(Llist* llist){
    listNd* dummy;
    listNd* curNode = llist->head;
    listNd* secLast = llist->head;
    while(curNode->next != NULL){
        curNode = curNode->next;
    }
    while(secLast->next != curNode){
        secLast = secLast->next;
    }
    dummy = curNode;
    secLast->next = NULL;
    return dummy->data;
}
void printNd(void* data){
    int * intData;
    intData = (int*)data;
    printf("%d", *intData);
}
void printLlist(Llist* list, listFunc fptr){
    void* data;
    listNd* curNode= list->head;
    while(curNode!=NULL){
        data = curNode->data;
        (*fptr)(data);
        curNode = curNode->next;
    }
}
void freeNd(listNd* node){
    listNd* firstNode = node;
    while(node != NULL){
        node = node->next;
        free(node);
    }
    free(firstNode);
}
void freeLlist(Llist* list, listFunc fptr){
    (*fptr)(list->head);
    free(list);
}
/*
int main(){
    Llist* llist = createLlist();
    int*entry = (int*)malloc(sizeof(int)*2);
    entry[0]= 1;
    entry[1]= 2;
    entry = (void*)(entry);
    insertStart(llist, entry);
    printLlist(llist, &printNd);
    return 0;
}
*/


