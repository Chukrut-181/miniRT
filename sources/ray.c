/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:23:47 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/29 12:19:50 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_ray	create_ray(t_tuple origin, t_tuple direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_tuple	ft_position(t_ray ray, double t)
{
	t_tuple	pos;

	pos = add_tuples(ray.origin, multiply_tuple_f(ray.direction, t));
	return (pos);
}

void	transform_ray(t_ray	*ray, t_4x4 mat, t_ray *new_ray)
{
	new_ray->direction = multiply_mat_and_tuple(mat, ray->direction);
	new_ray->origin = multiply_mat_and_tuple(mat, ray->origin);
}
