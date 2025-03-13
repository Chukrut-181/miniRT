#include "../include/minirt.h"

// testear todas estas funciones (eliminar estor posteriormente)

t_tuple	ft_create_material(float x, float y, float z)
{
	t_material m;

	m.color = ft_create_point(x, y, z);
	m.ambient = 0.1;
	m.diffuse = 0.9;
	m.specular = 0.9;
	m.shininess = 200.0;
	return (m);
}

t_tuple	*normal_at(t_sphere *sphere, t_tuple *world_point)
{
	t_tuple *object_point;
	t_tuple *object_normal;
	t_tuple *world_normal;
	t_4x4	*inverse_sphere;

	inverse_sphere = ft_find_inverse(sphere->transform);
	object_point = ft_multiply_mat_and_tuple(inverse_sphere, world_point);
	object_normal = ft_substract_tuples(object_point, ft_create_point(0, 0, 0));

	t_4x4	*transpose_inverse = ft_transpose(inverse_sphere);
	world_normal = ft_multiply_mat_and_tuple(transpose_inverse, object_normal);
	world_normal->w = 0;
	ft_normalize(world_normal)

	free(inverse_sphere);
	free(transpose_inverse);
	free(object_point);
	free(object_normal);
	return (world_normal);
}

t_tuple	*reflect(t_tuple *in, t_tuple *normal)
{
	float	dop;
	t_tuple	*str;
	t_tuple	*result;

	dop = ft_dot_product(*in, *normal);
	str = ft_multiply_tuple(normal, 2.0 * dot);
	result = ft_substract_tuples(in, str);
	free(scaled_normal);
	return (result);
}

t_tuple	*point_light(t_tuple *position, t_tuple *intensity)
{
	t_light *light;

	light = malloc(sizeof(t_light);

	light->position = *position;
	light->intensity = *intensity;
	return (light);
}

t_tuple	lighting(t_material mat, t_light light, t_tuple point, t_tuple eyev, t_tuple normalv)
{
	t_tuple	*effective_color;
	t_tuple	*lightv;
	t_tuple	*ambient;
	t_tuple	*diffuse;
	t_tuple	*specular;
	t_tuple	*reflectv;
	float	light_dot_normal;
	float	reflect_dot_eye;
	float	var;
	float	factor;

	effective_color = ft_cross_product(mat.color, light.intensity);
	lightv = ft_substract_tuples(light.position, point);
	ft_normalize(lightv);
	ambient = ft_multiply_tuple(effective_color, material.ambient);
	light_dot_normal = ft_dot_product(lightv, normalv);
	if (light_dot_normal < 0)
	{
		diffuse = ft_create_point(0, 0, 0);
		specular = ft_create_point(0, 0, 0);
	}
	else
	{
		diffuse = ft_multiply_tuple(effective_color, material.diffuse * light_dot_normal);
		reflectv = reflect(ft_negate_tuple(lightv), normalv);
		reflect_dot_eye = ft_dot_product(reflectv, eyev);
	}
	if (reflect_dot_eye <= 0)
		specular = ft_create_point(0, 0, 0);
	else
	{
		factor = powf(reflect_dot_eye, material.shininess);
		specular = ft_multiply_tuple(light.intensity, (material.specular * factor));
	}
	return (ft_multiply_tuple(ambient, (diffuse * specular));
}

