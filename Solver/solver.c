#include<stdio.h>

#define N 9

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

void print_grid(int grid[9][9]) // Prints the grid in a square format
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
}

void change_cell(int grid[9][9],int i, int j, int n) //Changes the value n of a specific cell inside the grid of i,j index
{
    grid[i][j] = n;
}


int contains(int arr[9], int n)
{
    for(int i = 0; i < sizeof(arr); i++)
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
                if (!contains(grid[9][9], grid[i][j])
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
    for (int j = 0; i < 9; j++)
    {
        for (int i = 0; j < 9; i++)
        {
            int arr[9];
            if (grid[i][j] != 0)
            {
                if (!contains(grid[9][9], grid[i][j])
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
    /*
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
                    *\
                }
                
            }
        }
    }
}