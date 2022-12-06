#ifndef DISPLAY_H
#define DISPLAY_H
#include <err.h>
#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>

SDL_Texture *change_board(int *board,int state,SDL_Surface *surface,SDL_Renderer *renderer);

#endif
