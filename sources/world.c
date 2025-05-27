/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:28:40 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/27 10:21:06 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_comps	prepare_computations(t_xs *hit, t_ray ray)
{
	t_comps	comps;

	comps.time = hit->time;
	comps.object = hit->object;
	comps.point = ft_position(ray, comps.time);
	comps.eyev = negate_tuple(ray.direction);
	comps.normalv = normal_at((t_shape *)comps.object, comps.point);
	if (dot_product(comps.normalv, comps.eyev) < 0)
	{
		comps.inside = true;
		comps.normalv = negate_tuple(comps.normalv);
	}
	else
		comps.inside = false;
	comps.over_point.x = comps.point.x + comps.normalv.x * EPSILON;
	comps.over_point.y = comps.point.y + comps.normalv.y * EPSILON;
	comps.over_point.z = comps.point.z + comps.normalv.z * EPSILON;
	comps.over_point.w = 1;
	return (comps);
}

bool	is_shadowed(t_world world, t_tuple point)
{
	t_tuple	v;
	float	distance;
	t_list	*xs_list;
	t_list	*current;
	t_xs	*xsection;

	xs_list = NULL;
	v = substract_tuples(world.light->source, point);
	distance = get_magnitude(v);
	xs_list = ft_intersect_world(world, create_ray(point, normalize(v)));
	current = xs_list;
	while (current)
	{
		xsection = (t_xs *)current->content;
		if (xsection->time > (EPSILON * 100) && xsection->time < distance)
		{
			ft_lstclear(&xs_list, free);
			return (true);
		}
		current = current->next;
	}
	ft_lstclear(&xs_list, free);
	return (false);
}

t_color	shade_hit(t_world world, t_comps comps)
{
	t_color	result;
	bool	shadowed;

	shadowed = is_shadowed(world, comps.over_point);
	result = lighting(comps, &world, shadowed);
	return (result);
}

static void	find_min(t_list *xs, t_xs **min_inter, double *min)
{
	t_xs	*temp;

	while (xs)
	{
		temp = (t_xs *) xs->content;
		if (*min > temp->time && temp->time > 0)
		{
			*min_inter = temp;
			*min = temp->time;
		}
		xs = xs->next;
	}
}

t_xs	*ft_find_hit(t_list *intersection_list)
{
	t_list	*current;
	t_xs	*inter;
	t_xs	*inte_min;
	double	min;

	inte_min = NULL;
	min = INFINITY;
	current = intersection_list;
	inter = malloc(sizeof(t_xs));
	if (current)
	{
		find_min(current, &inte_min, &min);
		if (inte_min && inte_min->time > 0)
		{
			free(inter);
			return (inte_min);
		}
	}
	inter->hit = 0;
	inter->time = 0;
	return (inter);
}
