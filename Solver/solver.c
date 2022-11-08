#include<stdio.h>
#include<stdlib.h>
#include "parser.h"


#define C 9

//Current task: Testing get-square --> No prints


/*------------------------------------------------------*/
// All declarations
void print_grid(int *grid);
int contains(int *arr, int n,int j);
int is_solvable(int *grid);
void change_cell(int *grid,int i, int j, int n);
int *get_row(int *grid, int i);
int *get_col(int *grid, int j);
int *get_square(int *grid, int i, int j);
int absentOnRow(int k,int *grid,int i);
int absentOnCol(int k,int *grid,int j);
int absentOnBloc(int k, int *grid,int i,int j);
int backtracking(int *grid,int position);

int test_grid[9][9];
/*------------------------------------------------------*/


int main()
{
    	
	int res[9*9] = {
		7, 5, 1,  8, 4, 3,  9, 2, 6,
		8, 9, 3,  6, 2, 5,  1, 7, 4, 
		6, 4, 2,  1, 7, 9,  5, 8, 3,
		4, 2, 5,  3, 1, 6,  7, 9, 8,
		1, 7, 6,  9, 8, 2,  3, 4, 5,
		9, 3, 8,  7, 5, 4,  6, 1, 2,
		3, 6, 4,  2, 9, 7,  8, 5, 1,
		2, 8, 9,  5, 3, 1,  4, 6, 7,
		5, 1, 7,  4, 6, 8,  2, 3, 9};

	print_grid(res);

	printf("\n ------------------------------\n");
	
	
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


	
	backtracking(to_solve,0);

	print_grid(to_solve);
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

void change_cell(int *grid,int i, int j, int n) //Changes the value n of a specific cell inside the grid of i,j index
{
    grid[i*9+j] = n;
}


int contains(int *arr, int n,int j) // Returns 1 if the number n is an element of the array, 0 otherwise
{
    for(int i = j+1; i < 9; i++)
    {
        if(arr[i] == n)
        	return 1;
    }
    return 0;
}

int *get_row(int *grid, int i) //Returns an int array contaning the specified row at index i
 {
	int *res = malloc(sizeof(int)*C*C);
	//printf("a\n");
    for (int n = 0; n < 9; n++)
    {
		//printf("get_row %u\n",n);

        res[n] = grid[i+n];
    }
	return res;
 }

int *get_col(int *grid, int j) //Returns an int array contaning the specified column at index j
 {
	int *res = malloc(sizeof(int)*C);

    for (int n = 0; n < 9; n++)
    {
        res[n] = grid[n*9+j];
    }
   return res;
 }

int *get_square(int *grid, int i, int j) //Returns an int array contaning the specified 3 by 3 square at starting point of index i and j
{
	int *res = malloc(sizeof(int)*C);

    int n = 0;
    for (int k = i; k < 3+i; k++)
    {
        for (int l = j; l < 3+j; l++)
        {
            res[n] = grid[k*9+l];
			//printf("get_squarre\n");
            n++;
        }
    }
	return res;
    
}

int __is_valid(int *arr) // Returns 1 if the array has no doubled elements, 0 otherwise
{
    for (int i = 0; i < 9; i++)
    {
		if (arr[i] != 0)
        {
           		if (contains(arr, arr[i],i))
           		{
					return 0;
				}
		}
        
		else
		{
			return 0;
		}
		
    }
    return 1;
}

int is_solvable(int *grid) //Returns 1 if if the grid is solvable, 0 otherwise
{
    //Checking rows
    //printf("je suis passé 1 \n");
	
	for (int i = 0; i < 9; i++) 
    {
		int *tmp = get_row(grid,i*9);
		//printf("passage2 %u \n",i);
		
        if (!__is_valid(tmp))
        {
            return 0;
        }
		//printf("fin passage");
	}
	
	//printf("je suis passé 2");


    //Checking columns
    for (int j = 0; j < C; j++)
    {
		
        int *col = get_col(grid,j);
        if (!__is_valid(col))
        {
            return 0;
        }
    }
	//printf("je suis passé 1 \n");


    //Checking squares
    for (int i = 0; i < C; i+=3)
    {
        for (int j = 0; j < C; j+=3)
        {
            int *square = get_square(grid,i,j);
            if (!__is_valid(square))
            {
                return 0;
            }
        }
    }
	//printf("je suis passé 1 \n");

    return 1;
}

//------------------------------------------------
//algorithme backtracking
//

int absentOnRow (int k, int *grid, int i)
{
	for(int j = 0; j < 9;j++)
	{
		if(grid[i*9+j] == k)
				

				return 0;
	}
	return 1;
}

int absentOnCol (int k, int *grid, int j)
{
    for(int i = 0; i < 9;i++)
	{
		if(grid[i*9+j] == k)
				

				return 0;
	}
	return 1;

}

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
		//we see if the position is at the end of the matrice
		//printf("%u\n",position);
		if (position > 80)
				return 1;
		
		//we initialize the variable i and j with position
		int i = position / 9;
		int j = position % 9;
		
	
		if(grid[i*9+j] != 0)
		{
			backtracking(grid,position + 1);
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

