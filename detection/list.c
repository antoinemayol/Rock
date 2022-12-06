#include <stdlib.h>
#include "list.h"
#include <stdio.h>
#include <stddef.h>


void free_all(struct list* l)
{
    struct list* tmp = l;
    struct list* tmp2 = l->next;
    while(tmp != NULL)
    {
        free(tmp);
        tmp = tmp2;
        if(tmp != NULL)
            tmp2 = tmp->next;
    }
}

void list_init(struct list *list)
{
   list->next = NULL;
   list->data = 0;
}

int list_is_empty(struct list *list)
{
    return list->next == NULL;
}

size_t list_len(struct list *list)
{
    size_t len = 0;
    struct list *tmp = list->next;
    while(tmp != NULL)
    {
        len++;
        tmp = tmp->next;
    }
    return len;
}

void list_push_front(struct list *list, struct list *elm)
{
    elm->next = list->next;
    list->next = elm;
}

struct list *list_pop_front(struct list *list)
{
    struct list* res = list->next;
    if(list->next != NULL)
    {
        list->next = res->next;
        res->next = NULL;
    }
    return res;
}

struct list *list_find(struct list *list, int value)
{
    struct list* res = list->next;
    while(res != NULL && res->data != value)
        res = res->next;
    return res;
}

struct list *list_lower_bound(struct list *list, int value)
{
    struct list* res = list;
    while(res->next != NULL && res->data <= value)
        res = res->next;
    return res;
}

int list_is_sorted(struct list *list)
{
    int sorted = 1;
    struct list* tmp = list;
    while(tmp->next != NULL && sorted)
    {
        sorted = tmp->data <= (tmp->next)->data;
        tmp = tmp->next;
    }
    return sorted;
}

void list_insert(struct list *list, struct list *elm)
{
    struct list* tmp = list;
    while(tmp->next != NULL && elm->data > (tmp->next)->data)
        tmp = tmp->next;
    elm->next = tmp->next;
    tmp->next = elm;
}

void list_rev(struct list *list)
{
    struct list* tmp = list->next;
    while(tmp->next != NULL)
    {
        struct list* nxt = list->next;
        list->next = tmp->next;
        tmp->next = (list->next)->next;
        (list->next)->next = nxt;
    }
}

void list_half_split(struct list *list, struct list *second)
{
    struct list* tmp = list->next;
    struct list* half = list;
    size_t len = 0;
    while(tmp != NULL)
    {
        if(len%2==0)
            half = half->next;
        len++;
        tmp = tmp->next;
    }
    second->next = half->next;
    half->next= NULL;
}

