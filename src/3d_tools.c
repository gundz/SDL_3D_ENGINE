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

void					rotateVector(const int xa, const int ya, const int za, t_object *object)
{
	t_list				*lstWalker;
	t_vector3			*v;
	float				matrice[3][3];

	matrice[0][0] = Cos[za] * Cos[ya];
	matrice[1][0] = Sin[za] * Cos[ya];
	matrice[2][0] = -Sin[ya];

	matrice[0][1] = Cos[za] * Sin[ya] * Sin[xa] - Sin[za] * Cos[xa];
	matrice[1][1] = Sin[za] * Sin[ya] * Sin[xa] + Cos[xa] * Cos[za];
	matrice[2][1] = Sin[xa] * Cos[ya];

	matrice[0][2] = Cos[za] * Sin[ya] * Cos[xa] + Sin[za] * Sin[xa];
	matrice[1][2] = Sin[za] * Sin[ya] * Cos[xa] - Cos[za] * Sin[xa];
	matrice[2][2] = Cos[xa] * Cos[ya];

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
