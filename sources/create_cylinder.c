/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:52:50 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/15 15:16:43 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

bool	ft_create_cylinder(t_scene *scene, char **cyl_data)
{
	t_shape	*cylinder;
	t_4x4	translation_matrix;
	t_4x4	rotation_matrix;
	t_4x4	scalation_matrix;
    char	**coords;
    float	radius;
    float	height;

	cylinder = malloc(sizeof(t_shape));
	if (!cylinder)
		ft_error_exit(scene, "Error\nFailed to allocate memory for cylinder", 1);
	cylinder->type = CYLINDER;
	if (!ft_check_coords(cyl_data[1]))
		return (free(cylinder), false);
	coords = ft_split(cyl_data[1], ',');
	translation_matrix = create_translation_mx(ft_atof(coords[0]), ft_atof(coords[1]), ft_atof(coords[2]));
	ft_free_array(coords);
	if (!ft_check_coords(cyl_data[2]))
		return (free(cylinder), false);
	coords = ft_split(cyl_data[2], ',');
	rotation_matrix = ft_rodriguez_rotation(ft_atof(coords[0]), ft_atof(coords[1]), ft_atof(coords[2]));
	ft_free_array(coords);
	radius = (ft_atof(cyl_data[3]) / 2.0);
	height = ft_atof(cyl_data[4]);
	if (radius <= 0 || height <= 0)
		return(free(cylinder), false);
	scalation_matrix = create_scaling_mx(radius, radius, height);
	cylinder->transform_matrix = ft_multiply_matrices(translation_matrix, ft_multiply_matrices(scalation_matrix, rotation_matrix));
	cylinder->inverse_matrix = ft_find_inverse(cylinder->transform_matrix);
	if (!ft_check_rgb(cyl_data[5]))
		return (free(cylinder), false);
	cylinder->material = ft_create_material(cyl_data[5]);
	ft_lstadd_back(&scene->world->objects, ft_lstnew(cylinder));
	return (true);
}
