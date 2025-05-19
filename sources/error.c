/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:03:48 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/19 11:45:37 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

/* int	key(int keycode, t_scene *scene)
{
	if (keycode == 53)
	{
		mlx_destroy_window(scene->mlx, scene->win);
		ft_free_scene(scene);
		exit (0);
	}
	return (0);
} */

int	ft_error_exit(char *err_msg, int err_code)
{
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
	free(scene);
}
