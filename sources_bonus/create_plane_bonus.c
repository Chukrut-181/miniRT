/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_plane_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:07:45 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/29 10:02:11 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt_bonus.h"

bool	create_plane(t_scene *scene, char **pla)
{
	t_shape	*plane;
	char	**coords;
	t_4x4	translate;
	t_4x4	rotate;

	plane = malloc(sizeof(t_shape));
	if (!plane)
		ft_error_exit(scene, "Error\nMemory allocation failed for plane.\n", 1);
	plane->type = PLANE;
	if (ft_arraylen(pla) != 5 || !check_coords(pla[1])
		|| !check_coords(pla[2]) || !check_rgb(pla[3]))
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
	plane->material = create_material(pla[3], pla[4]);
	ft_lstadd_back(&scene->world->objects, ft_lstnew(plane));
	return (true);
}
