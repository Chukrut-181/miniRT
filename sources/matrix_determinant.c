/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_determinant.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:10:23 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/29 12:19:50 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

double	determinant_3x3(t_3x3 submx)
{
	return (submx.data[0][0] * (submx.data[1][1] * submx.data[2][2]
		- submx.data[1][2] * submx.data[2][1])
		- submx.data[0][1] * (submx.data[1][0] * submx.data[2][2]
		- submx.data[1][2] * submx.data[2][0])
		+ submx.data[0][2] * (submx.data[1][0] * submx.data[2][1]
		- submx.data[1][1] * submx.data[2][0]));
}

static t_3x3	ft_get_3x3_submatrix(t_4x4 matrix, int exc_col)
{
	int		row;
	int		i;
	int		col_offset;
	int		j;
	t_3x3	submatrix;

	row = 1;
	i = 0;
	while (i < 3)
	{
		col_offset = 0;
		j = 0;
		while (j < 4)
		{
			if (j != exc_col)
			{
				submatrix.data[i][col_offset] = matrix.data[row + i][j];
				col_offset++;
			}
			j++;
		}
		i++;
	}
	return (submatrix);
}

double	calculate_determinant(t_4x4 matrix)
{
	double	det;
	t_3x3	submatrix;
	int		sign;
	int		col;

	det = 0;
	sign = 1;
	col = 0;
	while (col < 4)
	{
		submatrix = ft_get_3x3_submatrix(matrix, col);
		det += sign * matrix.data[0][col] * determinant_3x3(submatrix);
		sign = -sign;
		col++;
	}
	return (det);
}

t_4x4	transpose(t_4x4 matrix)
{
	t_4x4	transposed;
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			transposed.data[i][j] = matrix.data[j][i];
			j++;
		}
		i++;
	}
	return (transposed);
}
