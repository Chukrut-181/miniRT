/* ************************************************************************** */ /*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */ /*   Created: 2025/02/19 10:28:29 by igchurru          #+#    #+#             */
/*   Updated: 2025/03/12 14:08:57 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

# include "structures.h"
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <stdio.h>
# include <unistd.h>

# define EPSILON 0.00001

# ifndef M_PI
#  define M_PI 3.1415926
# endif

typedef struct s_world
{
	t_list *objects;  // Lista de objetos (esferas, etc.)
	t_light light;    // Fuente de luz
}	t_world;

int		main(int argc, char **argv);

//	MINIRT
int		ft_minirt(void);

//	TUPLE CREATION
t_tuple	ft_create_point(float x, float y, float z);
t_tuple	ft_create_vector(float x, float y, float z);
int		ft_check_equality(t_tuple tuple1, t_tuple tuple2);

//	TUPLE OPERATIONS
t_tuple	ft_add_tuples(t_tuple tuple1, t_tuple tuple2);
t_tuple	ft_substract_tuples(t_tuple tuple1, t_tuple tuple2);
t_tuple	ft_multiply_tuple(t_tuple tuple, float scalar);
t_tuple	ft_divide_tuple(t_tuple tuple, float scalar);
t_tuple	ft_negate_tuple(t_tuple tuple);
t_tuple	ft_multiply_colors(t_tuple c1, t_tuple c2);

//	VECTOR OPERATIONS
float	ft_calculate_magnitude(t_tuple v);
t_tuple	ft_normalize(t_tuple v);
float	ft_dot_product(t_tuple v1, t_tuple v2);
t_tuple	ft_cross_product(t_tuple v1, t_tuple v2);

//	MATRIX OPERATIONS
int		ft_check_matrix_equality(t_4x4 matrix1, t_4x4 matrix2);
t_4x4	ft_multiply_matrices(t_4x4 matrix1, t_4x4 matrix2);
t_tuple	ft_multiply_mat_and_tuple(t_4x4 matrix, t_tuple tuple);
t_4x4	ft_find_inverse(t_4x4 matrix);

// MATRIX DETERMINANT
float	ft_calculate_determinant(t_4x4 matrix);
float	ft_determinant_3x3(t_3x3 submx);

// MATRIX TRANSFOMATION
t_4x4	ft_create_identity_matrix(void);
t_4x4	create_translation_mx(t_tuple tuple);
t_4x4	create_scalation_mx(t_tuple tuple);
t_4x4	ft_create_shearing_mx(float Xy, float Xz, float Yx, float Yz, float Zx, float Zy);

// 	ROTATION
t_4x4	rotation_z(double radians);
t_4x4	rotation_x(double radians);
t_4x4	rotation_y(double radians);

//	RAY
t_ray	ft_create_ray(t_tuple origin, t_tuple direction);
t_tuple	ft_position(t_ray ray, float t);
t_list	*ft_intersection(t_ray ray, t_sphere sphere, t_list *xs_list);

//	LIGHT
t_material	ft_create_material(float x, float y, float z);
t_tuple	normal_at(t_sphere sphere, t_tuple world_point);
t_tuple	reflect(t_tuple in, t_tuple normal);
t_light	point_light(t_tuple position, t_tuple intensity);
t_tuple	lighting(t_material mat, t_light light, t_tuple point, t_tuple eyev, t_tuple normalv);

//	CAMERA
t_4x4	view_transform(t_tuple from, t_tuple to, t_tuple up);
t_camera	ft_create_camera(int hsize, int vsize, float field_of_view);
t_camera	ft_camera(int hsize, int vsize, float field_of_view);
t_ray	ray_for_pixel(t_camera c, float px, float py);
mlx_image_t *ft_render(mlx_t *mlx, t_camera camera, t_world world);

//	WORLD
t_world ft_default_world(void);
t_list *ft_find_hit(t_list *intersections);
t_comps	prepare_computations(t_list *intersection, t_ray ray);
t_list *ft_intersect_world(t_world world, t_ray ray);
t_tuple	shade_hit(t_world world, t_comps comps);
t_tuple	color_at(t_world world, t_ray ray);

//	THINGS
t_sphere	*ft_create_sphere(t_tuple point, float r);
void	ft_identify_hit(t_list *xs_list);

//	HOOKS
void	ft_handle_key(mlx_key_data_t keydata, void *param);

// 	ERROR EXIT
int	ft_error_exit(char *err_msg, int err_code);

//	TEST FUNCTIONS (to be removed)
void	ft_minigun(mlx_image_t	*image);
void	ft_draw_clock(mlx_image_t *image);
int	ft_test_matrix_functions(void);
int	ft_test_ray(void);
int	ft_test_intersection(void);
void	ft_render_sphere(mlx_image_t *image);
void	test_reflection();
void	test_lighting();
void 	render_lit_sphere(mlx_image_t *image);
t_tuple	color_at(t_world world, t_ray ray);

# endif
