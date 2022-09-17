#include <stdio.h>
#include <string.h>

void print_mat(int lenght, int width, int matrix[lenght][width])
{
    /* Print a matrix
     * ARGS:
     *  -lenght (int) : lenght of the matrix
     *  -width (int) : width of the matrix
     *  -matrix (int[]) : the matrix to print
     * OUT:
     *  none
     */
    for(int i = 0 ; i < lenght ; ++i)
    {
    	for (int j = 0; j < width; ++j)
    		printf("%d ", i[matrix][j]);
    	printf("\n");
    }
    printf("\n");
}

void apply_equivalence(int l, int w, int output[l][w], int equivalence[1000])
{
    /* Apply equivalence on the matrix
     * ARGS:
     *  -lenght (int) : lenght of the matrix
     *  -width (int) : width of the matrix
     *  -matrix (int[]) : the matrix to modify
     *  -equivalence (int[]) : array of equivalence
     * OUT:
     *  none
     */
    for(int i = 0; i < l; ++i)
        for(int j = 0; j < w; ++j)
            if(output[i][j] != equivalence[output[i][j]])
                output[i][j] = equivalence[output[i][j]];
}

void get_partitioned_matrix(int l, int w,int matrix[l][w], int output[l][w])
{
    /* Reconize different part of the picture
     * ARGS:
     *  -lenght (int) : lenght of the matrix
     *  -width (int) : width of the matrix
     *  -matrix (int[]) : the matrix to analyse
     *  -output (int[]) : the output matrix
     * OUT:
     *  none
     */
    int part_number = 0;
    int equivalence[1000] = {0};
    for(int i = 0; i < l; ++i)
    {
        for(int j = 0; j < w; ++j)
        {
            if(matrix[i][j] == 1)
            {
                if(j > 0 && matrix[i][j-1] == 1 )
                {
                    if(i>0&&matrix[i-1][j]==1 && output[i-1][j]<output[i][j-1])
                    {
                        equivalence[output[i][j-1]] = output[i-1][j];
                        output[i][j] = output[i-1][j];
                    }
                    else
                    {
                        if(i>0&&matrix[i-1][j]==1)
                            equivalence[output[i-1][j]] = output[i][j-1];
                        output[i][j] = output[i][j-1];
                    }
                }
                else if( i > 0 && matrix[i-1][j] == 1 )
                    output[i][j] = output[i-1][j];
                else
                {
                    ++part_number;
                    output[i][j] = part_number;
                    equivalence[part_number] = part_number;
                }
            }
        }
    }
    apply_equivalence(l,w,output,equivalence);
}

void connected_components(int l, int w, int matrix[l][w], int output[l][w])
{
    /* Reconize the sudoku on the picture
     * ARGS:
     *  -lenght (int) : lenght of the matrix
     *  -width (int) : width of the matrix
     *  -matrix (int[]) : the initial binary matrix from the picture
     *  -ouput (int[]) : the sudoku matrix
     * OUT:
     *  none
     */
    get_partitioned_matrix(l,w,matrix,output);
}
