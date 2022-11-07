#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <err.h>

#define MAXLEN 110

//return a char* representing the grid of sudoku 
//from a file (located at "path") 
char *getString(char *path)
{
	FILE *f = fopen(path,"r");
	if(f == NULL)
	{
		errx(1,"can't open file !");
	}

	char* res = malloc(MAXLEN*sizeof(char));

	char* line = NULL;
	size_t len = 0;
	int k = 0;
	while(getline(&line, &len, f) != -1)
	{
		len = strlen(line);
		for(size_t i = 0; i < len && k < MAXLEN; i++)
		{
			if(line[i] != ' ' && line[i]!= '\n')
			{
				res[k] = line[i];
				k++;
			}
		}
	}
	res[k] = '\0';
	return res;
}

//Change the initiale res matrice into a sudoku board from a char*
void getSudok(char *s, int res[9][9])
{
	for(int i = 0; i<9; i++)
	{
		for(int j = 0; j<9; j++)
		{
			printf("2D : [%d][%d]\n",i,j);
			printf("linear : [%d]\n",i*9+j);
			printf("value : %c\n",s[i*9+j]);
			if(s[i * 9 + j] == '.')
			{
				res[i][j] = 0;
			}

			if(s[i*9+j] >= '1' && s[i*9+j] <= '9')
			{
				res[i][j] = (int)(s[i * 9 + j] - '0');
			}
		}
	}
}

//function to convert a sudoku file into an int array
void file_to_sudok(char* path, int res[9][9])
{
	char *s = getString(path);
	getSudok(s,res);
}



