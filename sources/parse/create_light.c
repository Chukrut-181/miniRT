#include "../../include/minirt.h"

static int	check_origin_point(char *str, t_scene *data)
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
	data->light->position.x = num1;
	data->light->position.y = num2;
	data->light->position.z = num3;
	return (0);
}

static int	check_rgb_intensity(char *str, t_scene *data)
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
	data->light->intensity = ft_create_vector(num1/255.0, num2/255.0, num3/255.0);
	return (0);
}

int	create_light(char **res, t_scene *s)
{
	float	brightness;

	s->light = (t_light *)malloc(sizeof(t_light));
	if (!s->light)
		return (1);

	if (check_origin_point(res[1], s) == 1)
		return (free(s->light), 1);

	brightness = ft_atof(res[2]);
	if ((brightness < 0.0) || (brightness > 1.0))
		return (free(s->light), 1);

	if (check_rgb_intensity(res[3], s) == 1)
		return (free(s->light), 1);

	s->light->intensity = ft_multiply_tuple(s->light->intensity, brightness);
	return (0);
}

