#ifndef ROTATION_H
#define DEFINE_H

Uint32  SDL_LirePixel(SDL_Surface* surface,int x,int y);
void  SDL_EcrirePixel(SDL_Surface* surface,int x, int y, Uint32 pixel);
SDL_Surface* SDL_RotationCentrala(SDL_Surface* origine,float angle);
int princip(char* argv, float angle);
char *name_filled(char *img_name);
SDL_Surface *load_image1(const char* path);

#endif
