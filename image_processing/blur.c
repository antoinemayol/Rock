#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <string.h>

#define W 540 //width of the pic
#define H 480 // height of the pic

void generate_kernel(float ker[], float k, int M)
{
    for (int i =0; i < M; i++)
    {
        ker[i] = k * ker[i];
    }
}

void apply_kernel(SDL_Surface* surface, float ker[], int m, float x)
{
    //float ker[M] = {1,2,1,2,4,2,1,2,1};
    generate_kernel(ker,x, m);
    Uint32* pixels = surface->pixels;
    int len = surface->w * surface->h;
    //Uint32 res[len];
    SDL_LockSurface(surface);
    int klen = sqrt(m)-1;
    for (int z = 0; z < len; z++)
    {
        Uint8 acc = 0;
        int n = 0;
         Uint8 r,g,b;
        SDL_PixelFormat *format = surface->format;
        SDL_GetRGB(pixels[z], format, &r, &g, &b);

        for(int k = -1; k < klen; k++)
        {
            for(int l = -1; l < klen; l++)
            {
                int i = z / W;
                int j = z % W;
                if((i+k) >= 0 && (i+k) < H && (i+l) >= 0 && (j+l) < W)
                {
                    SDL_GetRGB(pixels[(i+k) * W + (j+l)], format, &r, &g, &b);
                    acc += ker[n] * r;
                    n++;
                }
            }
        }
        //printf("%d\n", acc);
        pixels[z] = SDL_MapRGB(format, acc, acc, acc);
        //res[z] = acc;
    }
    //memcpy(surface->pixels, res, sizeof(Uint32)*len);
    SDL_UnlockSurface(surface);
}

