/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_determinant.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:10:23 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/16 12:48:27 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

/**
 * ft_determinant_3x3 - Calculates the determinant of a 3x3 matrix.
 * 
 * This function computes the determinant of a 3x3 matrix using the cofactor 
 * expansion along the first row. The determinant is calculated as the sum 
 * of the products of the elements in the first row and their corresponding 
 * 2x2 minors, with appropriate signs applied based on the position of each 
 * element. The formula used is:
 * 
 * det = a * (ei - fh) - b * (di - fg) + c * (dh - eg)
 * 
 * where the 3x3 matrix is:
 * 
 * | a b c |
 * | d e f |
 * | g h i |
 * 
 * param submx: A t_3x3 structure representing the 3x3 matrix for which the 
 *              determinant is to be calculated.
 * 
 * Return The determinant of the 3x3 matrix.
 */
float	ft_determinant_3x3(t_3x3 submx)
{
	return (submx.data[0][0] * (submx.data[1][1] * submx.data[2][2]
		- submx.data[1][2] * submx.data[2][1])
		- submx.data[0][1] * (submx.data[1][0] * submx.data[2][2]
		- submx.data[1][2] * submx.data[2][0])
		+ submx.data[0][2] * (submx.data[1][0] * submx.data[2][1]
		- submx.data[1][1] * submx.data[2][0]));
}

/**
 * ft_get_3x3_submatrix - 	Extracts a 3x3 submatrix from a 4x4 matrix
 * 							by excluding a specific column.
 * 
 * This function generates a 3x3 submatrix from a given 4x4 matrix by removing 
 * the specified column, defined by the `exc_col` parameter.
 * 
 * param matrix: A t_4x4 structure representing the original 4x4 matrix.
 * param exc_col: The index of the column to be excluded (0 to 3).
 * 
 * Return A t_3x3 structure representing the 3x3 submatrix after excluding the 
 *         specified column.
 */
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

/**
 * ft_calculate_determinant - Calculates the determinant of a 4x4 matrix.
 * 
 * This function computes the determinant of a 4x4 matrix using the cofactor
 * expansion along the first row. The determinant is calculated as the sum of
 * the products of each element in the first row and its corresponding cofactor.
 * The sign alternates between positive and negative for each cofactor, and the
 * determinant of a 3x3 minor is computed recursively using a helper function
 * (`ft_determinant_3x3`). The result is the determinant of the original matrix.
 * 
 * param matrix: A t_4x4 structure representing the matrix for which the 
 *               determinant is to be calculated.
 * 
 * Return: The determinant of the 4x4 matrix.
 */
float	ft_calculate_determinant(t_4x4 matrix)
{
	float	det;
	t_3x3	submatrix;
	int		sign;
	int		col;

	det = 0;
	sign = 1;
	col = 0;
	while (col < 4)
	{
		submatrix = ft_get_3x3_submatrix(matrix, col);
		det += sign * matrix.data[0][col] * ft_determinant_3x3(submatrix);
		sign = -sign;
		col++;
	}
	return (det);
}

/**
 * ft_transpose - Transposes a 4x4 matrix and returns the resulting matrix.
 * 
 * Transposing a matrix involves swapping its rows and columns,
 * so the element at position `[i][j]` in the original matrix becomes
 * the element at position `[j][i]` in the transposed matrix. 
 * 
 * param matrix: A t_4x4 structure representing the matrix to be transposed.
 * 
 * Return: A t_4x4 structure representing the transposed matrix.
 */
t_4x4	ft_transpose(t_4x4 matrix)
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
