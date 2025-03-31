#include "../../include/minirt.h"

void	create_camera(char *str, t_scene *s)
{
	s->camera = (s->camera *)malloc(sizeof(s->camera));
	if (s->camera == NULL)
		return ;
	
}

