#include <lst.h>
#include <easy_sdl.h>
#include <sdl_3d.h>
#include <SDL.h>

void					line(const int a, const int b, SDL_Surface *surf, t_object *object, const int color)
{
	SDL_Rect			rect;

	rect.x = object->s[a].x;
	rect.y = object->s[a].y;
	rect.w = object->s[b].x;
	rect.h = object->s[b].y;
	draw_line(surf, rect, color);
}

void					wireframeView(SDL_Surface *surf, t_object *object, const int color)
{
	int					i;

	for (i = 0; i < object->nb_f; i++)
	{
		line(object->f[i]->x - 1, object->f[i]->y - 1, surf, object, color);
		line(object->f[i]->y - 1, object->f[i]->z - 1, surf, object, color);
		if (object->f[i]->xs != -1)
		{
			line(object->f[i]->z - 1, object->f[i]->xs - 1, surf, object, color);
			line(object->f[i]->xs - 1, object->f[i]->x - 1, surf, object, color);
		}
		else
			line(object->f[i]->z - 1, object->f[i]->x - 1, surf, object, color);
	}
}
