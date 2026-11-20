#include <stdio.h>
#include <stdlib.h>

typedef struct Linked_List {
    int data;
    struct Linked_List *next;
} Linked_List;

void free_linked_list(Linked_List *Head);

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 6};
    int n = 6;
    Linked_List* Head = (Linked_List*) malloc(sizeof(*Head));
    if (!Head) exit(1);

    (*Head).data = arr[0];
    (*Head).next = NULL;

    Linked_List* Temp = Head;
    for (int i = 1; i < n; i++) {
        Linked_List* Elem = (Linked_List*) malloc(sizeof(*Elem));
        (*Temp).next = Elem;
        (*Elem).data = arr[i];
        Temp = Elem;
    }

    free_linked_list(Head);
    return 0;
}

void free_linked_list(Linked_List *Head) {
    Linked_List *Temp;
    while (Head != NULL) {
        Temp = Head;
        Head = (*Head).next;
        printf("%d ", (*Temp).data);
        free(Temp);
    }
}
