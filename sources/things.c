/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   things.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:42:33 by igchurru          #+#    #+#             */
/*   Updated: 2025/03/05 12:48:38 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_sphere	*ft_create_sphere(t_tuple point, float r)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->center.x = point.x;
	sphere->center.y = point.y;
	sphere->center.z = point.z;
	sphere->radius = r;
	sphere->transform = NULL;
	return (sphere);
}
