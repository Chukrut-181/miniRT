/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_minigun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:39:24 by igchurru          #+#    #+#             */
/*   Updated: 2025/03/14 10:45:33 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static void	ft_draw_large_pixel(mlx_image_t	*image, int x, int y, int size)
{
	int	i;
	int	j;
	int	r;

	r = size / 2;
	i = -r;
	while (i <= r)
	{
		j = -r;
		while (j <= r)
		{
			if ((i * i) + (j * j) <= (r * r))
				mlx_put_pixel(image, x + i, y + j, 0xFFFFFFFF);
			j++;
		}
		i++;
	}
}

void	ft_minigun(mlx_image_t	*image)
{
	t_tuple	bullet;
	t_tuple	velocity;
	t_tuple	gravity;
	t_tuple	wind;
	t_tuple	environment;
	int		i = 0;
	float	l = 0;

	bullet = ft_create_point(0, 10, 0);
	velocity = ft_create_vector(1, 1, 0);
	velocity = ft_normalize(velocity);
	velocity = ft_multiply_tuple(velocity, 1.5);
	gravity = ft_create_vector(0, -0.1, 0);
	wind = ft_create_vector(-0.05, 0, 0);
	environment = ft_add_tuples(gravity, wind);
	while (bullet.y > 0)
	{
		ft_draw_large_pixel(image, (bullet.x * 100), (bullet.y * 100), 10);
		velocity = ft_add_tuples(velocity, environment);
		bullet = ft_add_tuples(bullet, velocity);
		l += velocity.x;
		i++;
	}
	printf("Touchdown in %i ticks at a distance of %f clicks.\n", i, l);
}
