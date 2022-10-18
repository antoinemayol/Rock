#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <string.h>

#define M_PI 3.14159265358979323846
#define sigma 1.5
#define W 540 //width of the pic
#define H 480 // height of the pic
#define M 9 // width qnd length of the kernel

void generate_kernel(float ker[M], float k)
{
    for (int i =0; i < M; i++)
    {
        ker[i] = k * ker[i];
    }
}

void apply_kernel(SDL_Surface* surface)
{
    float ker[M] = {1,2,1,2,4,2,1,2,1};
    generate_kernel(ker,1/16);
    Uint32* pixels = surface->pixels;
    int len = surface->w * surface->h;
    Uint32 res[len];
    SDL_LockSurface(surface);

    int klen = sqrt(M)-1;
    for (int z = 0; z < len; z++)
    {
        Uint32 acc = 0;
        int n = 0;
        for(int k = -1; k < klen; k++)
        {
            for(int l = -1; l < klen; l++)
            {
                int i = pixels[z] / W;
                int j = pixels[z] % W;
                if((i+k) >= 0 && (i+k) < H && (i+l) >= 0 && (j+l) < W)
                {
                    acc += ker[n] * pixels[(i+k) * W + (j+l)];
                    n++;
                }
            }
        }
        res[z] = acc;
    }
    memcpy(surface->pixels, res, sizeof(Uint32)*len);
    SDL_UnlockSurface(surface);
}

