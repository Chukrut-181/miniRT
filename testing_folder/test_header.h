/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_header.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:39:45 by igchurru          #+#    #+#             */
/*   Updated: 2025/02/25 15:45:17 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HEADER_H
# define TEST_HEADER_H

# include <stdio.h>
# include <math.h>
# include "../include/minirt.h"

# define EPSILON 0.00001

typedef struct s_tuple
{
	float	x;
	float	y;
	float	z;
	int		w;
}	t_tuple;

/* typedef struct s_4x4
{
	float	data[4][4];
}	t_4x4;

typedef struct s_3x3
{
	float	data[3][3];
}	t_3x3;

typedef struct s_2x2
{
	float	data[2][2];
}	t_2x2; */

int		main(void);
t_tuple	ft_create_point(float x, float y, float z);
t_tuple	ft_create_vector(float x, float y, float z);
int		ft_check_equality(t_tuple *tuple1, t_tuple *tuple2);
t_tuple	ft_add_tuples(t_tuple *tuple1, t_tuple *tuple2);
t_tuple	ft_substract_tuples(t_tuple *tuple1, t_tuple *tuple2);
t_tuple	ft_multiply_tuple(t_tuple *tuple, float scalar);
t_tuple	ft_divide_tuple(t_tuple *tuple, float scalar);
t_tuple	ft_negate_tuple(t_tuple *tuple);
float	ft_calculate_magnitude(t_tuple *v);
void	ft_normalize(t_tuple *v);
float	ft_dot_product(t_tuple *v1, t_tuple *v2);
t_tuple	ft_cross_product(t_tuple *v1, t_tuple *v2);

#endif