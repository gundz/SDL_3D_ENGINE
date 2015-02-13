#include <SDL.h>

SDL_Surface			*sdl_create_surface(int width, int height)
{
	SDL_Surface		*surf;

	surf = SDL_CreateRGBSurface(0, width, height, 32,
		0xFF000000,
		0x00FF0000,
		0x0000FF00,
		0x000000FF);
	return (surf);
}
