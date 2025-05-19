/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:10:34 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/19 12:30:10 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	key_hook(int keycode, t_scene *data)
{
	if (keycode == 65307)
	{
		printf("ESC key pressed. Exiting.\nThanks for using miniRT!\n");
		mlx_destroy_image(data->mlx, data->img.img_ptr);
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		ft_free_scene(data);
		exit (0);
	}
	else
		return (0);
}

int	close_hook(t_scene *data)
{
	printf("X button pressed. Exiting.\nThanks for using miniRT!\n");
	mlx_destroy_image(data->mlx, data->img.img_ptr);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	ft_free_scene(data);
	exit(0);
	return (0);
}
