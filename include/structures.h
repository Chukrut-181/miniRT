/* ************************************************************************** */
/*									      */
/*						       	:::	  ::::::::    */
/*   structures.h                                       :+:      :+:    :+:   */
/*							+:+ +:+		 +:+	      */ /*   By: igchurru <igchurru@student.42.fr>     	  +#+  +:+	   +#+*/ /*							+#+#+#+#+#+   +#+     */
/*   Created: 2025/03/05 12:43:31 by igchurru		  #+#	#+#	      */
/*   Updated: 2025/05/07 11:08:16 by eandres          ###   ########.fr       */
/*            							              */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
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

typedef struct s_color
{
	float	r;
	float	g;
	float	b;
}	t_color;

typedef struct s_material
{
	t_color	color;
	float	a_ratio;
	t_color	a_color;
	float	ambient;   // 0-1
	float	diffuse;   // 0-1
	float	specular;  // 0-1
	float	shininess; // 10-200
	
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

typedef struct s_sphere
{
	t_type		type;
	t_tuple		center;
	float		diameter;
	t_4x4		transform;
	//t_tuple		color;
	t_material	material;
}	t_sphere;

typedef struct s_cylinder
{
	t_type		type;
	t_tuple		center;
	t_tuple		axis_vector;
	float		diameter;
	float		height;
	t_4x4		*transform;
	t_material	material;
}	t_cyl;

 typedef struct s_plane
{
	t_type		type;
	t_tuple		point_in_plane;
	t_tuple		n_n_vector;
	t_4x4		*transform;
	t_material	material;
}	t_plane;

typedef struct s_quadratic_equation_data
{
	float	discriminant;
	float	a;
	float	b;
	float	c;
}	t_abcd;

typedef struct s_light
{
	t_tuple	source;
	t_color	l_color;
	float	intensity; // 0-1
}	t_light;

typedef struct s_world
{
	t_list *objects;  // Lista de shapes
	t_light light;    // Fuente de luz
	int		shape_count;
}	t_world;

typedef struct s_comps
{
	t_shape	*object;
	float	time;
	t_tuple	point;
	t_tuple	over_point;
	t_tuple	eyev;
	t_tuple	normalv;
	bool	inside;
}	t_comps;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}	t_point;

typedef struct s_camera
{
	double	hsize;
	double	vsize;
	double	field_of_view;
	double	pixel_size;
	double	half_width;
	double	half_height;
	t_4x4	transform;
	int		init;
	t_tuple	origin;
}	t_camera;

typedef struct s_ambient
{
	t_color	a_color;
	float	ratio;
}	t_ambient;

typedef struct s_scene
{
	mlx_t		*mlx;
	t_img		img;
	mlx_image_t	*image;
	t_camera	*camera;
	t_ambient	*ambient;
	t_light		*light;
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
	float	time;
	float	min;
	float	max;
	t_tuple	point;
	t_tuple normal;
	t_color color;
}	t_xs;

typedef struct s_lighting
{
	t_tuple	lightv;
	t_color	ambient;
	t_color diffuse;
	t_color specular;
	t_tuple reflectv;
	float	factor;
	float	reflect_dot_eye;
}	t_lighting;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

#endif
