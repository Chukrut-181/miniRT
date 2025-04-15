/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:03:48 by igchurru          #+#    #+#             */
/*   Updated: 2025/04/15 12:18:43 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

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
	if (scene->light)
		free(scene->light);
	if (scene->objects)
	{
		ft_lstclear(&scene->objects, free);
		free(scene->objects);
	}
}
