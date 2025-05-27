/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cube_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:29:33 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/27 17:07:54 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static t_4x4	ft_transform_cube(char *center, char *scale, char *target_v)
{
	t_4x4	translate;
	t_4x4	rotate;
	t_4x4	scalate;
	t_4x4	transform_matrix;
	char	**aux;

	aux = ft_split(center, ',');
	translate = create_translation_mx(ft_atof(aux[0]), ft_atof(aux[1]), ft_atof(aux[2]));
	ft_free_array(aux);
	aux = ft_split(scale, ',');
	scalate = create_scaling_mx(ft_atof(aux[0]), ft_atof(aux[1]), ft_atof(aux[2]));
	ft_free_array(aux);
	aux = ft_split(target_v, ',');
	rotate = rodriguez_rotation(ft_atof(aux[0]), ft_atof(aux[1]), ft_atof(aux[2]));
	ft_free_array(aux);
	transform_matrix = multiply_matrices(translate, multiply_matrices(rotate, scalate));
	return (transform_matrix);
}

bool	create_cube(t_scene *scene, char **temp)
{
	t_shape	*cube;
	
	cube = malloc(sizeof(t_shape));
	if (!cube)
		ft_error_exit(scene, "Error\nMemory allocation failed for cube.\n", 1);
	cube->type = CUBE;
	if (!check_coords(temp[1]) || !check_coords(temp[2]) || !check_coords(temp[3]) || !check_rgb(temp[4]))
		return (free(cube), false);
	cube->transform_matrix = ft_transform_cube(temp[1], temp[2], temp[3]);
	cube->inverse_matrix = find_inverse(cube->transform_matrix);
	cube->material = create_material(temp[4]);
	ft_lstadd_back(&scene->world->objects, ft_lstnew(cube));
	return (true);
}
	
	
	
	
	