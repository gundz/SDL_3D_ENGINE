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

t_vector3d				*setVector3d(int x, int y, int z)
{
	t_vector3d			*vector;

	if (!(vector = (t_vector3d *)malloc(sizeof(t_vector3d))))
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
	int					i;

	i = 0;
	for (i = 0; i < object->nb_v; i++)
	{
		object->s[i].x = ((object->v[i]->x - camera->x) * (object->v[i]->z - camera->z)) + camera->x + (RX / 2);
		object->s[i].y = ((object->v[i]->y - camera->y) * (object->v[i]->z - camera->z)) + camera->y + (RY / 2);
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
	float				matrice[3][3];
	int					i;

	matrice[0][0] = data->Cos[za] * data->Cos[ya];
	matrice[1][0] = data->Sin[za] * data->Cos[ya];
	matrice[2][0] = -data->Sin[ya];

	matrice[0][1] = data->Cos[za] * data->Sin[ya] * data->Sin[xa] - data->Sin[za] * data->Cos[xa];
	matrice[1][1] = data->Sin[za] * data->Sin[ya] * data->Sin[xa] + data->Cos[xa] * data->Cos[za];
	matrice[2][1] = data->Sin[xa] * data->Cos[ya];

	matrice[0][2] = data->Cos[za] * data->Sin[ya] * data->Cos[xa] + data->Sin[za] * data->Sin[xa];
	matrice[1][2] = data->Sin[za] * data->Sin[ya] * data->Cos[xa] - data->Cos[za] * data->Sin[xa];
	matrice[2][2] = data->Cos[xa] * data->Cos[ya];

	for (i = 0; i < object->nb_v; i++)
	{
		object->v[i]->x =
			matrice[0][0] * object->v[i]->xs
			+ matrice[1][0] * object->v[i]->ys
			+ matrice[2][0] * object->v[i]->zs;
		object->v[i]->y =
			matrice[0][1] * object->v[i]->xs
			+ matrice[1][1] * object->v[i]->ys
			+ matrice[2][1] * object->v[i]->zs;

		object->v[i]->z =
			matrice[0][2] * object->v[i]->xs
			+ matrice[1][2] * object->v[i]->ys
			+ matrice[2][2] * object->v[i]->zs;
	}
}
