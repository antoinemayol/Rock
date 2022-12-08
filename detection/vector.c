#include <err.h>
#include "vector.h"
#include "dot.h"

struct vector *vector_new()
{
    struct vector * res = malloc(sizeof(struct vector));
    res->capacity = 1;
    res->size = 0;
    res->data = malloc(sizeof(struct dot*)*res->capacity*2);
    if(res == NULL || res->data == NULL)
        errx(EXIT_FAILURE,"Not enough memory!");
    return res;
}

void vector_free(struct vector *v)
{
    free(v->data);
    free(v);
}

void double_capacity(struct vector *v)
{
    v->capacity*=2;
    v->data = realloc(v->data,sizeof(struct dot*)*v->capacity);
    if(v->data == NULL)
        errx(EXIT_FAILURE,"Not enough memory!");
}

void vector_push(struct vector *v, struct dot* x)
{
    if(v->capacity == v->size)
        double_capacity(v);
    *(v->data + v->size) = x;
    v->size++;
}

int vector_pop(struct vector *v, struct dot *x)
{
    if(v->size == 0)
        return 0;
    *x = **(v->data + v->size - 1);
    v->size--;
    return 1;
}

