/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:43:31 by igchurru          #+#    #+#             */
/*   Updated: 2025/03/07 12:57:17 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <stdbool.h>

typedef struct s_tuple
{
	float	x;
	float	y;
	float	z;
	int		w;
}	t_tuple;

typedef struct s_4x4
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
}	t_2x2;

typedef struct s_ray
{
	t_tuple	origin;
	t_tuple	direction;
}	t_ray;

typedef struct s_sphere
{
	t_tuple	center;
	float	radius;
	t_4x4	*transform;
}	t_sphere;

typedef struct s_intersection
{
	void	*object;
	float	time;
	t_tuple	point;
	bool	hit;
}	t_xs;

typedef struct s_quadratic_equation_data
{
	float	discriminant;
	float	a;
	float	b;
	float	c;
}	t_abcd;

#endif