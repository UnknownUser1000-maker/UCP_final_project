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
    list->size -= 1; /* going to be a void pointer as the data field of the list node struct is a void* */
    return dummy->data;
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
void freeNd(void* data){
    free(data);
    data = NULL;
}
void freeLlist(Llist* list, listFunc fptr){
    listNd* curr = list->head;
    listNd* temp;
    while(curr){
        /*point the temp to next to avoid leak*/
        temp = curr->next;
        /* clean the data of curr*/
        (*fptr)(curr->data);
        curr->data = NULL;
        curr->next = NULL;
        free(curr);
        /*set the current to the temp which its the next node*/
        curr = temp;
        
    }
    free(list);
}
/*
int main(){
    Llist* llist = createLlist();
    int*entry = (int*)malloc(sizeof(int)*2);
    int*entry1 = (int*)malloc(sizeof(int)*2);
    int*entry2 = (int*)malloc(sizeof(int)*2);
    int*entry3 = (int*)malloc(sizeof(int)*2);
    listNd* node;
    entry3[0]= 1;
    entry3[1]= 2; 
    entry3 = (void*)(entry3);
    insertStart(llist, entry3);
    entry[0] = 12;
    entry[1] = 13;
    insertStart(llist, entry);
    entry1 = (int*)llist->head->data;
    printf("%d %d", entry1[0], entry1[1]);
    removeStart(llist);
    entry2 = (int*)llist->head->data;
    printf("%d %d", entry2[0], entry2[1]);
    return 0;
}
*/

