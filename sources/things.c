/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   things.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:42:33 by igchurru          #+#    #+#             */
/*   Updated: 2025/03/19 17:33:30 by eandres          ###   ########.fr       */
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
	sphere->transform = ft_create_identity_matrix();
	return (sphere);
}
