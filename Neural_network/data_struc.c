#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
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

Brain load_brain(char* path)
{
	Brain res = get_empty();
	res.array = load(path, &res.len);
	return res;
}


//Load all the neurones in "neurones/" folder and
//returns them is acending order in brain* res 
Brain* make_neuronal(size_t* count)
{
	Brain* res = malloc(sizeof(Brain));

	struct dirent **namelist;
   	int n;
	int i = 0;
   	n = scandir("neurones/", &namelist, NULL, alphasort);
   	if (n < 0)
       	perror("scandir");
   	else 
	{
       	while (i<n) 
		{
			if(namelist[i]->d_name[0] == 'n')
			{
				res = realloc(res, (*count + 1)*sizeof(Brain));

				size_t fullsize = strlen(namelist[i]->d_name)+10;
				char* path = malloc(fullsize*sizeof(fullsize));
				strcpy(path,"neurones/");
				strcat(path,namelist[i]->d_name);

				res[*count] = load_brain(path);
       			free(namelist[i]);
				*count = *(count) + 1;
			}
			i++;
       	}
       	free(namelist);
   	}
	return res;
}

int main()
{

	Brain tmp = get_empty();
	double d[3] = {0.6,0.890,0.369};
	size_t len = 3;
	add_array(&tmp, d, len);
	//Brain test = load_brain("neurones/testload");
	
	size_t c = 0;
	Brain* li = make_neuronal(&c);
	printf("len : %zu",c);
	for(size_t i =0; i < c; i++)
	{
		printf("neu%zu : \n",i);
		for(size_t j = 0; j < li[i].len; j++)
		{
			printf("    val %zu : %f\n",j,li[i].array[j]);
		}
	}
	

}
