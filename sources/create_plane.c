/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:07:45 by igchurru          #+#    #+#             */
/*   Updated: 2025/06/02 17:03:21 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

bool	create_plane(t_scene *scene, char **pla)
{
	t_shape	*plane;
	char	**coords;
	t_4x4	translate;
	t_4x4	rotate;

	plane = malloc(sizeof(t_shape));
	if (!plane)
		return (false);
	plane->type = PLANE;
	if (!check_coords(pla[1]) || !check_coords(pla[2]) || !check_rgb(pla[3]))
		return (free(plane), false);
	coords = ft_split(pla[1], ',');
	translate = create_translation_mx(ft_atof(coords[0]),
			ft_atof(coords[1]), ft_atof(coords[2]));
	ft_free_array(coords);
	coords = ft_split(pla[2], ',');
	rotate = rodriguez_rotation(ft_atof(coords[0]),
			ft_atof(coords[1]), ft_atof(coords[2]));
	ft_free_array(coords);
	plane->transform_matrix = multiply_matrices(translate, rotate);
	plane->inverse_matrix = find_inverse(plane->transform_matrix);
	plane->material = create_material(pla[3]);
	ft_lstadd_back(&scene->world->objects, ft_lstnew(plane));
	return (true);
}
