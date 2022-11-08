#include<stdio.h>
#include<stdlib.h>
#include "parser.h"


#define C 9

//Current task: Testing get-square --> No prints


/*------------------------------------------------------*/
// All declarations
void print_grid(int *grid);
int absentOnRow(int k,int *grid,int i);
int absentOnCol(int k,int *grid,int j);
int absentOnBloc(int k, int *grid,int i,int j);
int backtracking(int *grid,int position);

int test_grid[9][9];
/*------------------------------------------------------*/


int main()
{
    	
	/*int res[9*9] = {
		7, 5, 1,  8, 4, 3,  9, 2, 6,
		8, 9, 3,  6, 2, 5,  1, 7, 4, 
		6, 4, 2,  1, 7, 9,  5, 8, 3,
		4, 2, 5,  3, 1, 6,  7, 9, 8,
		1, 7, 6,  9, 8, 2,  3, 4, 5,
		9, 3, 8,  7, 5, 4,  6, 1, 2,
		3, 6, 4,  2, 9, 7,  8, 5, 1,
		2, 8, 9,  5, 3, 1,  4, 6, 7,
		5, 1, 7,  4, 6, 8,  2, 3, 9};*/

	//print_grid(res);

	printf("\n ------------------------------\n\n");
	
	
	int to_solve[9*9] = 
    {
        9,0,0,1,0,0,0,0,5,
        0,0,5,0,9,0,2,0,1,
        8,0,0,0,4,0,0,0,0,
        0,0,0,0,8,0,0,0,0,
        0,0,0,7,0,0,0,0,0,
        0,0,0,0,2,6,0,0,9,
        2,0,0,3,0,0,0,0,6,
        0,0,0,2,0,0,9,0,0,
        0,0,1,9,0,4,5,7,0
    };


	print_grid(to_solve);

	printf("\n ------------------------------\n\n");

	backtracking(to_solve,0);

	print_grid(to_solve);

	printf("\n ------------------------------\n\n");

	return 0;
}

void print_grid(int *grid) // Prints the grid in a square format
{
    //int grid[9][9] = &grd[9][9];
    for (int i = 0; i < C; i++)
    {
        for (int j = 0; j < C; j++)
        {
            printf("%u", grid[i* 9 +j]);
            printf(" ");
        }
        printf("\n");
    }
}

//------------------------------------------------
//algorithme backtracking
//

int absentOnRow (int k, int *grid, int i) //check if the value k are on the row
{
	for(int j = 0; j < 9;j++)
	{
		if(grid[i*9+j] == k)
				

				return 0;
	}
	return 1;
}

int absentOnCol (int k, int *grid, int j) //check if the value k are on the col
{
    for(int i = 0; i < 9;i++)
	{
		if(grid[i*9+j] == k)
				

				return 0;
	}
	return 1;

}

int absentOnBloc (int k, int *grid, int i, int j)//check if the value k are on the square
{
	i -= i%3;
	j -= j%3;
	for(int y = i; y < i+3 && y < 9;y++)
	{
		for(int z = j; z < j+3 && z< 9;z++)
		{
			if(grid[y*9+z] == k)
					

					return 0;
		}
	}
	return 1;
}

int backtracking(int *grid,int position)
{
		//we see if the position is at the end of the matrice
		//printf("%u\n",position);
		if (position > 80)
				return 1;
		
		//we initialize the variable i and j with position
		int i = position / 9;
		int j = position % 9;
		
			
		if(grid[i*9+j] != 0)
		{
			return backtracking(grid,position + 1);
			
		}
		
		//start the backtracking with a variable can take all the different value in a sudoku
		for(int k = 1; k <= 9;k++)
		{
			if(absentOnRow(k,grid,i) && absentOnCol(k,grid,j) && absentOnBloc(k,grid,i,j))
			{
				
				grid[i*9+j] = k;
				

				if(backtracking(grid,position + 1))
						return 1;
			}
		}
			
		grid[i*9+j] = 0;
		return 0;
}

