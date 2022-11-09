
#include <math.h>
#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



/*permet de déterminer la valeur d'un pixel au position x,y*/
Uint32  SDL_LirePixel(SDL_Surface* surface, int x, int y)
{
  int bpp = surface->format->BytesPerPixel;
 
  Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
 
  switch(bpp)
  {
  		case 1:
        	return *p;
        case 2:
            return *(Uint16 *)p;
        case 3:
           	if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            	return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
        case 4: 
            return *(Uint32 *)p;
       	default:
        	return 0;
  } 
 
}
 
 
/*permet d'écrire un pixel au position x,y*/
void SDL_EcrirePixel(SDL_Surface* surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel; 
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp; 
 
 
    switch(bpp) 
	{ 
    	case 1: 
        	*p = pixel; 
        	break; 
 
    	case 2: 
        	*(Uint16 *)p = pixel; 
        	break; 
 
    	case 3: 
        	if(SDL_BYTEORDER == SDL_BIG_ENDIAN) 
			{ 
            	p[0] = (pixel >> 16) & 0xff; 
            	p[1] = (pixel >> 8) & 0xff; 
            	p[2] = pixel & 0xff; 
        	} 
			else 
			{ 
            p[0] = pixel & 0xff; 
            p[1] = (pixel >> 8) & 0xff; 
            p[2] = (pixel >> 16) & 0xff; 
        	} 
        	break; 
 
    	case 4: 
        	*(Uint32 *)p = pixel; 
        	break; 
    	}  
 
}
 
/*Proceed the rotation from an angle in degree, automatically allocate memory*/
SDL_Surface* SDL_RotationCentrala(SDL_Surface* origine, float angle)
{
	SDL_Surface* destination;
	int i;
	int j;
	Uint32 couleur;
	int mx, my;

	int bx, by;
	float angle_radian;

	/* Determine value of angle in radian */
	angle_radian = -angle * M_PI / 180.0;

	/* 
	 * Allocate memory to the destination, warning, 
	 * the surface has the same size
	 */
	destination = SDL_CreateRGBSurface(SDL_SWSURFACE, origine->w, origine->h, origine->format->BitsPerPixel,
					origine->format->Rmask, origine->format->Gmask, origine->format->Bmask, origine->format->Amask);

	/*We verify that memory has been allocated*/
	if(destination==NULL)
		return NULL;

	/*To simplify notation*/
	mx = origine->w/2;
	my = origine->h/2;

	for(j=0;j<origine->h;j++)
		for(i=0;i<origine->w;i++)
		{
			/* We determine pixel value that fit better to the position i, j*/

			/*We determine the best position on the origin surface by applying
			* an inverse rotation matrix
			*/

			bx = (int) (cos(angle_radian) * (i-mx) + sin(angle_radian) * (j-my)) + mx;
			by = (int) (-sin(angle_radian) * (i-mx) + cos(angle_radian) * (j-my)) + my;

			/* We verify that we don't get out of bounds*/

			if (bx>=0 && bx< origine->w && by>=0 && by< origine->h)
			{
				couleur = SDL_LirePixel(origine, bx, by);
				SDL_EcrirePixel(destination, i, j, couleur);
			}
		}
	return destination;
}
