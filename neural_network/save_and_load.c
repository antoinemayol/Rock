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
	char *num = malloc(5*sizeof(char));
	sprintf(num, "%d", i);
	char *path = malloc(21*sizeof(char));

    printf("1 = %s\n",path);
    strcpy(path,"neurones/nerons");
    printf("2 = %s\n",path);
    strcat(path,num);
    printf("3 = %s\n",path);
    strcat(path,".txt");

    printf("----------\n");
    printf("4 = path = %s\n",path);
    printf("----------\n");

	FILE *f = fopen(path,"w");
	if(f == NULL){
		errx(1,"Can't open file !");
	}

	for(size_t j = 0; j<len; j++)
	{
		fprintf(f,"%f\n",a[j]);
	}
	fclose(f);

}

void add_one(double** a, double b, size_t* len)
{
	double* res = realloc(*a,(*len+1)*sizeof(double));
	res[*len] = b;
	*len = *(len) + 1;
	*a = res;
}

double* load(char* path)
{
	FILE *f = fopen(path,"r");
	if(f == NULL)
	{
		errx(1,"Can't open file !");
	}

	double* array = malloc(sizeof(double));
	char* line = NULL;
	size_t len_l = 0;
	size_t i = 0;
    size_t len = 0;

	while(getline(&line, &len_l, f) != -1)
	{
		double x;
		sscanf(line,"%lf",&x);
		add_one(&array, x, &len);
		i++;
	}
	return array;
}
/*
int main()
{
    //double test[4] = {0.0,0.43,2.34,-65};
	//save(test,0,4);
	//return 0;
	//size_t len = 0;
	double* res = load("neurones/testload");
	for(size_t i =0; i < 3; i++)
	{
        printf("res : %f\n",res[i]);
	}
}
*/

