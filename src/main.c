#include <easy_sdl.h>
#include <SDL.h>

#include <sdl_3d.h>
#include <stdlib.h>

void					main_3D(t_data *data)
{
	data->surf = sdl_create_surface(RX, RY);

	projection(&data->c, data->o);

	if (data->view % 2 == 0)
		wireframeView(data->surf, data->o, 0xFFFFFFFF);
	else if (data->view % 1 == 0)
		dotView(data->surf, data->o, 0xFFFFFFFF);

	objectRotation(data, data->o);
	cameraTranslation(data);
	toggleView(data);

	data->text = SDL_CreateTextureFromSurface(data->esdl.en.ren, data->surf);
	SDL_RenderClear(data->esdl.en.ren);
	SDL_RenderCopy(data->esdl.en.ren, data->text, NULL, NULL);
	SDL_RenderPresent(data->esdl.en.ren);
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
	if (init_sdl(&data.esdl) == -1)
		return (-1);
	while (!data.esdl.en.in.key[SDL_SCANCODE_ESCAPE])
	{
		update_events(&data.esdl.en.in);
		fps_counter(&data.esdl);
		main_3D(&data);
	}
	return (0);
}
