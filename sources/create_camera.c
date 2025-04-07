#include "../include/minirt.h"

static int	check_vector(char *str, t_scene *data)
{
	char	**split;
	float	num1;
	float	num2;
	float	num3;

	split = ft_split(str, ',');
	if (!split)
		return (1);
	num1 = ft_atof(split[0]);
	num2 = ft_atof(split[1]);
	num3 = ft_atof(split[2]);
	ft_free_array(split);
	if ((num1 > 1 || num1 < -1) || (num2 > 1 || num2 < -1) || (num3 > 1 || num3 < -1))
		return (1);
	data->camera->v_orientation.x = num1;
	data->camera->v_orientation.y = num2;
	data->camera->v_orientation.z = num3;
	return (0);
}

static int	check_viewpoint(char *str, t_scene *data)
{
	char	**split;
	float	num1;
	float	num2;
	float	num3;

	split = ft_split(str, ',');
	if (!split)
		return (1);
	num1 = ft_atof(split[0]);
	num2 = ft_atof(split[1]);
	num3 = ft_atof(split[2]);
	data->camera->origin_point = ft_create_point(num1, num2, num3);
	return (0);
}

int	create_camera(char **str, t_scene *s)
{
	float	fov;
	t_tuple	up;
	t_tuple	to;

	s->camera = (t_camera *) malloc(sizeof(t_camera));
	if (s->camera == NULL)
		return (free(s->camera), 1);
	if (check_viewpoint(str[1], s) == 1)
		return (free(s->camera), 1);
	if (check_vector(str[2], s) == 1)
		return (free(s->camera), 1);
	fov = ft_atof(str[3]);
	if (fov <= 0 || fov >= 180)
	{
		free(s->camera);
		s->camera = NULL;
		return (1);
	}
	// lo necesito en radianes
	s->camera->field_of_view = fov * M_PI / 180.0;

	to = ft_add_tuples(s->camera->origin_point, s->camera->v_orientation);

	if (fabs(s->camera->v_orientation.y) > 0.99)
		up = ft_create_vector(0, 0, 1);
	else
		up = ft_create_vector(0, 1, 0);

	s->camera->transform = view_transform(s->camera->origin_point, to, up);
	return (0);
}

