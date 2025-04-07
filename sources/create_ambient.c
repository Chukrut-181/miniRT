#include "../include/minirt.h"

int	check_rgb(char *str, t_scene *data)
{
	char **split;
	int	num1;
	int	num2;
	int	num3;

	split = ft_split(str, ',');
	if (!split)
		return (1);
	num1 = ft_atoi(split[0]);
	num2 = ft_atoi(split[1]);
	num3 = ft_atoi(split[2]);
	ft_free_array(split);
	if ((num1 > 255 || num1 < 0) || (num2 > 255 || num2 < 0) ||
	(num3 > 255 || num3 < 0))
		return (1);
	data->ambient->color.x = num1;
	data->ambient->color.y = num2;
	data->ambient->color.z = num3;
	return (0);
}

int	check_ratio(char *str, t_scene *data)
{
	float	num;

	num = ft_atof(str);
	if ((num < 0.0) || (num > 1.0))
		return (1);
	data->ambient->ratio = num;
	return (0);
}

int	create_ambient_light(t_scene *s, char **res)
{
	s->ambient = (t_ambient_light *)malloc(sizeof(t_ambient_light));
	if (!s->ambient)
		return (1);
	if (check_ratio(res[1], s) == 1)
		return (free(s->ambient), 1);
	if (check_rgb(res[2], s) == 1)
		return (free(s->ambient), 1);
	return (0);
}

