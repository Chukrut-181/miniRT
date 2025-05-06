/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:05:17 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/06 16:30:27 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	ft_create_sphere(t_scene *scene, char **ball)
{
	t_shape	*sphere;
	t_4x4	translation_mx;
	t_4x4	scaling_mx;
	char	**center;
	float	diameter;

	sphere = malloc(sizeof(t_shape));
	if (!sphere)
		return (1);
	sphere->type = SPHERE;
	if (!ft_check_coords(ball[1]))
		return (free(sphere), 1);
	center = ft_split(ball[1], ',');
	translation_mx = translation(ft_atof(center[0]),
			ft_atof(center[1]), ft_atof(center[2]));
	diameter = ft_atof(ball[2]);
	scaling_mx = scaling(ft_create_point(diameter, diameter, diameter));
	if (!ft_check_rgb(ball[3]))
		return (free(sphere), 1);
	sphere->material = ft_create_material(ball[3]);
	sphere->transform_matrix = ft_multiply_matrices(translation_mx, scaling_mx);
	sphere->inverse_matrix = ft_find_inverse(sphere->transform_matrix);
	ft_lstadd_back(&(scene->world), ft_lstnew(sphere));
	ft_free_array(center);
	return (0);
}
