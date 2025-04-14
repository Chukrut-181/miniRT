/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:17:51 by igchurru          #+#    #+#             */
/*   Updated: 2025/04/14 11:21:17 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static bool	ft_intersect_ray_plane(t_ray ray, t_plane plane, float *t)
{
	float	denominator;
	t_tuple	plane_to_ray;

	denominator = ft_dot_product(plane.n_n_vector, ray.direction);
	if (fabs(denominator) < EPSILON) // Ray is parallel to the plane
		return (false);
	plane_to_ray = ft_substract_tuples(plane.point_in_plane, ray.origin);
	*t = ft_dot_product(plane_to_ray, plane.n_n_vector) / denominator;
	return (*t >= 0); // Only consider intersections in front of the ray
}

t_list	*ft_intersect_plane(t_ray ray, t_plane plane, t_list *xs_list)
{
	float	t;
	t_xs	*intersection;

	if (!ft_intersect_ray_plane(ray, plane, &t))
		return (xs_list); // No intersection
	intersection = malloc(sizeof(t_xs));
	if (!intersection)
		return (xs_list); // Memory allocation failed
	intersection->object = &plane;
	intersection->time = t;
	intersection->point = ft_position(ray, t);
	intersection->hit = 0;
	ft_lstadd_back(&xs_list, ft_lstnew(intersection));
	return (xs_list);
}
