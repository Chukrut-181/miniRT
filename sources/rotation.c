/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:23:48 by igchurru          #+#    #+#             */
/*   Updated: 2025/03/18 15:18:10 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_4x4	rotation_x(float radians)
{
	t_4x4	rotation_x;

	rotation_x = ft_create_identity_matrix();
	rotation_x.data[1][1] = cosf(radians);
	rotation_x.data[1][2] = -sinf(radians);
	rotation_x.data[2][1] = sinf(radians);
	rotation_x.data[2][2] = cosf(radians);
	return (rotation_x);
}

t_4x4	rotation_y(float radians)
{
	t_4x4	rotation_y;

	rotation_y = ft_create_identity_matrix();
	rotation_y.data[0][0] = cosf(radians);
	rotation_y.data[0][2] = sinf(radians);
	rotation_y.data[2][0] = -sinf(radians);
	rotation_y.data[2][2] = cosf(radians);
	return (rotation_y);
}

t_4x4	rotation_z(float radians)
{
	t_4x4	rotation_z;

	rotation_z = ft_create_identity_matrix();
	rotation_z.data[0][0] = cosf(radians);
	rotation_z.data[0][1] = -sinf(radians);
	rotation_z.data[1][0] = sinf(radians);
	rotation_z.data[1][1] = cosf(radians);
	return (rotation_z);
}
