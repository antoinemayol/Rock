#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

#define M_PI 3.14159265358979323846
#define sigma 1.5
#define W 540 //width of the pic
#define H 480 // height of the pic
#define M 9 // width qnd length of the kernel

float get_weight(int i,int j)//1
{
    return (1/((2*M_PI*sigma*sigma)*(expf(-(i*i + j*j)/2*sigma*sigma))));
}


float* set_weight(int i, int j)//2
{
    float arr[M];
    int klen = sqrt(M)-1;
    int c = 0;
    for(int k = -1; k < klen; k++)
    {
        for(int l = -1; l < klen; l++)
        {
            if(i+k >= 0 && i+k < M && j+l >= 0 && j+l < M)
            {
                arr[c]= get_weight(i+k,j+l);
            }
            c++;
        }
    }
    return &arr; 

}

float get_average(float *arr) //3
{
    float res = 0;
    for(int k = 0; k < M; k++)
    {
        res+= get_weight(i+k,j+l);
        nb++;
    }
    return res;
    //return math.roundf(res/float(nb))
}

float* update_weight(int i, int j, float *array[M], float average)//4
{
    float arr[M] = &array;
    float res[M];
    for(int k = 0; k < M; k++)
    {
        if(arr[k] != -1)
        {
            res[k] = arr[k] / average;
        }
        else
        {
            res[k] = -1;
        }
    }
    return &res; 
}

//generating kernel based on i,j with values contained in initial arr[256]
float* get_color(int i, int j, float *mainarr[256])//5
{
    float arr[W*H];
    arr = mainarr;
    float res[M];
    int klen = sqrt(M)-1;
    int c = 0;
    for(int k = -1; k < klen; k++)
    {
        for(int l = -1; l < klen; l++)
        {
            if(i+k >= 0 && i+k < M && j+l >= 0 && j+l < M)
            {
                res[c] = arr[(i+k)*(c/klen) + (j+l)*(c%klen)];//Might be wrong --> tried to implement (i*h +j), double dim arr to cell arr
            }
            else
            {
                res[c] = -1;
            }
            c++;
        }
    }
    return &arr; 

}

//returns the final new value of the pixel
float final_value(int i , int j, float *colorarr, float *weightarr)
{
    float warr[M] = &weightarr;
    float carr[M] = &colorarr;
    float res;
    for(int k = 0; k < M; k++)
    {
        if(warr[k] != -1 && warr[k] != -1)
        {
            res += warr[k] * carr[k];
        }
    }
    return round(res);
}

//Main function for one pixel
Uint32 blur_pixel(Uint32 pixel_color, SDL_PixelFormat* format, int i, int j, Uint32 *pixels)
{
    float warr2[M] = &set_weight(i,j);
    float warr[M] = &update_weight(i,j,&warr2, get_average(&warr));
    float* carr[M] = &get_color(i,j,&pixels);
    float res = final_value(i,j, &carr, &warr);
    Uint8 r, g, b;
    SDL_GetRGB(pixel_color, format, &r, &g, &b);
    Uint32 color = (unsigned int);
    return SDL_MapRGB(format, color, color, color);

}

void gaussian_blur(SDL_Surface* surface)
{
    Uint32* pixels = surface->pixels;
    Uint32* res[256];
    int len = surface->w * surface->h
    SDL_LockSurface(surface);
    for (int i =0; i < len; i++)
    {
        res[i] = blur_pixel(pixels[i], format, i/H, i%W, &pixels);
    }
    surface->pixels = res;
    SDL_UnlockSurface(surface);
}
