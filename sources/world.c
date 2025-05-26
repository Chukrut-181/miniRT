/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:28:40 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/26 12:52:33 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static t_ray	transform(t_ray ray, t_4x4	matrix)
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

static bool	ft_intersections(t_ray ray, t_shape *shape, t_list **inter)
{
	shape->ray_in_obj_space = transform(ray, shape->inverse_matrix);
	if (shape->type == SPHERE)
		return (intersec_sphere(shape, inter));
	else if (shape->type == PLANE)
		return (intersec_plane(shape, inter));
	else if (shape->type == CYLINDER)
		return (intersec_cylinder(shape, inter, shape->ray_in_obj_space));
	return (false);
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
	t_list	*xs;
	t_list	*current;
	t_xs	*intersection;

	xs = NULL;
	v = substract_tuples(world.light->source, point);
	distance = get_magnitude(v);
	xs = ft_intersect_world(world, create_ray(point, normalize(v)));
	current = xs;
	while (current)
	{
		intersection = (t_xs *)current->content;
		if (intersection->time > EPSILON && intersection->time < distance)
		{
			ft_lstclear(&xs, free);
			return (true);
		}
		current = current->next;
	}
	ft_lstclear(&xs, free);
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
