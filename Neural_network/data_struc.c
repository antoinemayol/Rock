#include <stdlib.h>
#include <stdio.h>
#include "save_and_load.h"

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
	double* res = realloc(b->array, (b->len+1)*sizeof(double));
	res[b->len] = d;
	b->len+=1;;
	b->array = res;
}

void add_array(Brain *b, double* a, size_t len_a)
{
	for(size_t i = 0; i < len_a; i++)
	{
		add_b(b,a[i]);
	}
}

void save_brain(Brain b, int i)
{	
	save(b.array, i, b.len);
}

void load_brain(char* path)
{

}

int main()
{
	Brain tmp = get_empty();
	double d[3] = {0.6,0.890,0.369};
	size_t len = 3;
	add_array(&tmp, d, len);
	printf("tmp = %zu\n",tmp.len);
	for(size_t i = 0; i < tmp.len; i++)
	{
		printf("%f\n",tmp.array[i]);
	}

	save_brain(tmp, 9);
}
