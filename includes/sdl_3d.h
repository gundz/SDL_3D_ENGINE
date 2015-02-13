#ifndef				SDL_3D_H
# define			SDL_3D_H

typedef struct		s_vector2
{
	int				x;
	int				y;
}					t_vector2;

typedef struct		s_vector3
{
	int				x;
	int				y;
	int				z;
}					t_vector3;

typedef struct		s_object
{
	int				nb_v;
	t_vector3		*v;
	t_vector2		*s;
	t_vector3		*som;
}					t_object;

float				Sin[360];
float				Cos[360];

void				setVector(float x, float y, float z, t_vector3 *vector, t_vector3 *som);

void				init_sin_cos(void);

void				rotateVector(const int xa, const int ya, const int za, t_object *object);

#endif
