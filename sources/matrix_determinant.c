/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_determinant.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:10:23 by igchurru          #+#    #+#             */
/*   Updated: 2025/02/25 15:55:21 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static float	ft_determinant_3x3(t_3x3 submx)
{
	return (submx.data[0][0] * (submx.data[1][1] * submx.data[2][2]
		- submx.data[1][2] * submx.data[2][1])
		- submx.data[0][1] * (submx.data[1][0] * submx.data[2][2]
		- submx.data[1][2] * submx.data[2][0])
		+ submx.data[0][2] * (submx.data[1][0] * submx.data[2][1]
		- submx.data[1][1] * submx.data[2][0]));
}

static void	ft_get_3x3_submatrix(t_4x4 *matrix, t_3x3 *submatrix, int exclude_col)
{
	int	row;
	int	i;
	int	col_offset;
	int	j;

	row = 1;
	i = 0;
	while (i < 3)
	{
		col_offset = 0;
		j = 0;
		while (j < 4)
		{
			if (j != exclude_col)
			{
				submatrix->data[i][col_offset] = matrix->data[row + i][j];
				col_offset++;
			}
			j++;
		}
		i++;
	}
}

float	ft_calculate_determinant(t_4x4 *matrix)
{
	float	determinant;
	t_3x3	submatrix;
	int		sign;
	int		col;

	determinant = 0;
	sign = 1;
	col = 0;
	while (col < 4)
	{
		ft_get_3x3_submatrix(matrix, &submatrix, col);
		determinant += sign * matrix->data[0][col] * ft_determinant_3x3(submatrix);
		sign = -sign;
		col++;
	}
	return (determinant);
}
