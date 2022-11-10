#include<stdio.h>
#include<stdlib.h>
#include "parser.h"
#include <err.h>


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


int main(int argc,char **argv)
{
    if(argc != 2)
    {
        errx(1,"Invoke with 1 argument !");
    }

	printf("\n ------------------------------\n\n");
	
	int to_solve[9*9] = {0};

	//Import the sudoku file and print the grid
    file_to_sudok(fi,to_solve);
	print_grid(to_solve);

	printf("\n ------------------------------\n\n");

	//Resolve the sudoku and print the grid
	backtracking(to_solve,0);
	print_grid(to_solve);

	printf("\n ------------------------------\n\n");
	
	//Save the sudoku
    sudok_to_file(to_solve,fi);

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
//Backtracking algorithm

//Check if the value k are on the row
int absentOnRow (int k, int *grid, int i)
{
	for(int j = 0; j < 9;j++)
	{
		if(grid[i*9+j] == k)
			return 0;
	}
	return 1;
}

//Check if the value k are on the col
int absentOnCol (int k, int *grid, int j) 
{
    for(int i = 0; i < 9;i++)
	{
		if(grid[i*9+j] == k)
			return 0;
	}
	return 1;
}

//Check if the value k are on the square
int absentOnBloc (int k, int *grid, int i, int j)
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
		//We see if the position is at the end of the matrice
		if (position > 80)
				return 1;
		
		//We initialize the variable i and j with position
		int i = position / 9;
		int j = position % 9;
		
			
		if(grid[i*9+j] != 0)
		{
			return backtracking(grid,position + 1);
		}
		
		//Start the backtracking with a variable that can take all the different value in a sudoku
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

