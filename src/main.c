#include <easy_sdl.h>
#include <SDL.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <sdl_3d.h>
#include <stdlib.h>

#define DIST			1000
#define ZMIN			500
#define ZMAX			-500
#define DZ				ZMAX - ZMIN

t_vector3				camera = {0, 0, 0, 0, 0, 0};
int						turn = 0;

void					projection(const t_object * const object)
{
	t_list				*lstWalker;
	t_vector3			*v;
	int					i;

	i = 0;
	lstWalker = object->v;
	while (lstWalker != NULL)
	{
		v = lstWalker->data;
		object->s[i].x = ((v->x - camera.x) * DIST) / (v->z + DZ + camera.z) + camera.x + (RX / 2);
		object->s[i].y = ((v->y - camera.y) * DIST) / (v->z + DZ + camera.z) + camera.y + (RY / 2);
		i++;
		if (lstWalker->next == NULL)
			break ;
		lstWalker = lstWalker->next;
	}
}
/*
void					ligne(int a, int b, int color, SDL_Surface *surf, t_object *object)
{
	SDL_Rect			rect;

	rect.x = object->s[a].x;
	rect.y = object->s[a].y;
	rect.w = object->s[b].x;
	rect.h = object->s[b].y;
	draw_line(surf, rect, color);
}

void					fdf(int color, SDL_Surface *surf, t_object *object)
{
	ligne(0, 1, color, surf, object);
	ligne(1, 2, color, surf, object);
	ligne(2, 3, color, surf, object);
	ligne(3, 0, color, surf, object);

	ligne(4, 5, color, surf, object);
	ligne(5, 6, color, surf, object);
	ligne(6, 7, color, surf, object);
	ligne(7, 4, color, surf, object);

	ligne(0, 5, color, surf, object);
	ligne(1, 4, color, surf, object);
	ligne(2, 7, color, surf, object);
	ligne(3, 6, color, surf, object);
}
*/

void					showDot(SDL_Surface *surf, t_object *object)
{
	int					i;

	for (i = 0; i < object->nb_v; i++) 
	{
		put_pixel(surf, object->s[i].x, object->s[i].y, 0xFFFFFFFF);
	}
}

int			xa = 0;
int			ya = 0;
int			za = 0;

void					test(t_esdl *esdl, t_object *object)
{
	static SDL_Texture	*text = NULL;
	SDL_Surface			*surf = NULL;

	surf = sdl_create_surface(RX, RY);

	rotateVector(xa, ya, za, object);
	projection(object);
//	fdf(0xFFFFFFFF, surf, object);
	showDot(surf, object);

	text = SDL_CreateTextureFromSurface(esdl->en.ren, surf);

	if (esdl->en.in.key[SDL_SCANCODE_D])
		ya = (ya + 3) % 360;
	if (esdl->en.in.key[SDL_SCANCODE_A])
	{
		if (ya - 3 <= 0)
			ya = 360 + ya;
		ya = (ya - 3) % 360;
	}

	if (esdl->en.in.key[SDL_SCANCODE_S])
		xa = (xa + 3) % 360;
	if (esdl->en.in.key[SDL_SCANCODE_W])
	{
		if (xa - 3 <= 0)
			xa = 360 + xa;
		xa = (xa - 3) % 360;
	}	
	
	if (esdl->en.in.key[SDL_SCANCODE_Q])
		za = (za + 3) % 360;
	if (esdl->en.in.key[SDL_SCANCODE_E])
	{
		if (za - 3 <= 0)
			za = 360 + za;
		za = (za - 3) % 360;
	}

	if (esdl->en.in.key[SDL_SCANCODE_UP])
		camera.z += 10;
	if (esdl->en.in.key[SDL_SCANCODE_DOWN])
		camera.z -= 10;

	if (esdl->en.in.key[SDL_SCANCODE_T])
	{
		if (turn == 1)
			turn = 0;
		else
			turn = 1;
		esdl->en.in.key[SDL_SCANCODE_T] = 0;
	}

	if (turn == 1)
	{
		ya = (ya + 3) % 360;
		xa = (xa + 1) % 360;
		za = (za + 1) % 360;
	}

	SDL_RenderClear(esdl->en.ren);
	SDL_RenderCopy(esdl->en.ren, text, NULL, NULL);
	SDL_RenderPresent(esdl->en.ren);
	SDL_FreeSurface(surf);
	SDL_DestroyTexture(text);
}

void				show(t_object *object, int details)
{
	t_list				*lstWalker;
	t_vector3			*v;

	if (details == 1)
	{
		lstWalker = object->v;
		while (lstWalker != NULL)
		{
			v = lstWalker->data;
			printf("x = %f - y = %f - z = %f\n", v->x, v->y, v->z);
			if (lstWalker->next == NULL)
				break ;
			lstWalker = lstWalker->next;
		}
	}
	printf("File loaded !\n");
	printf("vertex : %d\n", object->nb_v);
	printf("camera : %f | %f\n", camera.x, camera.y);
	printf("\n\n");
}

int					main(int argc, char **argv)
{
	t_esdl			esdl;

	t_object		*object;

	if (init_sdl(&esdl) == -1)
		return (-1);
	init_sin_cos();
	object = load_obj("ressources/LEGO_Man.obj");
	show(object, 0);
	while (!esdl.en.in.key[SDL_SCANCODE_ESCAPE])
	{
		update_events(&esdl.en.in);
		fps_counter(&esdl);
		test(&esdl, object);
	}
	(void)argc;
	(void)argv;
	return (0);
}
