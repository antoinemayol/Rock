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
void getSudok(char *s, int res[9*9])
{
	for(int i = 0; i<9; i++)
	{
		for(int j = 0; j<9; j++)
		{
			if(s[i * 9 + j] == '.')
			{
				res[i*9+j] = 0;
			}

			if(s[i*9+j] >= '1' && s[i*9+j] <= '9')
			{
				res[i*9+j] = (int)(s[i * 9 + j] - '0');
			}
		}
	}
}

//Convert the sudoku "sudok" into a char* and return it
char *ai_to_st(int sudok[9*9])
{
    char *res = malloc(9*9*sizeof(char));

    for(int i = 0; i<9*9;i++)
    {
        res[i] = sudok[i] + '0';
    }
    return res;
}


//Write the sudoku "s" converted by ai_to_st into the "path" file
void writeS(char* s,char* path)
{
    size_t len = strlen(path);
    char* r = ".result";
    char* name = malloc((len+7)*sizeof(char));
    for(size_t i = 0; i < len;i++)
    {
        name[i]=path[i];
    }
    for(size_t i = len; i<len+7; i++)
    {
        name[i]=r[i-len];
    }

	FILE *f = fopen(name,"w");
	if(f == NULL)
	{
		errx(1,"can't open file !");
	}

    for(int i = 1; i<=9*9; i++)
    {
        char tmp = s[i-1];
        if(tmp == '0')
        {
            tmp = '.';
        }

        fprintf(f,"%c",tmp);

        if(i%9==0)
        {
            fprintf(f,"\n");
        }
        else
        {
            if(i%3==0)
            {
                fprintf(f," ");
            }
        }
        if(i != 81&& i%27==0)
        {
            fprintf(f,"\n");
        }
    }
}

void sudok_to_file(int sudok[9*9], char* path)
{
    char* s = ai_to_st(sudok);
    writeS(s,path);
}

//Function to convert a sudoku file into an int array
void file_to_sudok(char* path, int res[9*9])
{
	char *s = getString(path);
	getSudok(s,res);
}




