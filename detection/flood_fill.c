#include <stdlib.h>

int __flood_fill(int h, int w, int* matrix, int x, int y, int c)
{
    *(matrix + x*w + y) = c;
    int size = 1;
    if(x>0 && *(matrix + (x-1)*w + y)==0)
        size += __flood_fill(h, w, matrix, x-1, y, c);
    if(y>0 && *(matrix + x*w + (y-1))==0)
        size += __flood_fill(h, w, matrix, x, y-1, c);
    if(x<h && *(matrix + (x+1)*w + y)==0)
        size += __flood_fill(h, w, matrix, x+1, y, c);
    if(y<w && *(matrix + x*w + (y+1))==0)
        size += __flood_fill(h, w, matrix, x, y+1, c);
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
                    int size = __flood_fill(h,w,matrix,x,y,c);
                    colors_coo = realloc(colors_coo, sizeof(int*)*(c+1));
                    *(colors_coo + c) = malloc(sizeof(int)*4);
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
                        *(*(colors_coo + val)) = y;
                    if(x > *(*(colors_coo + val) + 2))
                        *(*(colors_coo + val)) = x;
                    if(y > *(*(colors_coo + val) + 3))
                        *(*(colors_coo + val)) = y;
                }
            }
        }
    }
    int x1 = *(*(colors_coo + max_color));
    int y1 = *(*(colors_coo + max_color) + 1);
    int x2 = *(*(colors_coo + max_color) + 2);
    int y2 = *(*(colors_coo + max_color) + 3);

    for(int i = 2; i < c + 1; i++)
    {
        free(*(colors_coo + i));
    }
    printf("%d %d %d %d\n",x1, y1, x2, y2);
    free(colors_coo);
    return NULL;
}
