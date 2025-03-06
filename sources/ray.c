/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urduliz.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:23:47 by igchurru          #+#    #+#             */
/*   Updated: 2025/03/06 15:33:33 by eandres          ###   ########.fr       */
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

t_xs	*ft_intersection(t_ray ray, t_sphere sphere)
{
	float	discriminant;
	float	a, b, c;
	t_tuple	sphere_to_ray;
	t_xs	*new_xs;
	
	sphere_to_ray = *ft_substract_tuples(&ray.origin, &sphere.center);
	a = ft_dot_product(ray.direction, ray.direction);
	b = 2 * ft_dot_product(ray.direction, sphere_to_ray);
	c = (ft_dot_product(sphere_to_ray, sphere_to_ray) - (sphere.radius * sphere.radius));
	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (NULL);
	new_xs = malloc(sizeof(t_xs));
	new_xs->object = &sphere;
	new_xs->t1 = (-b - sqrtf(discriminant)) / (2 * a);
	new_xs->entry = ft_position(ray, new_xs->t1);
	new_xs->t2 = (-b + sqrtf(discriminant)) / (2 * a);
	new_xs->exit = ft_position(ray, new_xs->t2);
	new_xs->next = NULL;
	return (new_xs);
}
