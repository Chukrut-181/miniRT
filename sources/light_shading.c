#include "../include/minirt.h"

t_light	point_light(t_tuple position, t_color color)
{
	t_light light;

	light.source = position;
	light.l_color = color;
	return (light);
}

t_tuple	normal_at(t_shape *shape, t_tuple point)
{
	t_tuple	object_point;
	t_tuple	object_normal;
	t_4x4	world_normal;
	t_tuple	normal_at;

	object_normal = ft_create_vector(0, 0, 0);
	object_point = multiply_mat_and_tuple(shape->inverse_matrix, point);
	if (shape->type == SPHERE)
		object_normal = substract_tuples(object_point, ft_create_point(0, 0, 0));
	else if (shape->type == PLANE)
		object_normal = ft_create_vector(0, 1, 0);
	else if (shape->type == CYLINDER)
	{
        object_normal = ft_create_vector(object_point.x, 0, object_point.z);
        if (fabsf(object_point.y - 0) < EPSILON)
            object_normal = ft_create_vector(0, -1, 0);
        else if (fabsf(object_point.y - 1) < EPSILON)
            object_normal = ft_create_vector(0, 1, 0);
        else
            object_normal = ft_create_vector(object_point.x, 0, object_point.z);
    }
	world_normal = transpose(shape->inverse_matrix);
	normal_at = multiply_mat_and_tuple(world_normal, object_normal);
	return (ft_normalize(normal_at));
}

t_tuple	reflect(t_tuple in, t_tuple normal)
{
	float	dop;
	t_tuple	scaled;
	t_tuple	result;

	dop = dot_product(in, normal);
	scaled = multiply_tuple_f(normal, 2.0 * dop);
	result = substract_tuples(in, scaled);
	return (result);
}

static t_color	effective_color(t_material m, t_light l)
{
	t_color	effective_color;

	effective_color.r = m.color.r * l.l_color.r;
	effective_color.g = m.color.g * l.l_color.g;
	effective_color.b = m.color.b * l.l_color.b;
	return (effective_color);
}

static t_color		get_ambient(t_comps copm, t_light light)
{
	t_tuple point;
	t_color	ambient;

	point = multiply_tuple_f(color_tp(effective_color(copm.object->material, light)),
			copm.object->material.ambient);
	ambient = ft_create_color(point.x, point.y, point.z);
	return (ambient);
}

static t_color		get_diffuse(t_comps comp, t_light light, t_tuple lightv)
{
	t_tuple tp1;
	t_tuple tp2;
	t_color	diffuse;

	tp1 = multiply_tuple_f(color_tp(effective_color(comp.object->material, light)),
				comp.object->material.diffuse);
	tp2 = multiply_tuple_f(tp1, dot_product(lightv, comp.normalv));
	diffuse = ft_create_color(tp2.x, tp2.y, tp2.z);
	return (diffuse);
}

static t_color	calc_specular(t_material m, t_light l, double reflect_dot_eye)
{
	t_color	specular;
	double	factor;

	factor = pow(reflect_dot_eye, m.shininess);
	specular.r = l.l_color.r * m.specular * factor;
	specular.g = l.l_color.g * m.specular * factor;
	specular.b = l.l_color.b * m.specular * factor;
	return (specular);
}

t_color	lighting(t_comps comp, t_light light, int in_shadow)
{
	t_lighting l;

	l.lightv = substract_tuples(light.source, comp.over_point);
	l.lightv = ft_normalize(l.lightv);
	l.ambient = get_ambient(comp, light);
	if (dot_product(l.lightv, comp.normalv) < 0 || in_shadow)
	{
		l.diffuse = ft_create_color(0, 0, 0);
		l.specular = ft_create_color(0, 0, 0);
	}
	else
	{
		l.diffuse = get_diffuse(comp, light, l.lightv);
		l.reflectv = reflect(negate_tuple(l.lightv), comp.normalv);
		l.reflect_dot_eye = dot_product(l.reflectv, comp.eyev);
		if (l.reflect_dot_eye <= 0)
			l.specular = ft_create_color(0, 0, 0);
		else
		{
			l.specular = calc_specular(comp.object->material, light, l.reflect_dot_eye);
		}
	}
	return (add_colors(l.ambient, add_colors(l.diffuse, l.specular)));
}
