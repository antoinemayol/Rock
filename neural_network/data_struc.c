#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <math.h>
#include "save_and_load.h"
#include "data_struc.h"

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
	res.array = load(path);
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


//C'EST PAS LA BONNE VAL FAUT MODIF
Brain* create_base(size_t nb_in, size_t nb_layers, size_t* len)
{
	Brain* res = malloc(sizeof(Brain));

	while(*len < nb_layers && nb_in >= 1)
	{
		Brain tmp = get_empty();
		for(size_t i = 0; i < nb_in; i++)
		{
			double r = (double)rand()/(double)RAND_MAX;
			add_b(&tmp,r);
		}
		res = realloc(res, (*len + 1)*sizeof(Brain));
		res[*len] = tmp;
		//free(tmp);

		nb_in = nb_in/3;
		*len = *len +1;
	}
	return res;
}

int main()
{
}
