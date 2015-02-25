#include <lst.h>
#include <easy_sdl.h>
#include <sdl_3d.h>
#include <SDL.h>

#include <limits.h>

void
line(const int a, const int b, SDL_Surface *surf, t_object *object, const int color)
{
	SDL_Rect		rect;

	rect.x = object->s[a].x;
	rect.y = object->s[a].y;
	rect.w = object->s[b].x;
	rect.h = object->s[b].y;
	draw_line(surf, rect, color);
}

t_vector3
convert2dto3(t_vector2 vector)
{
	t_vector3	ret;

	ret.x = vector.x;
	ret.y = vector.y;
	return (ret);
}

void
scanLine(t_vector3 v1, t_vector3 v2, int contourX[RY][2])
{
	t_vector3			s;
	t_vector3			d1;
	t_vector3			d2;
	int				x;
	int				y;
	int				m;
	int				n;
	int				k;
	int				cnt;

	s.x = v2.x - v1.x;
	s.y = v2.y - v1.y;

	d1.x = 0;
	x = 0;

	if (s.x > 0)
		d1.x = 1;
	else if (s.x < 0)
		d1.x = -1;
	else
		d1.y = 0;

	if (s.y > 0)
		d1.y = 1;
	else if (s.y < 0)
		d1.y = -1;
	else
		d1.y = 0;

	m = abs(s.x);
	n = abs(s.y);
	d2.x = d1.x;
	d2.y = 0;

	if (m < n)
	{
		m = abs(s.y);
		n = abs(s.x);
		d2.x = 0;
		d2.y = d1.y;
	}
	x = v1.x;
	y = v1.y;
	cnt = m + 1;
	k = n / 2;

	while (cnt--)
	{
		if ((y >= 0) && (y < RY))
		{
			if (x < contourX[y][0])
				contourX[y][0] = x;
			if (x > contourX[y][1])
				contourX[y][1] = x;
		}
		k += n;
		if (k < m)
		{
			x += d2.x;
			y += d2.y;
		}
		else
		{
			k -= m;
			x += d1.x;
			y += d1.y;
		}
	}
}

void
polygonView(int ax, int bx, int cx, t_object *object, SDL_Surface *surf)
{
	t_vector3				v1 = convert2dto3(object->s[ax]);
	t_vector3				v2 = convert2dto3(object->s[bx]);
	t_vector3				v3 = convert2dto3(object->s[cx]);
	int					contourX[RY][2];
	int					y;
	int					x;
	int					len;

	for (y = 0; y < RY; y++)
	{
		contourX[y][0] = INT_MAX;
		contourX[y][1] = INT_MIN;
	}

	scanLine(v1, v2, contourX);
	scanLine(v2, v3, contourX);
	scanLine(v3, v1, contourX);

	for (y = 0; y < RY; y++)
	{
		if (contourX[y][1] >= contourX[y][0])
		{
			x = contourX[y][0];
			len = 1 + contourX[y][1] - contourX[y][0];
			while (len--)
				put_pixel(surf, x++, y, 0xFF00FFFF);
		}
	}
}

void
wireframeView(SDL_Surface *surf, t_object *object, const int color)
{
	int			i;

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
		{
			line(object->f[i]->z - 1, object->f[i]->x - 1, surf, object, color);
			polygonView(object->f[i]->x - 1, object->f[i]->y - 1, object->f[i]->z - 1, object, surf);
		}
	}
}
