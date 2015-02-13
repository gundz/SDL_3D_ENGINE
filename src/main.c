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

t_vector3				camera = {0, 0, 0};

t_object				*init(void)
{
	t_object			*object;

	if (!(object = (t_object *)malloc(sizeof(t_object))))
		return (NULL);
	object->nb_v = 8;
	if (!(object->v = (t_vector3 *)malloc(sizeof(t_vector3) * object->nb_v)))
		return (NULL);
	if (!(object->som = (t_vector3 *)malloc(sizeof(t_vector3) * object->nb_v)))
		return (NULL);
	if (!(object->s = (t_vector2 *)malloc(sizeof(t_vector2) * object->nb_v)))
		return (NULL);
	setVector(-100, -100, -100, &object->v[0], &object->som[0]);
	setVector(100, -100, -100, &object->v[1], &object->som[1]);
	setVector(100, 100, -100, &object->v[2], &object->som[2]);
	setVector(-100, 100, -100, &object->v[3],  &object->som[3]);

	setVector(100, -100, 100, &object->v[4],  &object->som[4]);
	setVector(-100, -100, 100, &object->v[5],  &object->som[5]);
	setVector(-100, 100, 100, &object->v[6],  &object->som[6]);
	setVector(100, 100, 100, &object->v[7],  &object->som[7]);
	init_sin_cos();

	return (object);
}

void					projection(const t_object * const object)
{
	int					i;

	for (i = 0; i < object->nb_v; i++)
	{
		object->s[i].x = ((object->v[i].x - camera.x) * DIST) / (object->v[i].z + DZ + camera.z) + camera.x + (RX / 2);
		object->s[i].y = ((object->v[i].y - camera.y) * DIST) / (object->v[i].z + DZ + camera.z) + camera.y + (RY / 2);
	}
}

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

int turn = 0;

void					showObject(const t_object * const object)
{
	int					i;

	for (i = 0; i < object->nb_v; i++)
	{
		printf("x = %d - y = %d - z = %d\n", object->v[i].x, object->v[i].y, object->v[i].z);
	}
	printf("\n");
}

int			xa = 0;
int			ya = 0;
int			za = 0;

void					test(t_esdl *esdl, t_object *object)
{
	static SDL_Texture	*text = NULL;
	SDL_Surface			*surf = NULL;

	int					i;

	surf = sdl_create_surface(RX, RY);

	rotateVector(xa, ya, za, object);
	showObject(object);
	projection(object);
	fdf(0xFFFFFFFF, surf, object);

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

int					main(int argc, char **argv)
{
	t_esdl			esdl;

	t_object		*object;

	if (init_sdl(&esdl) == -1)
		return (-1);
	object = init();
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
