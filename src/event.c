#include <easy_sdl.h>
#include <sdl_3d.h>
#include <SDL.h>

void					objectRotation(t_data *data, t_object *object)
{
	if (data->esdl.en.in.key[SDL_SCANCODE_W])
	{
		rotate(&object->r.x, 3);
		rotateVector(object->r.x, object->r.y, object->r.z, object, data);
	}
	if (data->esdl.en.in.key[SDL_SCANCODE_S])
	{
		rotate(&object->r.x, -3);
		rotateVector(object->r.x, object->r.y, object->r.z, object, data);
	}

	if (data->esdl.en.in.key[SDL_SCANCODE_A])
	{
		rotate(&object->r.y, 3);
		rotateVector(object->r.x, object->r.y, object->r.z, object, data);
	}
	if (data->esdl.en.in.key[SDL_SCANCODE_D])
	{
		rotate(&object->r.y, -3);
		rotateVector(object->r.x, object->r.y, object->r.z, object, data);
	}

	if (data->esdl.en.in.key[SDL_SCANCODE_Q])
	{
		rotate(&object->r.z, 3);
		rotateVector(object->r.x, object->r.y, object->r.z, object, data);
	}
	if (data->esdl.en.in.key[SDL_SCANCODE_E])
	{
		rotate(&object->r.z, -3);
		rotateVector(object->r.x, object->r.y, object->r.z, object, data);
	}
}

void					cameraTranslation(t_data *data, t_esdl *esdl)
{
	if (esdl->en.in.key[SDL_SCANCODE_KP_PLUS])
		data->c.z += 1;
	if (esdl->en.in.key[SDL_SCANCODE_KP_MINUS])
		data->c.z -= 1;
	if (esdl->en.in.key[SDL_SCANCODE_UP])
		data->c.y -= 1;
	if (esdl->en.in.key[SDL_SCANCODE_DOWN])
		data->c.y += 1;
	if (esdl->en.in.key[SDL_SCANCODE_LEFT])
		data->c.x -= 1;
	if (esdl->en.in.key[SDL_SCANCODE_RIGHT])
		data->c.x += 1;
}

void					toggleView(t_data *data, t_esdl *esdl)
{
	if (esdl->en.in.key[SDL_SCANCODE_V])
	{
		esdl->en.in.key[SDL_SCANCODE_V] = 0;
		data->view += 1;
	}
}
