/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:09:24 by igchurru          #+#    #+#             */
/*   Updated: 2025/02/26 11:05:51 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	ft_minirt(void)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx = mlx_init(2400, 1800, "miniRT", true);
	image = mlx_new_image(mlx, 2400, 1800);
	mlx_image_to_window(mlx, image, 0, 0);
	mlx_key_hook(mlx, ft_handle_key, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
