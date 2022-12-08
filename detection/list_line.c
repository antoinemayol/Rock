#include <stdlib.h>
#include "list_line.h"
#include <stdio.h>
#include <stddef.h>


void free_alll(struct listl* l)
{
    struct listl* tmp = l;
    struct listl* tmp2 = l->next;
    while(tmp != NULL)
    {
        free(tmp);
        tmp = tmp2;
        if(tmp != NULL)
            tmp2 = tmp->next;
    }
}
size_t listl_len(struct listl *list)
{
    size_t len = 0;
    struct listl *tmp = list->next;
    while(tmp != NULL)
    {
        len++;
        tmp = tmp->next;
    }
    return len;
}

int average_diff(struct listl* l)
{
    int diff = 0;
    struct listl* tmp = l->next;
    while(tmp->next)
    {
        diff += tmp->next->data->distance - tmp->data->distance;
        tmp = tmp->next;
    }
    return diff/(int) listl_len(l) - 1;
}
void listl_init(struct listl *list)
{
   list->next = NULL;
}
void listl_insert(struct listl *list, struct listl *elm)
{
    struct listl* tmp = list;
    while(tmp->next != NULL && elm->data->distance > (tmp->next)->data->distance)
        tmp = tmp->next;
    elm->next = tmp->next;
    tmp->next = elm;
}

struct LineParameter* get_max(struct listl* list)
{
    struct listl* res= list;
    while(res->next)
        res = res->next;
    return res->data;
}

struct LineParameter* get_min(struct listl* list)
{
    return list->next->data;
}
