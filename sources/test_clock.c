/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_clock.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:47:46 by igchurru          #+#    #+#             */
/*   Updated: 2025/03/04 15:56:20 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	ft_draw_large_pixel(mlx_image_t	*image, int x, int y, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_put_pixel(image, x + i, y + j, 0xFFFFFFFF);
			j++;
		}
		i++;
	}
}

void	ft_draw_clock(mlx_image_t *image)
{
	t_tuple		twelve_oclock;
	t_tuple		hour_position;
	t_4x4		*rotation_matrix;
	t_4x4		*translation_matrix;
	t_4x4		*shearing_matrix;
	t_4x4		*transformation_matrix;
	int			hour;
	double		angle;
	int			center_x;
	int			center_y;
	int			radius;

	center_x = image->width / 2;
	center_y = image->height / 2;
	radius = 500;
	translation_matrix = create_translation_mx
		(ft_create_point(image->width / 2, image->height / 2, 0));
	shearing_matrix = ft_create_shearing_mx(ft_create_point(-0.3, 0, 0));
	twelve_oclock = *ft_create_point(0, -radius, 0);
	ft_draw_large_pixel(image, center_x, center_y, 10);
	hour = 0;
	while (hour < 12)
	{
		angle = (float)hour * (2 * M_PI / 12);
		rotation_matrix = rotation_z(angle);
		transformation_matrix = ft_multiply_matrices(translation_matrix, ft_multiply_matrices(shearing_matrix, rotation_matrix));
		hour_position = *ft_multiply_mat_and_tuple(transformation_matrix, &twelve_oclock);
		printf("X = %9.3f, Y = %9.3f\n", hour_position.x, hour_position.y);
		ft_draw_large_pixel (image, (int)hour_position.x, (int)hour_position.y, 15);
		free(rotation_matrix);
		free(transformation_matrix);
		hour++;
	}
	free(translation_matrix);
	free(shearing_matrix);
}
