/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:52:50 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/21 11:43:22 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static t_4x4	ft_transform_cyl(char *center, char *axis, float r, float h)
{
	t_4x4	translate;
	t_4x4	rotate;
	t_4x4	scalate;
	t_4x4	transform_matrix;
	char	**aux;

	aux = ft_split(center, ',');
	translate = create_translation_mx(ft_atof(aux[0]),
			ft_atof(aux[1]), ft_atof(aux[2]));
	ft_free_array(aux);
	aux = ft_split(axis, ',');
	rotate = rodriguez_rotation(ft_atof(aux[0]),
			ft_atof(aux[1]), ft_atof(aux[2]));
	ft_free_array(aux);
	scalate = create_scaling_mx(1.0, 1.0, 1.0);
	transform_matrix = multiply_matrices(translate,
			multiply_matrices(rotate, scalate));
	scalate = create_scaling_mx(r, h, r);
	transform_matrix = multiply_matrices(transform_matrix, scalate);
	return (transform_matrix);
}

bool	ft_create_cylinder(t_scene *scene, char **cyl_data)
{
	t_shape	*cylinder;
	float	radius;
	float	height;

	cylinder = malloc(sizeof(t_shape));
	if (!cylinder)
		ft_error_exit(scene, "Error\nFailed to allocate cylinder", 1);
	cylinder->type = CYLINDER;
	if (!ft_check_coords(cyl_data[1]) || !ft_check_coords(cyl_data[2]))
		return (free(cylinder), false);
	radius = (ft_atof(cyl_data[3]) / 2.0);
	height = ft_atof(cyl_data[4]);
	if (radius <= 0 || height <= 0)
		return (free(cylinder), false);
	cylinder->transform_matrix = ft_transform_cyl(cyl_data[1],
			cyl_data[2], radius, height);
	cylinder->inverse_matrix = find_inverse(cylinder->transform_matrix);
	if (!check_rgb(cyl_data[5]))
		return (free(cylinder), false);
	cylinder->material = ft_create_material(cyl_data[5]);
	ft_lstadd_back(&scene->world->objects, ft_lstnew(cylinder));
	return (true);
}
