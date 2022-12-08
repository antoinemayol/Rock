#include <stdlib.h>
#include <stdio.h>

int __flood_fill(int h, int w, int* matrix, int x, int y, int c)
{
    *(matrix + x*w + y) = c;
    int size = 1;
    printf("%d\n",h);
    if(x>0 && *(matrix + (x-1)*w + y)==0)
        size += __flood_fill(h, w, matrix, x-1, y, c);
    if(y>0 && *(matrix + x*w + (y-1))==0)
        size += __flood_fill(h, w, matrix, x, y-1, c);
    if(x<h-1 && *(matrix + (x+1)*w + y)==0)
        size += __flood_fill(h, w, matrix, x+1, y, c);
    if(y<w-1 && *(matrix + x*w + (y+1))==0)
        size += __flood_fill(h, w, matrix, x, y+1, c);
    return size;
}

int _calculate_size(int* colors_coo)
{
    int x1 = *(colors_coo);
    int y1 = *(colors_coo + 1);
    int x2 = *(colors_coo + 2);
    int y2 = *(colors_coo + 3);

    return (x2-x1)*(y2-x2);
}

int* get_max_obj(int** colors, int nb)
{
    int max = 0;
    int max_i = 0;
    
    for(int i = 2; i < nb; i++)
    {
        int size = _calculate_size(*(colors + i));
        if(size > max)
        {
            max = size;
            max_i = i;
            printf("%d\n",i);
        }
    }

    return *(colors + max_i);
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
                    int size = __flood_fill(h,w,matrix,x,y,c);
                    
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
    int x1 = *(max_area);
    int y1 = *(max_area + 1);
    int x2 = *(max_area + 2);
    int y2 = *(max_area + 3);

    for(int i = 2; i < c + 1; i++)
    {
        free(*(colors_coo + i));
    }
    printf("%d %d %d %d\n",x1, y1, x2, y2);
    free(colors_coo);
    return NULL;
}
