#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void transvection(int **A, int k, int i, int alpha, int n)
{
    for(int j = 0; i < n; i++)
    {
        A[k][j] = A[k][j] - alpha*A[i][j];
    }
}

void exchange_line(int **A, int i, int j, int n)
{
    for(int k= 0; k < n; k++)
    {
        int tmp = A[i][k];
        A[i][k] = A[j][k];
        A[j][k] = tmp;
    }
}

int p_search(int **A, int i, int n)
{
    int i_mem = i;
    for(int j = i+1; j < n; j++)
    {
        if(abs(A[i][j])>abs(A[i_mem][i]))
        {
            i_mem = j;
        }
    }
    return i_mem;
}

void transpose(int **A, int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            int tmp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = tmp;
        }
    }
}

void substitution(int **A, int i, int a, int *line, int n)
{
    for(int j = 0; j < n; j++)
    {
        A[i][j] = A[i][j]/a;
    }
    for(int k = n-1; k < i-1; k++)
    {
        transvection(A, i, k, line[k]/a, n);
    }
}

int **copy_mat(int **A, int n)
{
    int **Ar = malloc(sizeof(int*)*n);
    for(int i  = 0; i < n; i++)
    {
        Ar[i] = malloc(sizeof(int)*n);
    }
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            Ar[i][j] = A[i][j];
        }
    }
    return Ar;
}

int **create_empty_mat(int n)
{
    int **Ar = malloc(sizeof(int*)*n);
    for(int i  = 0; i < n; i++)
    {
        Ar[i] = malloc(sizeof(int)*n);
    }
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            Ar[i][j] = 0;
        }
    }
    return Ar;
}

int **inverse(int **A0, int n)
{
    int **A =copy_mat(A0, n);
    int **inv = create_empty_mat(n);
    for(int i = 0; i < n; i++)
    {
        int j = p_search(A,i,n);
        if(j>i)
        {
            exchange_line(A,i,j,n);
            exchange_line(inv,i,j,n);
        }
        for(int k = i+1; k<n; k++)
        {
            int alpha = A[k][i]/A[i][i];
            transvection(A,k,i,alpha,n);
            transvection(inv,k,i,alpha,n);
        }
    }
    for(int i = n-1; n>-1; n--)
    {
        int a = A[i][i];
        int *line = malloc(sizeof(int)*n);
        for(int z = 0; z<n; z++)
        {
            line[z] = A[i][z];
        }
        substitution(A, i, a, line, n);
        substitution(inv, i, a, line, n);
    }
    return inv;
}
