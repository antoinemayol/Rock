#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void print_graph(int l, int w, int *matrix)
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
        {
            if(*(matrix + i*w + j) < 3)
                printf("\033[0;32m");
            else if((i*w + j)[matrix] < 64)
                printf("\033[0;33m");
            else{
                printf("\033[0;31m");
            }
    		printf("● \033[0m");
        }
    	printf("\n");
    }
    printf("\n");
}
void hough_transform(int l, int w, int *mat, int *hough_val)
{
    /* Calculate the number of occurences for each equation possible
     * ARGS:
     *  -lenght (int) : lenght of the matrix
     *  -width (int) : width of the matrix
     *  -matrix (*int) : the matrix to print
     *  -haugh_val (*int) : the haugh table
     * OUT:
     *  none
     */
    double max_p = l;

    for(double i = 0; i < 180;i++)
        for(double j = 0; j < max_p*2; j++)
            *(hough_val + (int)(i*max_p*2 + j)) = 0;

    for(int i = 0; i < l;i++)
        for(int j = 0; j < w; j++)
            if(*(mat + i*w + j))
                    for(double arg = -90; arg < 90; arg++)
                    {
                        float radian = arg * (M_PI / 180.0);
                        int p = (int)(i*cos(radian) + j*sin(radian));
                        *(hough_val + (int)((p + max_p)*180 + (arg+90))) +=1;
                    }
}

int get_max_hough_occ(int l, int w, int *hough)
{
    int max = 0;
    for(int i = 0; i < l; i ++)
       for(int j = 0; j < w; j++)
           if(*(hough + i*w +j) > max)
                   max = *(hough +i*w +j);
    return max;
}

int is_val_in_arr(int x, int* arr,int len)
{
    int i = 0;
    int not_in = 1;
    while(i < len && not_in)
    {
        not_in = *(arr + i) != x;
        i++;
    }
    return !not_in;
}

int deg_approximation(int deg,int biais, int cible)
{
    return deg >= cible - biais && deg <= cible + biais;
}


int** extract_intersection(int* horizontal_equ, int* vertical_equ, int lenh, int lenv)
{
    //int threshold = 2;
    int **coordonates = malloc(sizeof(int *)*81);
    
    for(int i = 0; i < lenh - 1; i++)
        for(int j = 0; j < lenv - 1; j++)
        {
            int* coo = malloc(sizeof(int)*4);
            *coo = *(horizontal_equ + i) + 1;
            *(coo + 1) = *(vertical_equ + j + 1) + 1;
            *(coo + 2) = *(horizontal_equ + i + 1);
            *(coo + 3) = *(vertical_equ + j);
            *(coordonates + i*(lenv - 1) + j) = coo;
        }
    return coordonates;
}

int** get_equation(int phi,int roh, int *hough_val)
{
    int max_occ = get_max_hough_occ(phi*2, roh*2, hough_val);
    
    int *horizontal_equ = malloc(sizeof(int));
    int *vertical_equ = malloc(sizeof(int));

    int nb_eq_ho = 0;
    int nb_eq_ve = 0;

    int threshold = 6;

    for(int i = 0; i < phi*2; i ++)
    {
       for(int j = 0; j < roh*2; j++)
       {
           if(*(hough_val + i*roh*2 + j) >= max_occ - threshold)
           {
               int deg = j - roh;
               int distance = i - phi;
               if(deg_approximation(deg, 3, 0))
               {
                    if(nb_eq_ho == 0 || !is_val_in_arr(distance, horizontal_equ, nb_eq_ve))
                    {
                        nb_eq_ho ++;
                        horizontal_equ = realloc(horizontal_equ, sizeof(int)*nb_eq_ho);
                        *(horizontal_equ + nb_eq_ho - 1) = distance;
                    }
               }
               else if(deg_approximation(deg, 3, -90))
               {
                    if(nb_eq_ve ==0 || !is_val_in_arr(distance, vertical_equ, nb_eq_ve))
                    {
                        nb_eq_ve ++;
                        vertical_equ = realloc(vertical_equ, sizeof(int)*nb_eq_ve);
                        *(vertical_equ + nb_eq_ve - 1) = distance*-1;
                    }
               }
           }
       }
    }
    int** coo = extract_intersection(horizontal_equ, vertical_equ, nb_eq_ho, nb_eq_ve);
    free(horizontal_equ);
    free(vertical_equ);
    return coo;
}

void stock_cases(int** coo, int* matrix, int width, int** cases)
{
    /* Stock all matrix of cases
     * ARGS:
     *  -coo (int**) cordonates of cases
     *  -width (int) : width of the matrix
     *  -matrix (int[]) : the matrix to print
     *  -cases (int**) : destination pointers
     * OUT:
     *  none
     */
    int nb_case = 81;
    for(int i = 0 ; i < nb_case ; ++i)
    {
        int X1 = *(*(coo+i));
        int Y1 = *(*(coo+i) +1);
        int X2 = *(*(coo+i) +2);
        int Y2 = *(*(coo+i) +3);
        int l = X2 - X1;
        int w = Y2 - Y1;
        int* new = malloc(sizeof(int)*l*w); 
        for(int j = 0; j < l; j++)
            for(int k = 0; k < w; k++)
                *(new +j*w + k) = *(matrix +(X1 + j)*width + Y1 + k);
        *(cases + (i/9)*9 + 9 - i % 9 - 1) = new;
    } 
}

int** hough_traitement(int l, int w, int *mat)
{
    double max_p = l;
    double mat_size = 180*max_p*2;
    const int nb_cases = 81;

    int* hough_val = malloc(mat_size*sizeof(int));

    hough_transform(l, w, mat, hough_val);
    int** coo = get_equation((int)max_p,90,hough_val);

    int** cases = malloc(sizeof(int *)*nb_cases);

    stock_cases(coo, mat, w, cases); 
    for(int i = 0; i < nb_cases; i++)
        free(*(coo +i));

    free(coo);
    free(hough_val);

    return cases;
}
