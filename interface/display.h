#ifndef DISPLAY_H
#define DISPLAY_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



SDL_Texture *change_board(int *board,int state,SDL_Surface *surface,SDL_Renderer *renderer);
void New_img(int *grille);

#endif
