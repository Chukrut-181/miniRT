/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:07:45 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/16 12:36:30 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static t_4x4	ft_transform_plane(char *center, char *normal)
{
	t_4x4	translate;
	t_4x4	rotate;
	t_4x4	transform;
	char	**aux;

	aux = ft_split(center, ',');
	translate = create_translation_mx(ft_atof(aux[0]),
			ft_atof(aux[1]), ft_atof(aux[2]));
	ft_free_array(aux);
	aux = ft_split(normal, ',');
	rotate = ft_rodriguez_rotation(ft_atof(aux[0]),
			ft_atof(aux[1]), ft_atof(aux[2]));
	ft_free_array(aux);
	transform = ft_multiply_matrices(translate, rotate);
	return (transform);
}

bool	ft_create_plane(t_scene *scene, char **surface)
{
	t_shape	*plane;

	plane = malloc(sizeof(t_shape));
	if (!plane)
		ft_error_exit(scene, "Error\nFailed to allocate memory for plane", 1);
	plane->type = PLANE;
	if (!ft_check_coords(surface[1]) || !ft_check_coords(surface[2]))
		return (free(plane), false);
	plane->transform_matrix = ft_transform_plane(surface[1], surface[2]);
	plane->inverse_matrix = ft_find_inverse(plane->transform_matrix);
	if (!ft_check_rgb(surface[3]))
		return (free(plane), false);
	plane->material = ft_create_material(surface[3]);
	ft_lstadd_back(&scene->world->objects, ft_lstnew(plane));
	return (true);
}
