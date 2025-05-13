/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:03:36 by igchurru          #+#    #+#             */
/*   Updated: 2025/04/15 12:36:41 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	key(int keycode, t_scene *scene)
{
	if (keycode == 53)
	{
		mlx_destroy_window(scene->mlx, scene->mlx);
		ft_free_scene(scene);
		exit (0);
	}
	return (0);
}
