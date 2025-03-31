/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_minigun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandres <eandres@student.42urduliz.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:39:24 by igchurru          #+#    #+#             */
/*   Updated: 2025/03/19 21:03:12 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

/* void	ft_draw_large_pixel(mlx_image_t	*image, int x, int y, int size)
{
	int	w;
	int	h;

	h = 0;
	while (h < size)
	{
		w = 0;
		while (w < size)
		{
			mlx_put_pixel(image, x + w, (1800 - y + h), 0xFF0000FF);
			w++;
		}
		h++;
	}
} */

void	ft_minigun(mlx_image_t	*image)
{
	t_tuple	*bullet;
	t_tuple	*velocity;
	t_tuple	*gravity;
	t_tuple	*wind;
	t_tuple	*environment;
	int		i = 0;
	float	l = 0;

	bullet = ft_create_point(0, 10, 0);
	velocity = ft_create_vector(1, 1, 0);
	ft_normalize(&velocity);
	velocity = ft_multiply_tuple(&velocity, 1.5);
	gravity = ft_create_vector(0, -0.1, 0);
	wind = ft_create_vector(-0.05, 0, 0);
	environment = ft_add_tuples(&gravity, &wind);
	while (bullet->y > 0)
	{
		ft_draw_large_pixel(image, (bullet->x * 100), (bullet->y * 100), 10);
		velocity = ft_add_tuples(&velocity, &environment);
		bullet = ft_add_tuples(&bullet, &velocity);
		l += velocity->x;
		i++;
	}
	printf("Touchdown in %i ticks at a distance of %f clicks.\n", i, l);
}
