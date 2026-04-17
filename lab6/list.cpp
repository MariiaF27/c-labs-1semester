#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "list.h"


List *list_new(){
        return (List *) calloc(1, sizeof(List));
}

void list_print(const List *list){
        Item *ptr = list->first;
        printf("'");
        while(ptr){
                printf("%c", ptr->symbol);
                ptr = ptr->next;
        }
        printf("'");
        printf("\n");
}

int list_put(List *list, char symbol){
        Item *ptr=(Item *) malloc(sizeof(Item));
        if(!ptr) return -1;

        ptr->symbol = symbol;
        ptr->next=NULL;
        ptr->prev=NULL;

        if(!list->first){
                list->first = ptr;
                list->last = ptr;
        }
        else{
                ptr->prev=list->last;
                list->last->next = ptr;
                list->last = ptr;
        }
        return 0;
}


int list_remove(Item *ptr, List *list){
        if(!ptr || !list) return -1;

        if(ptr==list->first){
                list->first = ptr->next;
                if(list->first){
                        list->first->prev=NULL;
                }
        }
        if(ptr == list->last){
                list->last = ptr->prev;
                if(list->last){
                        list->last->next=NULL;
                }
        }
        if(ptr->prev){
                ptr->prev->next=ptr->next;
        }
        if(ptr->next){
                ptr->next->prev=ptr->prev;
        }
        free(ptr);
        return 0;
}

int is_sep(const char letter){
        return (letter == ' ' || letter =='\t' || letter =='\n');
}

int process(List *list){

        Item *ptr=list->first;
        int count=0;
        char letter;
        if(!ptr){
                return -1;
        }
        while (ptr){
                letter=ptr->symbol;
                Item *next=ptr->next;

                if(!is_sep(letter) && count==0){
                        count = 1;
                } else if(is_sep(letter)){
                        if(!count){
                                list_remove(ptr, list);
                        }
                        count = 0;
                }
                ptr=next;
        }
        if(list->last && is_sep(list->last->symbol)){
                list_remove (list->last, list);
        }
        return 0;
}

void list_delete(List *list){
        Item *ptr = list->first;
        while(ptr){
                Item *next=ptr->next;
                free(ptr);
                ptr=next;
        }
        free(list);
}


void process2(List *list, int p){
        if(!list || !list->first) return;

        Item* head = list->first;
        Item* tail=NULL;
        Item* current = list->first;
        Item* prev_word_tail=NULL;
        int is_first_word=1;

        while (current){

                while(current && current->next && !is_sep(current->next->symbol) && current->next->symbol !='\n'){
                        current=current->next;
                }
                tail =current;
                current=current->next;

                tail->next=head;
                head->prev=tail;

                for(int count=0; count<p; count++){
                        head=head->prev;
                        tail=tail->prev;
                }
                tail->next=current;
                if(current){
                        current->prev=tail;
                }
                head->prev=prev_word_tail;

                if(is_first_word){
                        list->first=head;
                        is_first_word=0;
                }

                if(prev_word_tail){
                        prev_word_tail->next=head;
                }

                prev_word_tail=tail;

                while(current && is_sep(current->symbol)){

                        prev_word_tail=current;

                        current=current->next;
                }
                head=current; //обновление начала следующего слова
        }
        list->last=prev_word_tail;
}