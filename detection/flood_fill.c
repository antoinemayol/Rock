#include <stdlib.h>
#include <stdio.h>
#include "dot.h"
#include "flood_fill.h"
#include "vector.h"

int __flood_fill(int h, int w, int* matrix, struct dot* d, int c)
{
    struct vector* v = vector_new();
    vector_push(v,d);
    int size = 1;
    *(matrix + d->x*w + d->y) = c;
    while(v->size>0)
    {
        int i = vector_pop(v, d);
        int x = d->x;
        int y = d->y;

        size++;
        if(y<w-1 && *(matrix + x*w + (y+1)) == 0)
        {
            struct dot* d1 = init_dot(x,y+1);
            vector_push(v,d1);
            *(matrix + x*w + (y+1)) = c;
        }
        if(x<h-1 && *(matrix + (x+1)*w + y) == 0)
        {
            struct dot* d2 = init_dot(x+1,y);
            vector_push(v,d2);
            *(matrix + (x+1)*w + y) = c;
        }
        if(y>0 && *(matrix + x*w + (y-1)) == 0)
        {
            struct dot* d3 = init_dot(x,y-1);
            vector_push(v,d3);
            *(matrix + x*w + (y-1)) = c;
        }
        if(x>0 && *(matrix + (x-1)*w + y) == 0)
        {
            struct dot* d4 = init_dot(x-1,y);
            vector_push(v,d4);
            *(matrix + (x-1)*w + y) = c;
        }
    }
    return size;
}

int* flood_fill(int h, int w, int* matrix)
{
    int c = 2; 
    int** colors_coo = malloc(sizeof(int*)*2);
    int max_size = 0;
    int max_color = 0;
    for(int x = 0; x < h; x++)
    {
        for(int y = 0; y < w; y++)
        {
            int val = *(matrix + x*w +y);
            if(val != 1)
            {
                if(val == 0)
                {
                    struct dot* d = init_dot(x,y);
                    int size = __flood_fill(h,w,matrix,d,c);
                    colors_coo = realloc(colors_coo, sizeof(int*)*(c+1));
                    *(colors_coo + c) = malloc(sizeof(int)*4);
                    
                    *(*(colors_coo + c)) = x;
                    *(*(colors_coo + c) + 1) = y;
                    *(*(colors_coo + c) + 2) = x;
                    *(*(colors_coo + c) + 3) = y;
                    
                    if(size > max_size)
                    {
                        max_size = size;
                        max_color = c;
                    }
                    c++;
                }
                val = *(matrix + x*w +y);
                if(val > 1)
                {
                    if(x < *(*(colors_coo + val) + 0))
                        *(*(colors_coo + val)) = x;
                    if(y < *(*(colors_coo + val) + 1))
                        *(*(colors_coo + val) + 1) = y;
                    if(x > *(*(colors_coo + val) + 2))
                        *(*(colors_coo + val) + 2) = x;
                    if(y > *(*(colors_coo + val) + 3))
                        *(*(colors_coo + val) + 3) = y;
                }
            }
        }
    }
    int* max_area = *(colors_coo + max_color);
    

    for(int i = 2; i < c + 1; i++)
    {
        if(i != max_color)
            free(*(colors_coo + i));
    }
    free(colors_coo);
    return max_area;
}
