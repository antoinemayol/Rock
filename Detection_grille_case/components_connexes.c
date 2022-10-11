#include <stdio.h>
#include <string.h>
#include <limits.h>

void print_mat(int l, int w, int matrix[l*w])
{
    /* Print a matrix
     * ARGS:
     *  -lenght (int) : lenght of the matrix
     *  -width (int) : width of the matrix
     *  -matrix (int[]) : the matrix to print
     * OUT:
     *  none
     */
    for(int i = 0 ; i < l ; ++i)
    {
    	for (int j = 0; j < w; ++j)
    		printf("%d ", (i*w + j)[matrix]);
    	printf("\n");
    }
    printf("\n");
}
int get_obj_nb(int equivalence[1000])
{
    int nb_obj = 0;
    for(int i = 0; i < 1000; ++i)
    {
        if(equivalence[i] != 0 && equivalence[i] == i )
            nb_obj ++;
    }
    return nb_obj;
}

void apply_equivalence(int l, int w, int output[l*w], int equivalence[1000])
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
            if(output[i*w + j] != equivalence[output[i*w + j]])
                output[i*w + j] = equivalence[output[i*w + j]];
}

int get_partitioned_matrix(int l, int w,int matrix[l*w], int output[l*w])
{
    /* Reconize different part of the picture
     * ARGS:
     *  -lenght (int) : lenght of the matrix
     *  -width (int) : width of the matrix
     *  -matrix (int[]) : the matrix to analyse
     *  -output (int[]) : the output matrix
     * OUT:
     *  -nb_obj (int) : number of obj in matrix
     */
    int part_number = 0;
    int equivalence[1000] = {0};
    for(int i = 0; i < l; ++i)
    {
        for(int j = 0; j < w; ++j)
        {
            if(matrix[i*w + j] == 1)
            {
                if(j > 0 && matrix[i*w + j-1] == 1 )
                {
                    if(i>0&&matrix[(i-1)*w + j]==1 &&
                            output[(i-1)*w + j]<output[i*w + j-1])
                    {
                        equivalence[output[i*w+ j-1]] = output[(i-1)*w +j];
                        output[i*w + j] = output[(i-1)*w + j];
                    }
                    else
                    {
                        if(i>0&&matrix[(i-1)*w + j]==1)
                            equivalence[output[(i-1)*w + j]] = output[i*w + j-1];
                        output[i*w + j] = output[i*w + j-1];
                    }
                }
                else if( i > 0 && matrix[(i-1)*w + j] == 1 )
                    output[i*w + j] = output[(i-1)*w + j];
                else
                {
                    ++part_number;
                    output[i*w + j] = part_number;
                    equivalence[part_number] = part_number;
                }
            }
        }
    }
    apply_equivalence(l,w,output,equivalence);
    int nb_obj = get_obj_nb(equivalence);
    return nb_obj;
}

int get_obj_index(int value, int nb_obj, int list[5*nb_obj])
{
    int i = 0;
    while(i<nb_obj && list[i*5] != value)
        ++i;
    return i;
}

void init_size_mat(int nb_obj, int mat[nb_obj*5])
{
    for(int i = 0; i < nb_obj; i++)
    {
        mat[i*5] = i;
        mat[i*5 + 1] = INT_MAX;
        mat[i*5 + 2] = INT_MAX;
        mat[i*5 + 3] = INT_MIN;
        mat[i*5 + 4] = INT_MIN;
    }

}

int calculate_size(int x1, int y1, int x2, int y2)
{
    return (x2 - x1+1)*(y2 - y1+1);
}

void get_biggest_size(int nb_obj, int mat[5*nb_obj], int pos[4])
{
    int biggest = 0;

    for(int i = 0; i < nb_obj; i++)
    {
        int l = calculate_size(mat[i*5 + 1],mat[i*5 + 2],mat[i*5 + 3],mat[i*5 + 4]);
        if(l > biggest)
        {
            biggest = l;
            for(int j = 0; j < 4; j++)
            {
                pos[j] = mat[i*5 + 1 + j];
            }
        }
    }
}

void get_biggest_submat(int l, int w, int matrix[l*w], int nb_obj, int pos[4])
{
    int current_obj_index = 1;
    int submat_size[5*nb_obj] ; //ex: nb,x1,y1,x2,y2
    init_size_mat(nb_obj, submat_size);
    for(int i = 0; i < l; ++i)
    {
        for(int j = 0; j < w; ++j)
        {
            int cell = matrix[i*w + j];
            if(cell != 0){
                if(cell-1 != submat_size[(current_obj_index-1)*5])
                {
                    current_obj_index = get_obj_index(cell, nb_obj, submat_size);
                }
                int *x1 = &submat_size[(current_obj_index-1)*5 + 1];
                int *y1 = &submat_size[(current_obj_index-1)*5 + 2];
                int *x2 = &submat_size[(current_obj_index-1)*5 + 3];
                int *y2 = &submat_size[(current_obj_index-1)*5 + 4];

                if(i<*x1)
                    *x1 = i;
                if(i>*x2)
                    *x2 = i;
                if(j<*y1)
                    *y1 = j;
                if(j>*y2)
                    *y2 = j;
            }
        }
    }
    get_biggest_size(nb_obj,submat_size,pos);

}

void extract_biggest_obj(int pos[4],int l, int w, int mat[l*w], int final[])
{
    int l2 = pos[2] - pos[0]+1;
    int w2 = pos[3] - pos[1]+1;
    for(int i = 0; i<l2; i++)
    {
        for(int j = 0; j < w2; j++)
        {
            final[i*w2 + j] =mat[(pos[0]+i)*w +(pos[1]+j)];
        }
    }
}

void connected_components(int l, int w, int matrix[l*w], int output[l*w])
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

    int nb_obj = get_partitioned_matrix(l,w,matrix,output);
    int pos[4];
    get_biggest_submat(l, w, output, nb_obj, pos);
   
    int final[calculate_size(pos[0], pos[1], pos[2], pos[3])];
    extract_biggest_obj(pos, l, w,matrix, final);
    print_mat(pos[2] - pos[0] +1 , pos[3] - pos[1]+1, final);

}
