#ifndef _LIST_LINE_H_
#define _LIST_LINE_H_
#include <stddef.h>
#include "LineParameter.h"

struct listl
{
  struct listl *next;
  struct LineParameter* data;
};
void free_alll(struct listl* l);
size_t listl_len(struct listl *list);
int average_diff(struct listl* l);
// Initialize the sentinel of an empty list.
void listl_init(struct listl *list);


// Insert 'elm' in the sorted list (keeping the list sorted).
// Note that 'elm' is already an existing element.
// You just have to insert it.
void listl_insert(struct listl *list, struct listl *elm);
struct LineParameter* get_max(struct listl* list);
struct LineParameter* get_min(struct listl* list);

#endif
