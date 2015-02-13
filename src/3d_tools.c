#include <sdl_3d.h>
#include <stddef.h>

void					setVector(float x, float y, float z, t_vector3 *vector, t_vector3 *som)
{
	vector->x = x;
	vector->y = y;
	vector->z = z;

	if (som != NULL)
	{
		som->x = x;
		som->y = y;
		som->z = z;
	}
}

void					rotateVector(const int xa, const int ya, const int za, t_object *object)
{
	int					i;
	float				matrice[3][3];
	t_vector3			tmp;

	matrice[0][0] = Cos[za] * Cos[ya];
	matrice[1][0] = Sin[za] * Cos[ya];
	matrice[2][0] = -Sin[ya];

	matrice[0][1] = Cos[za] * Sin[ya] * Sin[xa] - Sin[za] * Cos[xa];
	matrice[1][1] = Sin[za] * Sin[ya] * Sin[xa] + Cos[xa] * Cos[za];
	matrice[2][1] = Sin[xa] * Cos[ya];

	matrice[0][2] = Cos[za] * Sin[ya] * Cos[xa] + Sin[za] * Sin[xa];
	matrice[1][2] = Sin[za] * Sin[ya] * Cos[xa] - Cos[za] * Sin[xa];
	matrice[2][2] = Cos[xa] * Cos[ya];

	for (i = 0; i < object->nb_v; i++)
	{
		object->v[i].x =
			matrice[0][0] * object->som[i].x
			+ matrice[1][0] * object->som[i].y
			+ matrice[2][0] * object->som[i].z;

		object->v[i].y =
			matrice[0][1] * object->som[i].x
			+ matrice[1][1] * object->som[i].y
			+ matrice[2][1] * object->som[i].z;

		object->v[i].z =
			matrice[0][2] * object->som[i].x
			+ matrice[1][2] * object->som[i].y
			+ matrice[2][2] * object->som[i].z;
	}
}
