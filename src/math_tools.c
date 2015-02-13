#include <sdl_3d.h>
#include <math.h>

void					init_sin_cos(void)
{
	int					i;

	for (i = 0; i < 360; i++)
	{
		Sin[i] = sin(i * M_PI / 180);
		Cos[i] = cos(i * M_PI / 180);
	}
}
