#include "../include/minirt.h"

t_material	ft_create_material(char *rgb_code)
{
	t_material m;
	char **split;

	m.ambient = 0.2;
	m.diffuse = 0.7;
	m.specular = 0.9;
	m.shininess = 150.0;
	split = ft_split(rgb_code, ',');
	if (!split || !split[0] || !split[1] || !split[2])
		m.color = ft_create_color(255, 255, 255);
	else
		m.color = ft_create_color(ft_atof(split[0]), ft_atof(split[1]), ft_atof(split[2]));
	if (split)
		free(split);
	return (m);
}

t_tuple normal_at(t_sphere sphere, t_tuple world_point)
{
	t_tuple object_point;
	t_tuple object_normal;
	t_tuple world_normal;
	t_4x4 inverse_transform;
	t_4x4 transpose_inverse;
	
	inverse_transform = ft_find_inverse(sphere.transform);
	object_point = ft_multiply_mat_and_tuple(inverse_transform, world_point);
	object_normal = ft_substract_tuples(object_point, sphere.center);
	transpose_inverse = ft_transpose(inverse_transform);
	world_normal = ft_multiply_mat_and_tuple(transpose_inverse, object_normal);
	world_normal.w = 0;
	world_normal = ft_normalize(world_normal);
	
	return (world_normal);
}

t_tuple	reflect(t_tuple in, t_tuple normal)
{
	float	dop;
	t_tuple	scaled;
	t_tuple	result;

	dop = ft_dot_product(in, normal);
	scaled = ft_multiply_tuple_f(normal, 2.0 * dop);
	result = ft_substract_tuples(in, scaled);
	return (result);
}

// t_light	point_light(t_tuple position, t_tuple color)
// {
// 	t_light light;

// 	light.source = position;
// 	light.intensity = color;
// 	return (light);
// }

/* t_color	lighting(t_material mat, t_light light, t_tuple point, t_tuple eyev, t_tuple normalv)
{
	t_color	effective_color;
	t_tuple	lightv;
	t_color	ambient;
	t_color	diffuse;
	t_color	specular;
	t_tuple	reflectv;
	t_color	res;
	float	light_dot_normal;
	float	reflect_dot_eye = 0.0;
	float	factor;

	effective_color = ft_multiply_color(mat.color, light.l_color);
	lightv = ft_substract_tuples(light.source, point);
	lightv = ft_normalize(lightv);
	ambient = ft_multiply_color_f(effective_color, mat.ambient);
	light_dot_normal = ft_dot_product(lightv, normalv);
	if (light_dot_normal < 0)
	{
		diffuse = ft_create_color(0, 0, 0);
		specular = ft_create_color(0, 0, 0);
	}
	else
	{
		diffuse = ft_multiply_color_f(effective_color, mat.diffuse * light_dot_normal);
		reflectv = reflect(ft_negate_tuple(lightv), normalv);
		reflect_dot_eye = ft_dot_product(reflectv, eyev);
	}
	if (reflect_dot_eye <= 0)
		specular = ft_create_color(0, 0, 0);
	else
	{
		factor = powf(reflect_dot_eye, mat.shininess);
		specular = ft_multiply_color_f(light.l_color, (mat.specular * factor));
	}
	res = ft_add_color(ambient, ft_add_color(diffuse, specular));
	return (res);
}
 */