/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:34:10 by igchurru          #+#    #+#             */
/*   Updated: 2025/03/05 15:45:41 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	ft_test_ray(void)
{
	t_tuple	gun;
	t_tuple	direction;
	t_ray	blast;
	float	time;
	t_tuple	position;

	time = 16.55479;
	gun = *ft_create_point(0, 0, -5);
	direction = *ft_create_vector(0, 0, 1);
	blast = ft_create_ray(gun, direction);
	printf("Given a point of origin %.4f %.4f %.4f %i\n", blast.origin.x, blast.origin.y, blast.origin.z, blast.origin.w);
	printf("and a direction vector %.4f %.4f %.4f %i\n", blast.direction.x, blast.direction.y, blast.direction.z, blast.direction.w);
	printf("we can see that, in %f ticks\n", time);
	position = ft_position(blast, time);
	printf("the ray will reach coordinates %.4f %.4f %.4f %i\n", position.x, position.y, position.z, position.w);
	return (0);
}

int ft_test_intersection(void)
{
	t_ray		beam;
	t_sphere	ball;
	float		*time;

	beam = ft_create_ray(*ft_create_point(0, 0, -5), *ft_create_vector(0, 0, 1));
	ball = *ft_create_sphere(*ft_create_point(0, 0, 0), 1);
	time = ft_intersection(beam, ball);
	printf("Time of X1 = %.5f\n", *time++);
	printf("Time of X2 = %.5f\n", *time);
	return (0);
}
