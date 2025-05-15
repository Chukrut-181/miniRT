#include "../include/minirt.h"

t_light	point_light(t_tuple position, t_color color)
{
	t_light light;

	light.source = position;
	light.l_color = color;
	return (light);
}

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
		m.color = ft_create_color(1.0, 1.0, 1.0);
	else
		m.color = ft_create_color(ft_atof(split[0]), ft_atof(split[1]), ft_atof(split[2]));
	m.a_color = m.color;
	if (split)
		ft_free_array(split);
	return (m);
}

t_tuple	normal_at(t_shape *shape, t_tuple point)
{
	t_tuple	object_point;
	t_tuple	object_normal;
	t_4x4	world_normal;
	t_tuple	normal_at;

	object_point = ft_multiply_mat_and_tuple(shape->inverse_matrix, point);
	if (shape->type == SPHERE)
		object_normal = ft_substract_tuples(object_point, ft_create_point(0, 0, 0));
	if (shape->type == PLANE)
		object_normal = ft_create_point(0, 1, 0);
//	if (shape->type == CYLINDER)
//		object_normal = ft_normal_cylinder();
	world_normal = ft_transpose(shape->inverse_matrix);
	normal_at = ft_multiply_mat_and_tuple(world_normal, object_normal);
	return (ft_normalize(normal_at));
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

static t_color		get_ambient(t_comps copm, t_light light)
{
	t_tuple point;
	t_color	ambient;

	point = ft_multiply_tuple_f(color_tp(ft_multiply_color(copm.object->material.a_color, light.l_color)),
			copm.object->material.ambient);
	ambient = ft_create_color(point.x, point.y, point.z);
	return (ambient);
}

static t_color		get_diffuse(t_comps comp, t_light light, t_tuple lightv)
{
	t_tuple tp1;
	t_tuple tp2;
	t_color	diffuse;

	tp1 = ft_multiply_tuple_f(color_tp(ft_multiply_color(comp.object->material.a_color, light.l_color)),
				comp.object->material.ambient);
	tp2 = ft_multiply_tuple_f(tp1, ft_dot_product(lightv, comp.normalv));
	diffuse = ft_create_color(tp2.x, tp2.y, tp2.z);
	return (diffuse);
}

t_color	lighting(t_comps comp, t_light light, bool in_shadow)
{
	t_lighting l;

	l.lightv = ft_substract_tuples(light.source, comp.over_point);
	l.lightv = ft_normalize(l.lightv);
	l.ambient = get_ambient(comp, light);
	if (ft_dot_product(l.lightv, comp.normalv) < 0 || in_shadow)
	{
		l.diffuse = ft_create_color(0, 0, 0);
		l.specular = ft_create_color(0, 0, 0);
	}
	else
	{
		l.diffuse = get_diffuse(comp, light, l.lightv);
		l.reflectv = reflect(ft_negate_tuple(l.lightv), comp.normalv);
		l.reflect_dot_eye = ft_dot_product(l.reflectv, comp.eyev);
		if (l.reflect_dot_eye <= 0)
			l.specular = ft_create_color(0, 0, 0);
		else
		{
			l.factor = powf(l.reflect_dot_eye, comp.object->material.shininess);
			l.specular = ft_multiply_color_f(light.l_color, (comp.object->material.specular * l.factor));
		}
	}
	return (ft_add_color(l.ambient, ft_add_color(l.diffuse, l.specular)));
}
