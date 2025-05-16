/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:11:13 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/16 11:48:58 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_4x4	ft_orientation(t_tuple left, t_tuple true_up, t_tuple forward)
{
	t_4x4	matrix;

	matrix = ft_create_identity_matrix();
	matrix.data[0][0] = left.x;
	matrix.data[0][1] = left.y;
	matrix.data[0][2] = left.z;
	matrix.data[1][0] = true_up.x;
	matrix.data[1][1] = true_up.y;
	matrix.data[1][2] = true_up.z;
	matrix.data[2][0] = forward.x;
	matrix.data[2][1] = forward.y;
	matrix.data[2][2] = forward.z;
	return (matrix);
}

t_4x4	view_transform(t_tuple origin, t_tuple direction)
{
	t_tuple	up_normal;
	t_tuple	left_vector;
	t_tuple	neg_or;
	t_4x4	orientation;
	t_4x4	res;

	direction = ft_normalize(direction);
	up_normal = ft_create_vector(0, 1, 0);
	left_vector = ft_cross_product(direction, up_normal);
	orientation = ft_orientation(left_vector, up_normal, direction);
	neg_or = ft_negate_tuple(origin);
	res = ft_multiply_matrices(orientation,
			create_translation_mx(neg_or.x, neg_or.y, neg_or.z));
	return (res);
}

bool	ft_aim_camera(t_camera *cam1, float fov, char *place, char *aiming)
{
	t_tuple		direction;
	char		**aux;

	cam1->hsize = WIDTH;
	cam1->vsize = HEIGHT;
	cam1->field_of_view = fov;
	if (!ft_check_coords(place) || !ft_check_coords(aiming))
		return (free(cam1), false);
	aux = ft_split(place, ',');
	cam1->origin = ft_create_point(ft_atof(aux[0]),
			ft_atof(aux[1]), ft_atof(aux[2]));
	ft_free_array(aux);
	aux = ft_split(aiming, ',');
	direction = ft_create_vector(ft_atof(aux[0]),
			ft_atof(aux[1]), ft_atof(aux[2]));
	ft_free_array(aux);
	cam1->transform = view_transform(cam1->origin, direction);
	return (true);
}

bool	ft_create_camera(t_scene *scene, char **cam_data)
{
	float		fov;
	float		half_view;
	float		aspect;

	if (scene->camera->field_of_view != -1)
		ft_error_exit(scene, "Error\nDuplicated camera", 1);
	fov = ft_atof(cam_data[3]);
	if (fov <= 0 || 180 < fov)
		return (false);
	if (!ft_aim_camera(scene->camera, fov, cam_data[1], cam_data[2]))
		return (false);
	half_view = tanf((fov * M_PI / 180) / 2);
	aspect = (float)HEIGHT / (float)WIDTH;
	if (aspect >= 1)
	{
		scene->camera->half_width = half_view;
		scene->camera->half_height = half_view / aspect;
	}
	else
	{
		scene->camera->half_width = half_view * aspect;
		scene->camera->half_height = half_view;
	}
	scene->camera->pixel_size = (scene->camera->half_width * 2) / (double)WIDTH;
	return (true);
}
