/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: igchurru <igchurru@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/03/05 12:43:31 by igchurru		  #+#	#+#			 */
/*   Updated: 2025/04/10 15:57:04 by eandres          ###   ########.fr       */
/*																			*/
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
	t_tuple	color;
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
	t_tuple		color;
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

typedef struct s_intersection
{
	void	*object;
	float	time;
	t_tuple	point;
	int	hit;
}	t_xs;

typedef struct s_quadratic_equation_data
{
	float	discriminant;
	float	a;
	float	b;
	float	c;
}	t_abcd;
//
//typedef struct s_light
//{
//	t_tuple	intensity;
//	t_tuple position;
//}	t_light;

typedef struct s_light
{
	t_tuple	source;
	t_tuple	intensity;
	t_color	color;
}	t_light;

typedef struct s_world
{
	t_list *objects;  // Lista de objetos (esferas, etc.)
	t_light light;    // Fuente de luz
}	t_world;

typedef struct s_comps
{
	void	*object;
	float	time;
	t_tuple	point;
	t_tuple	eyev;
	t_tuple	normalv;
	bool	inside;
}	t_comps;

typedef struct s_camera
{
//	int	hsize;
//	int	vsize;
//	float	pixel_size;
//	float	half_width;
//	float	half_height;
	t_tuple	viewpoint;
	t_tuple	v_orientation;
	float	field_of_view;
	t_4x4	transform;
}	t_camera;

typedef struct s_ambient
{
	t_color	color;
	float	ratio;
}	t_ambient;

typedef struct s_scene
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_camera	*camera;
	t_ambient	*ambient;
	t_light		*light;
	t_list		*objects;
}	t_scene;

#endif
