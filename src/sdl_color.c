#include <easy_sdl.h>
SDL_Color					sdl_int_to_color(int color)
{
	SDL_Color				ret_color;

	ret_color.r = (color >> 24) & 0xFF;
	ret_color.g = (color >> 16) & 0xFF;
	ret_color.b = (color >> 8) & 0xFF;
	ret_color.a = (color) & 0xFF;
	return (ret_color);
}

int							sdl_color_to_int(SDL_Color color)
{
	int						ret_color;

	ret_color = 0;
	ret_color = (ret_color << 8) + color.r;
	ret_color = (ret_color << 8) + color.g;
	ret_color = (ret_color << 8) + color.b;
	ret_color = (ret_color << 8) + color.a;
	return (ret_color);
}
