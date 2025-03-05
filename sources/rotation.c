/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:23:48 by igchurru          #+#    #+#             */
/*   Updated: 2025/03/05 10:23:49 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_4x4	*rotation_x(double radians)
{
	t_4x4	*rotation_x;

	rotation_x = ft_create_identity_matrix();
	rotation_x->data[1][1] = cos(radians);
	rotation_x->data[1][2] = -sin(radians);
	rotation_x->data[2][1] = sin(radians);
	rotation_x->data[2][2] = cos(radians);
	return (rotation_x);
}

t_4x4	*rotation_y(double radians)
{
	t_4x4	*rotation_y;

	rotation_y = ft_create_identity_matrix();
	rotation_y->data[0][0] = cos(radians);
	rotation_y->data[0][2] = sin(radians);
	rotation_y->data[2][0] = -sin(radians);
	rotation_y->data[2][2] = cos(radians);
	return (rotation_y);
}

t_4x4	*rotation_z(double radians)
{
	t_4x4	*rotation_z;

	rotation_z = ft_create_identity_matrix();
	rotation_z->data[0][0] = cos(radians);
	rotation_z->data[0][1] = -sin(radians);
	rotation_z->data[1][0] = sin(radians);
	rotation_z->data[1][1] = cos(radians);
	return (rotation_z);
}
