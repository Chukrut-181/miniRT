/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:34:10 by igchurru          #+#    #+#             */
/*   Updated: 2025/03/05 12:02:03 by igchurru         ###   ########.fr       */
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
