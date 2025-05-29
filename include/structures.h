/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:58:02 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/29 12:19:50 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "../lib/minilibx/mlx.h"
# include "../lib/libft/libft.h"
# include <stdbool.h>

typedef struct s_tuple
{
	double	x;
	double	y;
	double	z;
	int		w;
}	t_tuple;

typedef struct s_4x4
{
	double	data[4][4];
}	t_4x4;

typedef struct s_3x3
{
	double	data[3][3];
}	t_3x3;

typedef struct s_ray
{
	t_tuple	origin;
	t_tuple	direction;
}	t_ray;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

typedef struct s_material
{
	t_color	color;
	double	ambient;
	double	diffuse;
	double	specular;
	double	shininess;
}	t_material;

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE,
	CUBE,
	TORUS,
}	t_type;

typedef struct s_quadratic_equation_data
{
	double	discriminant;
	double	a;
	double	b;
	double	c;
}	t_abcd;

typedef struct s_light
{
	t_tuple	source;
	t_color	l_color;
	double	intensity;
}	t_light;

typedef struct s_ambient
{
	t_color	a_color;
	double	ratio;
}	t_ambient;

typedef struct s_world
{
	t_list		*objects;
	t_ambient	*ambient;
	t_light		*light;
}	t_world;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}	t_point;

typedef struct s_camera
{
	double	field_of_view;
	double	pixel_size;
	double	half_width;
	double	half_height;
	t_4x4	transform;
	t_tuple	origin;
}	t_camera;

typedef struct s_img
{
	void	*img_ptr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	void	*data;
}			t_img;

typedef struct s_scene
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_camera	*camera;
	t_world		*world;
}	t_scene;

typedef struct s_shape
{
	t_4x4		inverse_matrix;
	t_4x4		transform_matrix;
	t_material	material;
	t_ray		ray_in_obj_space;
	t_type		type;
}	t_shape;

typedef struct s_intersection
{
	bool	intersec;
	int		hit;
	t_shape	*object;
	double	time;
	double	min;
	double	max;
	t_tuple	point;
	t_tuple	normal;
	t_color	color;
}	t_xs;

typedef struct s_comps
{
	t_shape	*object;
	double	time;
	t_tuple	point;
	t_tuple	over_point;
	t_tuple	eyev;
	t_tuple	normalv;
	t_tuple	reflectv;
	bool	inside;
}	t_comps;

typedef struct s_lighting
{
	t_tuple	lightv;
	t_color	ambient;
	t_color	diffuse;
	t_color	specular;
	t_tuple	reflectv;
	double	factor;
	double	reflect_dot_eye;
}	t_lighting;

#endif
