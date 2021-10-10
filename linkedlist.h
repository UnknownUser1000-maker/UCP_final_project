#ifndef LINKEDLIST
#define LINKEDLIST
typedef struct listNd{
    void* data;
    struct listNd* next;
}listNd;
typedef struct{
    listNd* head;
    int size;
} Llist;
typedef void (*listFunc)(void* data);
Llist* createLlist(void);
void insertStart(Llist* llist, void* entry);
void* removeStart(Llist* list);
void insertLast(Llist* llist, void* entry);
void* removeLast(Llist* llist);
void printNd(void* data);
void printLlist(Llist* list, listFunc fptr);
void freeNd(void* data);
void freeLlist(Llist* list, listFunc fptr);
#endif


