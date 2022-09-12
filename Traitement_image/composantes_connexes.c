#include <stdio.h>
#include <string.h>

void print_mat(int lenght, int width, int matrix[lenght][width]);
void connected_components(int l, int w, int matrix[l][w], int output[l][w]);
void get_partitioned_matrix(int l, int w,int matrix[l][w], int output[l][w]);

int main()
{
    int lenght= 6;
    int width= 6;
    int input[6][6] = {
        {0,0,0,0,0,0},
        {0,1,0,1,0,0},
        {0,1,1,1,0,0},
        {0,0,0,0,0,0},
        {0,0,1,1,1,0},
        {0,0,1,1,1,0}};
    int out[6][6] ={0};
    connected_components(lenght,width,input,out);
    print_mat(lenght, width, out);
    return 0;
}

void print_mat(int lenght, int width, int matrix[lenght][width])
{
	int i;
    for(i = 0 ; i < lenght ; ++i)
    {
    	int j;
    	for (int j = 0; j < width; ++j)
    	{
    		printf("%d ", i[matrix][j]);
    	}
    	printf("\n");
    }
    printf("\n");
}

void connected_components(int l, int w, int matrix[l][w], int output[l][w])
{
    get_partitioned_matrix(l,w,matrix,output);
}

void get_partitioned_matrix(int l, int w,int matrix[l][w], int output[l][w])
{
    int part_number = 0;

    for(int i = 0; i < l; ++i)
    {
        for(int j = 0; j < w; ++j)
        {

            if(matrix[i][j] == 1)
            {
                if(j > 0 && matrix[i][j-1] == 1 )
                {
                    output[i][j] = output[i][j-1];
                }
                else if( i > 0 && matrix[i-1][j] == 1 )
                {
                    output[i][j] = output[i-1][j];
                }
                else
                {
                    ++part_number;
                    output[i][j] = part_number;
                }
            }
        }
    }
}
