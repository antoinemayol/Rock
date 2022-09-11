#include<stdio.h>

void print_grid(int grid[9][9]);
int contains(int arr[], int n);
int is_solvable(int grid[9][9]);
void change_cell(int grid[9][9],int i, int j, int n);
int test_grid[9][9];
int is_unique(int arr[9]);



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
    printf("%d",is_solvable(grid));
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

int is_unique(int arr[9])
{
    int tmp[9];
    for (int i = 0; i < 9; i++)
    {
        if (arr[i] != 0)
        {
            //printf("yess %d", arr[i]);
            if(contains(tmp, arr[i]))
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

int is_solvable(int grid[9][9])
{
    //Testing rows and columns
    for(int i = 0; i < 9; i++)
    {
        printf("%d", i);
        int row[9];
        
        for (int j = 0; j < 9; i++)
        {
            row[i] = grid[i][j];
        }
        
        if (!is_unique(row))
        {
            printf("error in row : %d\n", i);
            return 0;
        }
        int tmp_arr[9];
        for (int j = 0; j < 9; i++)
        {
            tmp_arr[i] = grid[i][j];
        }
        if(!is_unique(tmp_arr))
        {
            printf("error in columns");
            return 0;
        }
    }
    for (int k = 0; k < 9; k++) // Testing 3 by 3 square
        {
            int tmp[9];
            int count = 0;
            for (int l = (k /3) *3; l < 3; l++)
            {
                for(int m = (k % 3)*3; m < 3; m++)
                {
                    tmp[count] = grid[l][m];
                    count++;
                }
            }
            if(!is_unique(tmp))
            {
                printf("error in squares");
                return 0;
            }
        }
    return 1;
}