/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:26:57 by igchurru          #+#    #+#             */
/*   Updated: 2025/02/24 10:53:30 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	ft_draw_large_pixel(mlx_image_t	*image, int x, int y, int size)
{
	int	w;
	int	h;

	h = 0;
	while(h < size)
	{
		w = 0;
		while (w < size)
		{
			mlx_put_pixel(image, x + w, (1800 - y + h), 0xFF0000FF);
			w++;
		}
		h++;
	}
}

void	ft_minigun(mlx_image_t	*image)
{
	t_tuple	bullet;
	t_tuple	velocity;
	t_tuple	gravity;
	t_tuple	wind;
	t_tuple	environment;
	int		i;
	float	l;

	bullet = ft_create_point(0, 1, 0);						//	A point in space.
	velocity = ft_create_vector(1, 1, 0);					//	A vector representing movement.
	ft_normalize(&velocity);
	velocity = ft_multiply_tuple(&velocity, 1.5);								//	Muzzle speed is 1 click per tick.
	gravity = ft_create_vector(0, -0.1, 0);					//	A vector representing gravity.
	wind = ft_create_vector(-0.01, 0, 0);					//	A vector representing drag.
	environment = ft_add_tuples(&gravity, &wind);			//	Environment is gravity + drag
	i = 0;
	l = 0;
	while(bullet.y > 0)										//	While bullet is above ground
	{
		ft_draw_large_pixel(image, (bullet.x * 100), (bullet.y * 100), 10);
		velocity = ft_add_tuples(&velocity, &environment);	//	Modify velocity with environment
		bullet = ft_add_tuples(&bullet, &velocity);			//	Move bullet with velocity
		l += velocity.x;									//	Measure distance
		i++;												//	Count 'time'
	}
	printf("Bullet hit the ground in %i ticks and travelled %f clicks.\n", i, l);
}

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 2)
		ft_error_exit("Error\nUsage: ./miniRT <arg1>", 1);
	else
		ft_minirt();
	return (0);
}
