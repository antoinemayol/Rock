#include<stdio.h>

#define C 9

//Current task: Testing get-square --> No prints


/*------------------------------------------------------*/
// All declarations
void print_grid(int grid[C][C]);
int contains(int arr[], int n);
int is_solvable(int grid[C][C]);
void change_cell(int grid[C][C],int i, int j, int n);
int *get_row(int grid[C][C], int i, int *res);
int *get_col(int grid[C][C], int j, int *res);
int *get_square(int grid[C][C], int i, int j, int* res);

int test_grid[9][9];
/*------------------------------------------------------*/


void main()
{
    int test_grid[C][C] = { 
         {3, 0, 6, 5, 0, 8, 4, 0, 0}, 
         {5, 2, 0, 0, 0, 0, 0, 0, 0}, 
         {0, 8, 7, 0, 0, 0, 0, 3, 1}, 
         {0, 0, 3, 0, 1, 0, 0, 8, 0}, 
         {9, 0, 0, 8, 6, 3, 0, 0, 5}, 
         {0, 5, 0, 0, 9, 0, 6, 0, 0}, 
         {1, 3, 0, 0, 0, 0, 2, 5, 0}, 
         {0, 0, 0, 0, 0, 0, 0, 7, 4}, 
         {0, 0, 5, 2, 0, 6, 3, 0, 0} };
         int *ptr;
         int test[C];
         ptr = get_square(test_grid, 0, 0, test);
         for (int i = 0; i < C; i++)
         {
            printf("%d ", ptr[i]);
         }
}

void print_grid(int grid[C][C]) // Prints the grid in a square format
{
    //int grid[9][9] = &grd[9][9];
    for (int i = 0; i < C; i++)
    {
        for (int j = 0; j < C; j++)
        {
            printf("%d", grid[i][j]);
            printf(" ");
        }
        printf("\n");
    }
}

void change_cell(int grid[C][C],int i, int j, int n) //Changes the value n of a specific cell inside the grid of i,j index
{
    grid[i][j] = n;
}


int contains(int arr[C], int n) // Returns 1 if the number n is an element of the array, 0 otherwise
{
    for(int i = 0; i < C; i++)
    {
        if(arr[i] == n)
        return 1;
    }
    return 0;
}

int *get_row(int grid[C][C], int i, int *res) //Returns an int array contaning the specified row at index i
 {
    for (int n = 0; n < C; n++)
    {
        res[n] = grid[i][n];
    }
    return res;
 }

int *get_col(int grid[C][C], int j, int *res) //Returns an int array contaning the specified column at index j
 {
    for (int n = 0; n < C; n++)
    {
        res[n] = grid[n][j];
    }
    return res;
 }

int *get_square(int grid[C][C], int i, int j, int *res) //Returns an int array contaning the specified 3 by 3 square at starting point of index i and j
{
    int n = 0;
    for (int k = i; k < 3+i; k++)
    {
        for (int l = j; j < 3+j; j++)
        {
            res[n] = grid[k][l];
            n++;
        }
    }
    return res;
}
/*
int is_valid(int arr[C]) // Returns 1 if the array has no doubled elements, 0 otherwise
{
    int tmp[C];
    for (int i = 0; i < C; i++)
    {
        if (arr[i] != 0)
        {
            if (contains(tmp, arr[i]))
            {
                return 0;
            }
            else
            {
                tmp[i] = arr[i];
            }
        }
    }
    return 1;
}

int is_solvable(int grid[C][C]) //Returns 1 if if the grid is solvable, 0 otherwise
{
    //Checking rows
    for (int i = 0; i < C; i++) 
    {
        int row[C];
        row = get_row(grid,i);
        if (!is_valid(row))
        {
            return 0;
        }
    }

    //Checking columns
    for (int j = 0; j < C; j++)
    {
        int col[C];
        col = get_col(grid,j);
        if (!is_valid(col))
        {
            return 0;
        }
    }

    //Checking squares
    for (int i = 0; i < C; i+=3)
    {
        for (int j = 0; j < C; j+=3)
        {
            int square[C];
            square = get_square(grid,i,j);
            if (!is_valid(square))
            {
                return 0;
            }
        }
    }

    return 1;
}
*/