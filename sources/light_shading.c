#include "../include/minirt.h"

t_material	ft_create_material(float x, float y, float z)
{
	t_material m;

	m.color = ft_create_point(x, y, z);
	m.ambient = 0.1;
	m.diffuse = 0.9;
	m.specular = 0.9;
	m.shininess = 200.0;
	return (m);
}

//t_tuple	normal_at(t_sphere sphere, t_tuple world_point)
//{
//	t_tuple	object_normal;
//	t_tuple	world_normal;
//
//	object_normal = ft_substract_tuples(world_point, sphere.center);
//	world_normal = ft_normalize(object_normal);
//	world_normal.w = 0;
//	return (world_normal);
//}

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

t_light	point_light(t_tuple position, t_color color)
{
	t_light light;

	light.source = position;
	light.color = color;
	return (light);
}

t_tuple	lighting(t_material mat, t_light light, t_tuple point, t_tuple eyev, t_tuple normalv)
{
	t_tuple	effective_color;
	t_tuple	lightv;
	t_tuple	ambient;
	t_tuple	diffuse;
	t_tuple	specular;
	t_tuple	reflectv;
	t_tuple	res;
	float	light_dot_normal;
	float	reflect_dot_eye = 0.0;
	float	factor;

	effective_color = ft_multiply_tuple(mat.color, light.intensity);
	lightv = ft_substract_tuples(light.source, point);
	lightv = ft_normalize(lightv);
	ambient = ft_multiply_tuple_f(effective_color, mat.ambient);
	light_dot_normal = ft_dot_product(lightv, normalv);
	if (light_dot_normal < 0)
	{
		diffuse = ft_create_point(0, 0, 0);
		specular = ft_create_point(0, 0, 0);
	}
	else
	{
		diffuse = ft_multiply_tuple_f(effective_color, mat.diffuse * light_dot_normal);
		reflectv = reflect(ft_negate_tuple(lightv), normalv);
		reflect_dot_eye = ft_dot_product(reflectv, eyev);
	}
	if (reflect_dot_eye <= 0)
		specular = ft_create_point(0, 0, 0);
	else
	{
		factor = powf(reflect_dot_eye, mat.shininess);
		specular = ft_multiply_tuple_f(light.intensity, (mat.specular * factor));
	}
	res = ft_add_tuples(ambient, ft_add_tuples(diffuse, specular));
	return (res);
}

