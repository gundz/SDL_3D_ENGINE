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
	t_list				*lstWalker;
	t_vector3			*f;

	lstWalker = object->f;
	while (lstWalker != NULL)
	{
		f = lstWalker->data;
		line(f->x - 1, f->y - 1, surf, object, color);
		line(f->y - 1, f->z - 1, surf, object, color);
		line(f->z - 1, f->x - 1, surf, object, color);
		if (lstWalker->next == NULL)
			break ;
		lstWalker = lstWalker->next;
	}
}
