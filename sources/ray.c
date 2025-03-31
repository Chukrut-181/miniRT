/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urduliz.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:23:47 by igchurru          #+#    #+#             */
/*   Updated: 2025/03/21 08:34:29 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_ray	ft_create_ray(t_tuple origin, t_tuple direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_tuple	ft_position(t_ray ray, float t)
{
	t_tuple	pos;

	pos = ft_add_tuples(ray.origin, ft_multiply_tuple(ray.direction, t));
	return (pos);
}

void	transform_ray(t_ray	*ray, t_4x4 mat, t_ray *new_ray)
{
	new_ray->direction = ft_multiply_mat_and_tuple(mat, ray->direction);
	new_ray->origin = ft_multiply_mat_and_tuple(mat, ray->origin);
}

