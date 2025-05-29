/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:26:19 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/29 12:19:50 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt_bonus.h"

void	solve_quadratic_equation(t_abcd data, double *t)
{
	t[0] = (-data.b - sqrtf(data.discriminant)) / (2 * data.a);
	t[1] = (-data.b + sqrtf(data.discriminant)) / (2 * data.a);
	return ;
}

void	update_inter(t_list **inter, t_shape *shape, double time)
{
	t_xs	*intersec;

	intersec = malloc(sizeof(t_xs));
	if (!intersec)
		return ;
	intersec->object = shape;
	intersec->time = time;
	intersec->hit = 1;
	intersec->intersec = true;
	if (*inter == NULL)
		*inter = ft_lstnew(intersec);
	else
		ft_lstadd_back(inter, ft_lstnew(intersec));
}

void	identify_hit(t_list *xs_list)
{
	double	reference;
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

t_ray	transform(t_ray ray, t_4x4	matrix)
{
	t_tuple	multi[2];
	t_tuple	p;
	t_tuple	vec;
	t_ray	new_ray;

	multi[0] = multiply_mat_and_tuple(matrix, ray.origin);
	multi[1] = multiply_mat_and_tuple(matrix, ray.direction);
	p = ft_create_point(multi[0].x, multi[0].y, multi[0].z);
	vec = create_vector(multi[1].x, multi[1].y, multi[1].z);
	new_ray.origin = p;
	new_ray.direction = vec;
	return (new_ray);
}

t_list	*ft_intersect_world(t_world world, t_ray ray)
{
	t_list	*intersections;
	t_list	*current;
	t_shape	*shape;
	bool	found_inter;

	current = world.objects;
	found_inter = false;
	intersections = NULL;
	while (current)
	{
		shape = (t_shape *)current->content;
		if (ft_intersections(ray, shape, &intersections))
			found_inter = true;
		current = current->next;
	}
	if (found_inter == false)
	{
		ft_lstclear(&intersections, free);
		return (NULL);
	}
	return (intersections);
}
