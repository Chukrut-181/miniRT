/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:23:47 by igchurru          #+#    #+#             */
/*   Updated: 2025/03/07 12:44:34 by igchurru         ###   ########.fr       */
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

	pos = *ft_add_tuples(&ray.origin, ft_multiply_tuple(&ray.direction, t));
	return (pos);
}

static void	ft_calculate_abcd(t_ray ray, t_sphere sphere, t_abcd *data)
{
	t_tuple	sphere_to_ray;

	sphere_to_ray = *ft_substract_tuples(&ray.origin, &sphere.center);
	data->a = ft_dot_product(ray.direction, ray.direction);
	data->b = 2 * ft_dot_product(ray.direction, sphere_to_ray);
	data->c = (ft_dot_product(sphere_to_ray, sphere_to_ray)
			- (sphere.radius * sphere.radius));
	data->discriminant = (data->b * data->b) - (4 * data->a * data->c);
	return ;
}

t_list	*ft_register_intersections(t_abcd data, t_list *xs_list, t_ray ray)
{
	t_xs	*first_xs;
	t_xs	*second_xs;

	first_xs = malloc(sizeof(t_xs));
	first_xs->object = "sphere";
	first_xs->time = (-data.b - sqrtf(data.discriminant)) / (2 * data.a);
	first_xs->point = *ft_add_tuples
		(&ray.origin, ft_multiply_tuple(&ray.direction, first_xs->time));
	second_xs = malloc(sizeof(t_xs));
	second_xs->object = "sphere";
	second_xs->time = (-data.b + sqrtf(data.discriminant)) / (2 * data.a);
	second_xs->point = *ft_add_tuples
		(&ray.origin, ft_multiply_tuple(&ray.direction, second_xs->time));
	ft_lstadd_back(&xs_list, ft_lstnew(first_xs));
	ft_lstadd_back(&xs_list, ft_lstnew(second_xs));
	return (xs_list);
}

t_list	*ft_intersection(t_ray ray, t_sphere sphere, t_list *xs_list)
{
	t_abcd	solution_data;

	ft_calculate_abcd(ray, sphere, &solution_data);
	if (solution_data.discriminant < 0)
		return (xs_list);
	xs_list = ft_register_intersections(solution_data, xs_list, ray);
	return (xs_list);
}
