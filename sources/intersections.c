/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:59:10 by igchurru          #+#    #+#             */
/*   Updated: 2025/03/22 12:15:44 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	ft_identify_hit(t_list *xs_list)
{
	float	reference;
	t_xs	*aux;
	t_xs	*mark;

	reference = 214748368;
	aux = NULL;
	mark = NULL;
	while (xs_list != NULL)
	{
		aux = (t_xs *)xs_list->content;
		if (aux->time < reference && aux->time > 0)
		{
			reference = aux->time;
			if (mark)
				mark->hit = 0;
			aux->hit = 1;
			mark = aux;
		}
		xs_list = xs_list->next;
	}
}

static void	ft_calculate_abcd(t_ray ray, t_sphere sphere, t_abcd *data)
{
	t_tuple	sphere_to_ray;

	sphere_to_ray = ft_substract_tuples(ray.origin, sphere.center);
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
	first_xs->point = ft_add_tuples
		(ray.origin, ft_multiply_tuple(ray.direction, first_xs->time));
	first_xs->hit = 0;
	second_xs = malloc(sizeof(t_xs));
	second_xs->object = "sphere";
	second_xs->time = (-data.b + sqrtf(data.discriminant)) / (2 * data.a);
	second_xs->point = ft_add_tuples
		(ray.origin, ft_multiply_tuple(ray.direction, second_xs->time));
	second_xs->hit = 0;
	ft_lstadd_back(&xs_list, ft_lstnew(first_xs));
	ft_lstadd_back(&xs_list, ft_lstnew(second_xs));
	return (xs_list);
}

t_list	*ft_intersection(t_ray ray, t_sphere sphere, t_list *xs_list)
{
	t_abcd	solution_data;

	ft_calculate_abcd(ray, sphere, &solution_data);
	if (solution_data.discriminant < 0)
		return (NULL);
	xs_list = ft_register_intersections(solution_data, xs_list, ray);
	ft_identify_hit(xs_list);
	return (xs_list);
}

