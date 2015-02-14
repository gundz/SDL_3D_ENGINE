#include <easy_sdl.h>
#include <SDL.h>

#include <sdl_3d.h>
#include <stdlib.h>

void					test(t_esdl *esdl, t_data *data)
{
	data->surf = sdl_create_surface(RX, RY);

	rotateVector(data->o->r.x, data->o->r.y, data->o->r.z, data->o, data);
	projection(&data->c, data->o);

	if (data->view % 2 == 0)
		wireframeView(data->surf, data->o, 0xFFFFFFFF);
	else if (data->view % 1 == 0)
		dotView(data->surf, data->o, 0xFFFFFFFF);

	objectRotation(esdl, data->o);
	cameraTranslation(data, esdl);
	toggleView(data, esdl);

	data->text = SDL_CreateTextureFromSurface(esdl->en.ren, data->surf);
	SDL_RenderClear(esdl->en.ren);
	SDL_RenderCopy(esdl->en.ren, data->text, NULL, NULL);
	SDL_RenderPresent(esdl->en.ren);
	SDL_FreeSurface(data->surf);
	SDL_DestroyTexture(data->text);
}

void					init(t_data *data)
{
	init_sin_cos(data->Sin, data->Cos);
	data->c.x = 0;
	data->c.y = 0;
	data->c.z = 100;
	data->view = 0;
}

int						main(int argc, char **argv)
{
	t_data				data;
	t_esdl				esdl;

	if (argc != 2)
	{
		printf("Usage : file.obj\n");
		return (0);
	}
	init(&data);
	if ((data.o = load_obj(argv[1])) == NULL)
	{
		printf("Error while loading file !\n");
		return (-1);
	}
	if (init_sdl(&esdl) == -1)
		return (-1);
	while (!esdl.en.in.key[SDL_SCANCODE_ESCAPE])
	{
		update_events(&esdl.en.in);
		fps_counter(&esdl);
		test(&esdl, &data);
	}
	return (0);
}
