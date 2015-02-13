#include <easy_sdl.h>
#include <SDL.h>

int				ft_abs(int num)
{
	if (num < 0)
		return (-num);
	return (num);
}

void			put_pixel(SDL_Surface *const surf, const int x, const int y, const int color)
{
	int			bpp;
	Uint32		*p;

	if ((x >= 0 && y >= 0) && (x < RX && y < RY))
	{
		SDL_LockSurface(surf);
		bpp = surf->format->BytesPerPixel;
		p = surf->pixels + y * surf->pitch + x * bpp;
		*(Uint32 *)p = color;
		SDL_UnlockSurface(surf);
	}
}

void			draw_line(SDL_Surface *surf, SDL_Rect rect, const int color)
{
	t_pt		d;
	t_pt		s;
	int			err;
	int			e2;

	d.x = ft_abs(rect.w - rect.x);
	d.y = ft_abs(rect.h - rect.y);
	s.x = (rect.x < rect.w ? 1 : -1);
	s.y = (rect.y < rect.h ? 1 : -1);
	err = d.x - d.y;
	while (rect.x != rect.w || rect.y != rect.h)
	{
		put_pixel(surf, rect.x, rect.y, color);
		if ((e2 = 2 * err) > -d.y)
			err -= (d.y + 0 * (rect.x += s.x));
		if (rect.x == rect.w && rect.y == rect.h)
		{
			put_pixel(surf, rect.x, rect.y, color);
			return ;
		}
		if (e2 < d.x)
			err += (d.x + 0 * (rect.y += s.y));
	}
}

void		draw_square(SDL_Surface *surf, const SDL_Rect rect, const int color)
{
	int		x;
	int		y;

	x = y = 0;
	while (y < rect.h)
	{
		x = 0;
		while (x < rect.w)
		{
			put_pixel(surf, x + rect.x, y + rect.y, color);
			x++;
		}
		y++;
	}
}

void		clear_screen(SDL_Surface *surf, const int color)
{
	int		x;
	int		y;

	y = 0;
	while (y < surf->h)
	{
		x = 0;
		while (x < surf->w)
		{
			put_pixel(surf, x, y, color);
			x++;
		}
		y++;
	}
}
