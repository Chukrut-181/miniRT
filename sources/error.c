/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:03:48 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/15 11:09:20 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	ft_error_exit(t_scene *scene, char *err_msg, int err_code)
{
	if (scene)
		ft_free_scene(scene);
	ft_printf("%s\n", err_msg);
	exit (err_code);
}

void	ft_free_scene(t_scene *scene)
{
	if (scene->ambient)
		free(scene->ambient);
	if (scene->camera)
		free(scene->camera);
	if (scene->world)
	{
		if (scene->world->objects)
			ft_lstclear(&scene->world->objects, free);
		if (scene->world->light)
			free(scene->world->light);
		free(scene->world);
	}
	if (scene->image)
		mlx_delete_image(scene->mlx, scene->image);
	if (scene->mlx)
		mlx_terminate(scene->mlx);
	free(scene);
}
