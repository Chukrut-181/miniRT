/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:07:45 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/15 13:07:08 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

bool	ft_create_plane(t_scene *scene, char **surface)
{
	t_shape	*plane;
	char	**coords;
	t_4x4	translate;
	t_4x4	rotate;

	plane = malloc(sizeof(t_shape));
	if (!plane)
		ft_error_exit(scene, "Error\nFailed to allocate memory for plane", 1);
	plane->type = PLANE;
	if (!ft_check_coords(surface[1]))
		return (free(plane), false);
	coords = ft_split(surface[1], ',');
	translate = create_translation_mx(ft_atof(coords[0]), ft_atof(coords[1]), ft_atof(coords[2]));
	ft_free_array(coords);
	if (!ft_check_coords(surface[2]))
		return (free(plane), false);
	coords = ft_split(surface[2], ',');
	rotate = ft_rotate_plane(ft_atof(coords[0]), ft_atof(coords[1]), ft_atof(coords[2]));
	ft_free_array(coords);
	plane->transform_matrix = ft_multiply_matrices(translate, rotate);
	plane->inverse_matrix = ft_find_inverse(plane->transform_matrix);
	if (!ft_check_rgb(surface[3]))
		return (free(plane), false);
	plane->material = ft_create_material(surface[3]);
	return (ft_lstadd_back(&scene->world->objects, ft_lstnew(plane)), true);
}
