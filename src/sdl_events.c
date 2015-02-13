#include <easy_sdl.h>

#include <SDL.h>

#include <stdlib.h>

void                update_events(t_input *in)
{
 	SDL_Event event;

	SDL_GetMouseState(&in->m_x, &in->m_y);
	SDL_GetRelativeMouseState(&in->m_r_x, &in->m_r_y);
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			in->key[event.key.keysym.scancode] = 1;
			break ;
		}
		else if (event.type == SDL_KEYUP)
		{
			in->key[event.key.keysym.scancode] = 0;
			break ;
		}
		else if (event.type == SDL_QUIT)
			 exit (0);
	} 
}
