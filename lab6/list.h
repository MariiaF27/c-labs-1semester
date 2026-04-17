#ifndef LIST_H
#define LIST_H

typedef struct Item {
    char symbol;
    struct Item *next;
    struct Item *prev;
} Item;

typedef struct List {
    Item *first;
    Item *last;
} List;

List *list_new();
void list_print(const List *list);
int process(List *list);
int list_put(List *list, char symbol);
void list_delete(List *list);
void process2(List *list, int N);

#endif