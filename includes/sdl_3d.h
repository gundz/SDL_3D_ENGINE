#ifndef				SDL_3D_H
# define			SDL_3D_H

#include <lst.h>
#include <easy_sdl.h>
#include <SDL.h>

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

typedef struct		s_vector3d
{
	int				x;
	int				y;
	int				z;
}					t_vector3d;

typedef struct		s_object
{
	int				nb_v; //number of vertex
	t_list			*v;	//vertex list
	t_list			*som; //raw vertex list
	int				nb_f; //number of faces
	t_list			*f; //faces list
	t_vector2		*s; //2D projection
	t_vector3d		r; //Rotation value
}					t_object;

typedef struct		s_data
{
	t_esdl			esdl;
	float			Sin[360]; //Pre computed Sin
	float			Cos[360]; //Pre computed Cos
	SDL_Texture		*text; //SDL Texture
	SDL_Surface		*surf; // SDL Surface
	t_object		*o; // Object
	t_vector3		c; // camera
	int				view;
}					t_data;

//GLOBAL

//INIT

void				init_sin_cos(float *Sin, float *Cos);

//Vector

t_vector3			*setVector3(float x, float y, float z);

void				rotate(int *coor, int value);
void				rotateVector(const int xa, const int ya, const int za, t_object *object, t_data *data);

//VIEWS

void				projection(const t_vector3 *const camera, const t_object *const object);
void				wireframeView(SDL_Surface *surf, t_object *object, int color);
void				dotView(SDL_Surface *surf, t_object *objec, int color);

//OBJECTS

t_object			*load_obj(char *path);

//EVENTS
void				objectRotation(t_data *data, t_object *object);
void				cameraTranslation(t_data *data, t_esdl *esdl);
void				toggleView(t_data *data, t_esdl *esdl);

//La fleme d'en faire un
char				*get_next_line(const int fd);

#endif
