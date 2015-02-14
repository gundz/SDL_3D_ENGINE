#include <easy_sdl.h>
#include <sdl_3d.h>
#include <SDL.h>

void					dotView(SDL_Surface *surf, t_object *object, int color)
{
	int					i;

	for (i = 0; i < object->nb_v; i++) 
	{
		put_pixel(surf, object->s[i].x, object->s[i].y, color);
	}
}
