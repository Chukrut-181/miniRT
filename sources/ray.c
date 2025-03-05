/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:23:47 by igchurru          #+#    #+#             */
/*   Updated: 2025/03/05 15:31:58 by igchurru         ###   ########.fr       */
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
	t_tuple	position;

	position = *ft_add_tuples(&ray.origin, ft_multiply_tuple(&ray.direction, t));
	
	return (position);
}

float	ft_intersection(t_ray ray, t_sphere sphere)
{
	float	discriminant;
	float	a, b, c;
	t_tuple	sphere_to_ray;
	float	time[2];

	sphere_to_ray = *ft_substract_tuples(&ray.origin, &sphere.center);
	a = ft_dot_product(ray.direction, ray.direction);
	b = 2 * ft_dot_product(ray.direction, sphere_to_ray);
	c = ft_dot_product(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (0);
	time[0] = (-b - sqrtf(discriminant)) / (2 * a);
	time[1] = (-b + sqrtf(discriminant)) / (2 * a);
	return (*time);
}
