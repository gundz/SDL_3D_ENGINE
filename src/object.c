#include <libft.h>
#include <sdl_3d.h>

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>

int				openFile(char *path)
{
	int			fd;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (-1);
	return (fd);
}

t_object			*create_object(void)
{
	t_object		*object;

	if (!(object = (t_object *)malloc(sizeof(t_object))))
		return (NULL);
	return (object);
}

void				store_vertex(t_list *lst, t_object *object)
{
	t_vector3		*vertex;
	t_list			*lstWalker;
	int			i;

	object->nb_v = lst_count(lst);
	if (!(object->v = (t_vector3 **)malloc(sizeof(t_vector3 *) * object->nb_v)))
		return ;
	i = 0;
	lstWalker = lst;
	while (lstWalker != NULL)
	{
		vertex = lstWalker->data;
		object->v[i++] = vertex;
		if (lstWalker->next == NULL)
			break ;
		lstWalker = lstWalker->next;
	}
	//free_lst
}

void				store_faces(t_list *lst, t_object *object)
{
	t_vector3d		*face;
	t_list			*lstWalker;
	int			i;

	object->nb_f = lst_count(lst);
	if (!(object->f = (t_vector3d **)malloc(sizeof(t_vector3d *) * object->nb_f)))
		return ;
	i = 0;
	lstWalker = lst;
	while (lstWalker != NULL)
	{
		face = lstWalker->data;
		object->f[i++] = face;
		if (lstWalker->next == NULL)
			break ;
		lstWalker = lstWalker->next;
	}
	//free_lst
}

t_object			*load_obj(char *path)
{
	int			fd;
	char			*buf;
	t_object		*object = create_object();
	t_vector3		*tmp;
	t_vector3d		*tmp2;
	char			**tab;

	if ((fd = openFile(path)) == -1)
		return (NULL);

	t_list					*vertex = NULL;
	t_list					*faces = NULL;
	while ((buf = get_next_line(fd)) != NULL)
	{
		if (buf[0] == 'v' && buf[1] == ' ')
		{
			tab = ft_strsplit(buf, ' ');
			tmp = setVector3(atof(tab[1]), atof(tab[2]), atof(tab[3]));
			lst_push_back(&vertex, tmp);
			ft_freectab(tab);
		}
		else if (buf[0] == 'f' && buf[1] == ' ')
		{
			tab = ft_strsplit(buf, ' ');
			tmp2 = setVector3d(atoi(tab[1]), atoi(tab[2]), atoi(tab[3]));
			if (ft_ctablen((const char **)tab) == 5)
				tmp2->xs = atoi(tab[4]);
			else
				tmp2->xs = -1;
			lst_push_back(&faces, tmp2);
			ft_freectab(tab);
		}
	}
	close(fd);
	store_vertex(vertex, object);
	store_faces(faces, object);
	if (!(object->s = (t_vector2 *)malloc(sizeof(t_vector2) * object->nb_v)))
		return (NULL);
	printf("File loaded !\nVertex : %d Faces : %d\n", object->nb_v, object->nb_f);
	return (object);
}
