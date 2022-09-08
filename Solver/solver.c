#include<stdio.h>

#define N 9

void print_grid(int grid[9][9]);
int contains(int arr[], int n);
int is_solvable(int grid[9][9]);
void change_cell(int grid[9][9],int i, int j, int n);
int test_grid[9][9];



void main()
{
    int grid[9][9] = { {3, 0, 6, 5, 0, 8, 4, 0, 0}, 
         {5, 2, 0, 0, 0, 0, 0, 0, 0}, 
         {0, 8, 7, 0, 0, 0, 0, 3, 1}, 
         {0, 0, 3, 0, 1, 0, 0, 8, 0}, 
         {9, 0, 0, 8, 6, 3, 0, 0, 5}, 
         {0, 5, 0, 0, 9, 0, 6, 0, 0}, 
         {1, 3, 0, 0, 0, 0, 2, 5, 0}, 
         {0, 0, 0, 0, 0, 0, 0, 7, 4}, 
         {0, 0, 5, 2, 0, 6, 3, 0, 0} };
    print_grid(grid);
}

void print_grid(int grid[9][9]) // Prints the grid in a square format
{
    //int grid[9][9] = &grd[9][9];
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            printf("%d", grid[i][j]);
            printf(" ");
        }
        printf("\n");
    }
}

void change_cell(int grid[9][9],int i, int j, int n) //Changes the value n of a specific cell inside the grid of i,j index
{
    grid[i][j] = n;
}


int contains(int arr[], int n)
{
    for(int i = 0; i < 9; i++)
    {
        if(arr[i] == n)
        return 1;
    }
    return 0;
}

int is_solvable(int grid[9][9])
{
    //Testing rows
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            int arr[N];
            if (grid[i][j] != 0)
            {
                int *grd = &grid[9][9];
                if (!contains(grd, grid[i][j]))
                {
                   arr[j] += grid[i][j];
                }
                else
                {
                    return 0;
                }
            }
        }
    }

    //Testing columns
    for (int j = 0; j < 9; j++)
    {
        for (int i = 0; i < 9; i++)
        {
            int arr[9];
            if (grid[i][j] != 0)
            {
                int *grd = &grid[9][9];
                if (!contains(grd, grid[i][j]))
                {
                   arr[i] += grid[i][j];
                }
                else
                {
                    return 0;
                }
            }
        }
    }
}