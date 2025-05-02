/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:07:46 by igchurru          #+#    #+#             */
/*   Updated: 2025/04/22 15:23:32 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static void	setup_camera_transform(t_camera *camera)
{
	t_tuple	forward;
	t_tuple	up;
	t_tuple	right;
	t_tuple	true_up;
	t_4x4	rotation;
	t_4x4	translation;

	forward = ft_normalize(camera->v_orientation);
	
	if (fabsf(forward.y) > 0.99999f)
		up = ft_create_vector(0, 0, 1);
	else
		up = ft_create_vector(0, 1, 0);
	
	right = ft_cross_product(forward, up);
	right = ft_normalize(right);
	true_up = ft_cross_product(right, forward);

	rotation = ft_create_identity_matrix();

	rotation.data[0][0] = right.x;
	rotation.data[0][1] = right.y;
	rotation.data[0][2] = right.z;
	
	rotation.data[1][0] = true_up.x;
	rotation.data[1][1] = true_up.y;
	rotation.data[1][2] = true_up.z;
	
	rotation.data[2][0] = -forward.x;
	rotation.data[2][1] = -forward.y;
	rotation.data[2][2] = -forward.z;
	
	translation = create_translation_mx(camera->viewpoint);
	camera->transform = ft_multiply_matrices(translation, rotation);
}

static bool	ft_apply_fov(t_scene *scene, char *angle)
{
	float	aux;

	aux = ft_atof(angle);
	if (aux < 0 || 180 < aux)
		return (false);
	scene->camera->field_of_view = aux;
	return (true);
}

static bool	ft_apply_orientation_vector(t_scene *scene, char *coords)
{
	char	**split;
	float	aux;
	int		i;

	split = ft_split(coords, ',');
	if (!split)
		return (false);
	i = 0;
	while (i < 3)
	{
		aux = ft_atof(split[i]);
		if (i == 0)
			scene->camera->v_orientation.x = aux;
		else if (i == 1)
			scene->camera->v_orientation.y = aux;
		else if (i == 2)
			scene->camera->v_orientation.z = aux;
		i++;
	}
	scene->camera->v_orientation.w = 0;
	ft_free_array(split);
	return (true);
}

bool	ft_check_orientation_vector(char *orientation)
{
	char	**split;
	int		i;
	float	aux;

	split = ft_split(orientation, ',');
	if (ft_arraylen(split) > 3)
		return (ft_free_array(split), false);
	i = 0;
	while (i < 3)
	{
		aux = ft_atof(split[i]);
		if (aux < -1 || 1 < aux)
			return (ft_free_array(split), false);
		i++;
	}
	return (true);
}

static bool	ft_apply_camera_coords(t_scene *scene, char *coords)
{
	char	**split;
	float	aux;
	int		i;

	split = ft_split(coords, ',');
	if (!split)
		return (false);
	i = 0;
	while (i < 3)
	{
		aux = ft_atof(split[i]);
		if (i == 0)
			scene->camera->viewpoint.x = aux;
		else if (i == 1)
			scene->camera->viewpoint.y = aux;
		else if (i == 2)
			scene->camera->viewpoint.z = aux;
		i++;
	}
	scene->camera->viewpoint.w = 1;
	ft_free_array(split);
	return (true);
}

int	ft_create_camera(t_scene *scene, char **cam)
{
	if (scene->camera != NULL)
		return (free(scene->camera), 1);
	scene->camera = malloc(sizeof(t_camera));
	if (!ft_check_coords(cam[1]))
		return (free(scene->camera), 1);
	if (!ft_apply_camera_coords(scene, cam[1]))
		return (free(scene->camera), 1);
	if (!ft_check_orientation_vector(cam[2]))
		return (free(scene->camera), 1);
	if (!ft_apply_orientation_vector(scene, cam[2]))
		return (free(scene->camera), 1);
	if (!ft_apply_fov(scene, cam[3]))
		return (free(scene->camera), 1);
	setup_camera_transform(scene->camera);
	return (0);
}
