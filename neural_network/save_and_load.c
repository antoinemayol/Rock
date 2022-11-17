#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <err.h>

void concat_path(char* res,char* s1, char* s2, char* s3, char *s4, int maxpath)
{
	int k = 0;
	for(size_t i = 0; k < maxpath && s1[i] != '\0'; i++)
	{
		res[k]=s1[i];
		k+=1;
	}

	for(size_t i = 0; k < maxpath && s2[i] != '\0'; i++)
	{
		res[k]=s2[i];
		k+=1;
	}

	for(size_t i = 0; k < maxpath && s3[i] != '\0'; i++)
	{
		res[k]=s3[i];
		k+=1;
	}

	for(size_t i = 0; k < maxpath && s4[i] != '\0'; i++)
	{
		res[k]=s4[i];
		k+=1;
	}
}


void save(double *a, int i, size_t len)
{
	printf("len : %zu\n",len);
	char *num = malloc(5*sizeof(char));
	sprintf(num, "%d", i);
	char *path = malloc(25*sizeof(char));

	concat_path(path,"neurones/", "nerons", num,".txt",25);

	FILE *f = fopen(path,"w");
	if(f == NULL){
		errx(1,"Can't open file !");
	}

	for(size_t j = 0; j<len; j++)
	{
		printf("a : %f\n",a[j]);
		fprintf(f,"%f\n",a[j]);
	}
	fclose(f);

}

void load(char* path, double* array, size_t len)
{
	FILE *f = fopen(path,"r");
	if(f == NULL)
	{
		errx(1,"Can't open file !");
	}
	
	char* line = NULL;
	size_t len_l = 0;
	size_t i = 0;
	while(i < len && getline(&line, &len_l, f) != -1)
	{
		printf("Actual line : %s\n",line);
		double x;
		sscanf(line,"%lf",&x);
		array[i] = x;
		i++;
	}	
}
/*
int main()
{
//	double test[4] = {0.0,0.43,2.34,-65};
//	save(test,0,4);
//	return 0;
	double* res = malloc(3*sizeof(double));
	load("neurones/testload",res,3);
	for(int i =0; i < 3; i++)
	{
		printf("%f\n",res[i]);
	}
}*/
