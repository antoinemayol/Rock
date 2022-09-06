#include<stdio.h>

#define N 9;

void main()
{
    int grid[9][9];
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            grid[i][j] = 0;
        }
    }
}

void print_grid(int grid[N][N]) // Prints the grid in a square format
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            printf("%d", grid[i][j]);
            printf(" ");
        }
        printf("/n");
    }
    return 0;
}

void change_cell(int grid[N][N],int i, int j, int n) //Changes the value n of a specific cell inside the grid of i,j index
{
    grid[i][j] = n;
}


bool contains(int arr[], int n)
{
    for(int i = 0; i < sizeof(arr); i++)
    {
        if(arr[i] == n)
        return true;
    }
    return false;
}

bool is_solvable(int grid[N][N])
{
    //Testing rows
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            int arr[N];
            if (grid[i][j] != 0)
            {
                if (!contains(grid[][], grid[i][j])
                {
                   arr[j] += grid[i][j];
                }
                else
                {
                    return false;
                }
            }
        }
    }

    //Testing columns
    for (int j = 0; i < 9; j++)
    {
        for (int i = 0; j < 9; i++)
        {
            int arr[N];
            if (grid[i][j] != 0)
            {
                if (!contains(grid[][], grid[i][j])
                {
                   arr[i] += grid[i][j];
                }
                else
                {
                    return false;
                }
            }
        }
    }

    //Testing 3*3 squares
    for (int i = 0; i < 9; j+=3)
    {
        for (int i = 0; j < 9; i++)
        {
            int arr[N];
            if (grid[i][j] != 0)
            {
                if (!contains(grid[][], grid[i][j])
                {
                    /* code */
                }
                
            }
        }
    }
}