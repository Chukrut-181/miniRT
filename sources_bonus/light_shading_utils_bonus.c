/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shading_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:31:02 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/28 10:51:21 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_tuple	normal_at(t_shape *shape, t_tuple point)
{
	t_tuple	obj_point;
	t_tuple	obj_normal;
	t_4x4	world_normal;
	t_tuple	normal_at;
	float	abs[4];

	obj_normal = create_vector(0, 0, 0);
	obj_point = multiply_mat_and_tuple(shape->inverse_matrix, point);
	if (shape->type == SPHERE)
		obj_normal = substract_tuples(obj_point, ft_create_point(0, 0, 0));
	else if (shape->type == PLANE)
		obj_normal = create_vector(0, 1, 0);
	else if (shape->type == CYLINDER)
		obj_normal = create_vector(obj_point.x, 0, obj_point.z);
	else if (shape->type == CUBE)
	{
		abs[1] = fabsf(obj_point.x);
		abs[2] = fabsf(obj_point.y);
		abs[3] = fabsf(obj_point.z);
		abs[0] = fmaxf(fmaxf(abs[1], abs[2]), abs[3]);
		if (fabsf(abs[0] - abs[1]) < EPSILON)
			obj_normal = create_vector(obj_point.x, 0, 0);
		else if (fabsf(abs[0] - abs[2]) < EPSILON)
			obj_normal = create_vector(0, obj_point.y, 0);
		else
			obj_normal = create_vector(0, 0, obj_point.z);
	}
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
