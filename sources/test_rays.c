/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:34:10 by igchurru          #+#    #+#             */
/*   Updated: 2025/03/07 13:32:19 by igchurru         ###   ########.fr       */
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

	time = 12.55479;
	gun = *ft_create_point(0, 0, -5);
	direction = *ft_create_vector(0, 0, 1);
	blast = ft_create_ray(gun, direction);
	printf("Given a point of origin %.4f %.4f %.4f %i\n", blast.origin.x, blast.origin.y, blast.origin.z, blast.origin.w);
	printf("and a direction vector %.4f %.4f %.4f %i\n", blast.direction.x, blast.direction.y, blast.direction.z, blast.direction.w);
	printf("we can see that, in %f ticks\n", time);
	position = ft_position(blast, time);
	printf("the ray will reach coordinates %.4f %.4f %.4f\n", position.x, position.y, position.z);
	return (0);
}

int	ft_test_intersection(void)
{
	t_ray		beam;
	t_sphere	ball;
	t_list		*xs_list;
	t_xs		*aux;

	beam = ft_create_ray(*ft_create_point(0.0, 0.0, -5.0), *ft_create_vector(0.0, 0.0, 1));
	ball = *ft_create_sphere(*ft_create_point(0.0, 0.0, 0.0), 1.0);
	xs_list = NULL;
	xs_list = ft_intersection(beam, ball, xs_list);
	if (!xs_list)
		return (printf("No intersection detected\n"));
	while (xs_list)
	{
		aux = (t_xs *)(xs_list->content);
		printf("\nObject intersected: %s\n", (char *)aux->object);
		printf("XS data: Time = %.3f, Coords %.3f, %.3f, %.3f\n", aux->time, aux->point.x, aux->point.y, aux->point.z);
		if (aux->hit == 1)
			printf("That was a hit!\n");
		xs_list = xs_list->next;
		free(aux);
	}
	return (0);
}
