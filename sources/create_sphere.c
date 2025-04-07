#include "../include/minirt.h"

static	t_4x4	create_sphere_transform(t_tuple center, float diameter)
{
	t_4x4	transform;
	t_tuple	scale_vector;

	transform = ft_create_identity_matrix();
	transform = ft_multiply_matrices(translation(center), transform);

	scale_vector = ft_create_vector(diameter / 2, diameter / 2, diameter / 2);
	transform = ft_multiply_matrices(scaling(scale_vector), transform);
	return (transform);
}

static int	check_viewpoint1(char *str, t_sphere *sphere)
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
	sphere->center.x = num1;
	sphere->center.y = num2;
	sphere->center.z = num3;
	return (0);
}

static int	check_rgb_sphere(char *str, t_sphere *sphere)
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
	sphere->material.color.x = num1;
	sphere->material.color.y = num2;
	sphere->material.color.z = num3;
	sphere->material.ambient = 0.1;
	sphere->material.diffuse = 0.7;
	sphere->material.specular = 0.3;
	sphere->material.shininess = 100.0;
	return (0);
}

int	create_sphere(char **res, t_scene *s)
{
	float		diameter;
	t_sphere	*sphere;
	t_list		*new_node;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sphere)
		return (free(sphere), 1);
	if (check_viewpoint1(res[1], sphere) == 1)
		return (free(sphere), 1);
	if (check_rgb_sphere(res[3], sphere) == 1)
		return (free(sphere), 1);
	diameter = ft_atof(res[2]);
	sphere->diameter = diameter;
	sphere->type = SPHERE;

	sphere->transform = create_sphere_transform(sphere->center, diameter);

	new_node = ft_lstnew(sphere);
	if (!new_node)
		return (free(sphere), 1);
	ft_lstadd_back(&(s->objects), new_node);
	return (0);
}

