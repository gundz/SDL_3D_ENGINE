#include <sdl_3d.h>

#include <stdlib.h>

#include <stddef.h>

t_vector3				*setVector3(float x, float y, float z)
{
	t_vector3			*vector;

	if (!(vector = (t_vector3 *)malloc(sizeof(t_vector3))))
		return (NULL);
	vector->x = x;
	vector->y = y;
	vector->z = z;
	vector->xs = x;
	vector->ys = y;
	vector->zs = z;
	return (vector);
}

void					projection(const t_vector3 *const camera, const t_object *const object)
{
	t_list				*lstWalker;
	t_vector3			*v;
	int					i;

	i = 0;
	lstWalker = object->v;
	while (lstWalker != NULL)
	{
		v = lstWalker->data;
		object->s[i].x = ((v->x - camera->x) * (v->z - camera->z)) + camera->x + (RX / 2);
		object->s[i].y = ((v->y - camera->y) * (v->z - camera->z)) + camera->y + (RY / 2);
		i++;
		if (lstWalker->next == NULL)
			break ;
		lstWalker = lstWalker->next;
	}
}

void					rotate(int *coor, int value)
{
	if (*coor + value <= 0)
		*coor = 360 + value;
	else
		*coor = (*coor + value) % 360;
}

void					rotateVector(const int xa, const int ya, const int za, t_object *object, t_data *data)
{
	t_list				*lstWalker;
	t_vector3			*v;
	float				matrice[3][3];

	matrice[0][0] = data->Cos[za] * data->Cos[ya];
	matrice[1][0] = data->Sin[za] * data->Cos[ya];
	matrice[2][0] = -data->Sin[ya];

	matrice[0][1] = data->Cos[za] * data->Sin[ya] * data->Sin[xa] - data->Sin[za] * data->Cos[xa];
	matrice[1][1] = data->Sin[za] * data->Sin[ya] * data->Sin[xa] + data->Cos[xa] * data->Cos[za];
	matrice[2][1] = data->Sin[xa] * data->Cos[ya];

	matrice[0][2] = data->Cos[za] * data->Sin[ya] * data->Cos[xa] + data->Sin[za] * data->Sin[xa];
	matrice[1][2] = data->Sin[za] * data->Sin[ya] * data->Cos[xa] - data->Cos[za] * data->Sin[xa];
	matrice[2][2] = data->Cos[xa] * data->Cos[ya];

	lstWalker = object->v;
	while (lstWalker != NULL)
	{
		v = lstWalker->data;
		v->x =
			matrice[0][0] * v->xs
			+ matrice[1][0] * v->ys
			+ matrice[2][0] * v->zs;
		v->y =
			matrice[0][1] * v->xs
			+ matrice[1][1] * v->ys
			+ matrice[2][1] * v->zs;

		v->z =
			matrice[0][2] * v->xs
			+ matrice[1][2] * v->ys
			+ matrice[2][2] * v->zs;

		if (lstWalker->next == NULL)
			break ;
		lstWalker = lstWalker->next;
	}
}
