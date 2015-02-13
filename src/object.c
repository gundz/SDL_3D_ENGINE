#include <libft.h>
#include <sdl_3d.h>

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>

int							openFile(char *path)
{
	int						fd;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (-1);
	return (fd);
}

t_object					*create_object(void)
{
	t_object				*object;

	if (!(object = (t_object *)malloc(sizeof(t_object))))
		return (NULL);
	return (object);
}

t_object					*load_obj(char *path)
{
	int						fd;
	char					*buf;
	t_object				*object = create_object();
	t_vector3				*tmp = NULL;

	if ((fd = openFile(path)) == -1)
		return (NULL);

	t_list					*vertex = NULL;
	while ((buf = get_next_line(fd)) != NULL)
	{
		if (buf[0] == 'v' && buf[1] == ' ')
		{
			char			**tab = ft_strsplit(buf, ' ');
			tmp = setVector3(atof(tab[1]), atof(tab[2]), atof(tab[3]));
			lst_push_back(&vertex, tmp);
			//free tab !!!!
		}
	}
	close(fd);
	object->v = vertex;
	object->nb_v = lst_count(vertex);
	if (!(object->s = (t_vector2 *)malloc(sizeof(t_vector2) * object->nb_v)))
		return (NULL);
	return (object);
}
