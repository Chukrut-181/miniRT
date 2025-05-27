/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:23:12 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/21 12:44:37 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_4x4	create_identity_matrix(void)
{
	t_4x4	idmatrix;
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i == j)
				idmatrix.data[i][j] = 1;
			else
				idmatrix.data[i][j] = 0;
			j++;
		}
		i++;
	}
	return (idmatrix);
}

t_4x4	create_translation_mx(float x, float y, float z)
{
	t_4x4	translation_mx;

	translation_mx = create_identity_matrix();
	translation_mx.data[0][3] = x;
	translation_mx.data[1][3] = y;
	translation_mx.data[2][3] = z;
	return (translation_mx);
}

t_4x4	create_scaling_mx(float x, float y, float z)
{
	t_4x4	scaling_mx;

	scaling_mx = create_identity_matrix();
	scaling_mx.data[0][0] = x;
	scaling_mx.data[1][1] = y;
	scaling_mx.data[2][2] = z;
	return (scaling_mx);
}

/* t_4x4	create_shearing_mx
		(float Xy, float Xz, float Yx, float Yz, float Zx, float Zy)
{
	t_4x4	shearing_mx;

	shearing_mx = create_identity_matrix();
	shearing_mx.data[0][1] = Xy;
	shearing_mx.data[0][2] = Xz;
	shearing_mx.data[1][0] = Yx;
	shearing_mx.data[1][2] = Yz;
	shearing_mx.data[2][0] = Zx;
	shearing_mx.data[2][1] = Zy;
	return (shearing_mx);
} */
