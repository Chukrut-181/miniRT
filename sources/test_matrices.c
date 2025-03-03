/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_matrices.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:41:59 by igchurru          #+#    #+#             */
/*   Updated: 2025/03/03 15:59:07 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"
#include <time.h>
#include <limits.h>

static void	ft_print_4x4(t_4x4 *matrix)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			printf("%10.5f ", matrix->data[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
}

t_4x4 *ft_randomize_matrix(void)
{
	t_4x4	*random_mx;
	float	temp;
	int		i;
	int		j;

	random_mx = ft_create_identity_matrix();
	srand(time(NULL));
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			temp = (rand() / 10000000) + (float)rand() / 10000000000;
			if (rand() % 2 == 0)
				temp = -temp;
			random_mx->data[i][j] = temp;
			j++;
		}
		i++;
	}
	return (random_mx);
	
}

int ft_test_matrix_functions(void)
{
	t_4x4 *testmx1;
	t_4x4 *testmx2;

	testmx1 = ft_randomize_matrix();
	printf("This is testmx1:\n");
	ft_print_4x4(testmx1);
	testmx2 = ft_randomize_matrix();
	printf("And this is testmx2:\n");
	ft_print_4x4(testmx2);
	printf("Determinant of testmx1 is %f, and of testmx2 is %f\n", ft_calculate_determinant(testmx1), ft_calculate_determinant(testmx2));
	return (0);
}

