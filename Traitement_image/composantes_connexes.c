#include <stdio.h>
#include <string.h>

void print_mat(int *matrix, int length, int width)
{
	int i;
    for(i = 0 ; i < length ; ++i)
    {
    	int j;	
    	for (int j = 0; j < width; ++j)
    	{
    		printf("%d ", i[matrix][j]);//to fix
    	}
    	printf("\n");	
    }
    printf("\n");
}


int main()
{
	/*printf("lol\n");
	int rows = 5;
	int columns = 5;

	int mat[5][5]=	{{0,0,0,0,0},
					{0,1,0,0,0},
					{0,1,1,1,0},
					{0,0,1,1,0},
					{0,0,0,0,0}};


	print_mat(rows, columns, mat);
	*/
	int lenght = 6;
	int width = 8;

	int visited[lenght][width];
	for (int i = 0; i < lenght ; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			visited[i][j] = 0;
		}
	}

	return 0;
}

