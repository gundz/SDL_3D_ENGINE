#ifndef				SDL_3D_H
# define			SDL_3D_H

#include <lst.h>

typedef struct		s_vector2
{
	int				x;
	int				y;
}					t_vector2;

typedef struct		s_vector3
{
	float			x;
	float			y;
	float			z;
	float			xs;
	float			ys;
	float			zs;
}					t_vector3;

typedef struct		s_object
{
	int				nb_v;
	t_list			*v;	
	t_list			*som;
	t_vector2		*s;
}					t_object;

float				Sin[360];
float				Cos[360];

t_vector3			*setVector3(float x, float y, float z);

void				init_sin_cos(void);

void				rotateVector(const int xa, const int ya, const int za, t_object *object);

t_object			*load_obj(char *path);

//La fleme d'en faire un
char				*get_next_line(const int fd);

#endif
