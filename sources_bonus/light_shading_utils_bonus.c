/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shading_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:31:02 by igchurru          #+#    #+#             */
/*   Updated: 2025/06/02 10:50:18 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt_bonus.h"

static t_tuple	get_cube_normal(t_tuple obj_point)
{
	float	abs_x;
	float	abs_y;
	float	abs_z;
	float	max_abs;

	abs_x = fabsf(obj_point.x);
	abs_y = fabsf(obj_point.y);
	abs_z = fabsf(obj_point.z);
	max_abs = fmaxf(fmaxf(abs_x, abs_y), abs_z);
	if (fabsf(max_abs - abs_x) < EPSILON)
		return (create_vector(obj_point.x, 0, 0));
	else if (fabsf(max_abs - abs_y) < EPSILON)
		return (create_vector(0, obj_point.y, 0));
	else
		return (create_vector(0, 0, obj_point.z));
}

t_tuple	normal_at(t_shape *shape, t_tuple point)
{
	t_tuple	obj_point;
	t_tuple	obj_normal;
	t_4x4	world_normal;
	t_tuple	normal_at;

	obj_normal = create_vector(0, 0, 0);
	obj_point = multiply_mat_and_tuple(shape->inverse_matrix, point);
	if (shape->type == SPHERE)
		obj_normal = substract_tuples(obj_point, ft_create_point(0, 0, 0));
	else if (shape->type == PLANE)
		obj_normal = create_vector(0, 1, 0);
	else if (shape->type == CYLINDER)
		obj_normal = create_vector(obj_point.x, 0, obj_point.z);
	else if (shape->type == CUBE)
		obj_normal = get_cube_normal(obj_point);
	world_normal = transpose(shape->inverse_matrix);
	normal_at = multiply_mat_and_tuple(world_normal, obj_normal);
	return (normalize(normal_at));
}

t_color	effective_color(t_material m, t_color color, float intensity)
{
	t_color	effective_color;

	effective_color.r = m.color.r * color.r * intensity;
	effective_color.g = m.color.g * color.g * intensity;
	effective_color.b = m.color.b * color.b * intensity;
	return (effective_color);
}

t_light	point_light(t_tuple position, t_color color)
{
	t_light	light;

	light.source = position;
	light.l_color = color;
	return (light);
}

t_color	reflected_color(t_world world, t_comps comps)
{
	t_ray	reflect_ray;
	t_color	color;

	if (comps.object->material.reflectiveness == 0)
		return (ft_create_color(0, 0, 0));
	reflect_ray = create_ray(comps.over_point, comps.reflectv);
	color = calculate_inter(world, reflect_ray);
	return(multiply_color_f(color, comps.object->material.reflectiveness));
}
