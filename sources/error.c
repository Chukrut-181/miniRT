/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:03:48 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/26 11:20:20 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	free_intersections(t_xs **inter, t_list **xs)
{
	t_list	*temp;

	if ((*inter)->time == 0)
		free(*inter);
	while (*xs)
	{
		temp = (*xs)->next;
		free((*xs)->content);
		free(*xs);
		*xs = temp;
	}
}

int	ft_error_exit(t_scene *failed_scene, char *err_msg, int err_code)
{
	if (failed_scene)
		ft_free_scene(failed_scene);
	ft_printf("%s\n", err_msg);
	exit (err_code);
}

void	ft_free_scene(t_scene *scene)
{
	if (scene->camera)
		free(scene->camera);
	if (scene->world)
	{
		if (scene->world->objects)
			ft_lstclear(&scene->world->objects, free);
		if (scene->world->light)
			free(scene->world->light);
		if (scene->world->ambient)
			free(scene->world->ambient);
		free(scene->world);
	}
	free(scene);
}
