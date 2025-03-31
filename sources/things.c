/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   things.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:42:33 by igchurru          #+#    #+#             */
/*   Updated: 2025/03/31 15:59:30 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_sphere	*ft_create_sphere(t_tuple point, float r)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->type = SPHERE;
	sphere->center = point;
	sphere->radius = r;
	*sphere->transform = ft_create_identity_matrix();
	return (sphere);
}

t_plane	*ft_create_plane(t_tuple point, t_tuple vector)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (NULL);
	plane->type = PLANE;
	plane->point_in_plane = point;
	plane->n_n_vector = vector;
	*plane->transform = ft_create_identity_matrix();
	return (plane);
}

t_cyl	*ft_create_cylinder(t_tuple point, t_tuple vector, float d, float h)
{
	t_cyl	*cylinder;

	cylinder = malloc(sizeof(t_cyl));
	if (!cylinder)
		return (NULL);
	cylinder->type = CYLINDER;
	cylinder->center = point;
	cylinder->n_n_vector = vector;
	cylinder->diameter = d;
	cylinder->height = h;
	*cylinder->transform = ft_create_identity_matrix();
	return (cylinder);	
}
