#include <easy_sdl.h>

#include <stdio.h>

void			fps_counter(t_esdl *esdl)
{
	if ((esdl->fps.update = SDL_GetTicks()) - esdl->fps.current >= 1000)
	{
		esdl->fps.current = esdl->fps.update;
		sprintf(esdl->fps.title, "%d fps", esdl->fps.fps);
		SDL_SetWindowTitle(esdl->en.win, esdl->fps.title);
		esdl->fps.fps = 0;
	}
	esdl->fps.fps++;
}
