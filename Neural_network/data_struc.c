#include <stdlib.h>
#include <stdio.h>

typedef struct Brain{
	double* array;
	size_t len;
	size_t index;
}Brain;

Brain get_empty()
{
	Brain res;
	res.array = malloc(sizeof(double));
	res.len = 0;
	res.index = 0;
	return res;
}

void add_b(Brain *b, double d)
{
	double* res = realloc(b->array, b->len+1*sizeof(double));
	res[b->len] = d;
	b->len+=1;;
	b->array = res;
}

int main()
{
	Brain tmp = get_empty();
	double d = 0.6;
	add_b(&tmp, d);
	printf("%f\n",b.array[0]);
	printf("tmp = %zu",tmp.len);
}
