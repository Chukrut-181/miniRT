#include "../include/minirt.h"

// testear estas tres funciones (eliminar estor posteriormente)

t_tuple	ft_create_material(float x, float y, float z)
{
	t_material m;

	m.color = ft_create_point(x, y, z);
	m.ambient = 0,1;
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

	inverse_sphere = ft_find_inverse(sphere.transform);
	object_point = ft_cross_product(inverse_sphere, world_point);
	object_normal = ft_substract_tuples(object_point, ft_create_point(0, 0, 0));
	world_normal = ft_transpose(ft_cross_product(inverse_sphere, object_normal));
	world_normal.w = 0;
	return (ft_normalize(world_normal));
}

t_tuple	*reflect(t_tuple *in, t_tuple *normal)
{
	t_tuple	*str1;
	t_tuple	*str;
	t_tuple	*result;

	str1 = ft_multiply_tuple(normal, 2);
	str = ft_cross_product(str1, ft_dot_product(in, normal));
	result = ft_substract_tuples(in, str);
	return (result);
}

t_tuple	*point_light(t_tuple position, t_tuple intensity)
{
	t_light *light;

	light.position = position;
	light.intensity = intensity;
	return (light);
}

t_tuple	lighting(t_material mat, t_light light, t_tuple point, t_tuple eyev, t_tuple normalv)
{
	t_tuple	*effective_color;
	t_tuple	*lightv;
	t_tuple	*ambient;
	float	light_dot_normal;
	float	var;

	effective_color = ft_cross_product(mat.color, light.intensity);
	lightv = ft_substract_tuples(light.position, point);
	ft_normalize(lightv);
	ambient = ft_multiply_tuple(effective_color, material.ambient);
	light_dot_normal = ft_dot_product(lightv, normalv);
	if (light_dot_normal < 0)
	{
		material.diffuse = 0;
		material.specular = 0;
	}
	else
	{
		var = material.diffuse * light_dot_normal;
		material.diffuse = ft_multiply_tuple(effective_color, var);
		
	}
}
