/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v0                                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:08:55 by v0                #+#    #+#             */
/*   Updated: 2025/05/07 13:02:00 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include "structures.h"

# define EPSILON 0.00001

# define HEIGHT 1800
# define WIDTH 2400

# ifndef M_PI
#  define M_PI 3.1415926
# endif

//	MAIN
int	main(int argc, char **argv);

//	TUPLE CREATION
t_color	ft_create_color(float x, float y, float z);
t_tuple	ft_create_point(float x, float y, float z);
t_tuple	ft_create_vector(float x, float y, float z);
int		ft_check_equality(t_tuple tuple1, t_tuple tuple2);
t_tuple	point_tp(t_point p);
t_tuple	color_tp(t_color p);

//	TUPLE OPERATIONS
t_tuple	ft_add_tuples(t_tuple tuple1, t_tuple tuple2);
t_tuple	ft_substract_tuples(t_tuple tuple1, t_tuple tuple2);
t_tuple	ft_multiply_tuple_f(t_tuple tuple, float scalar);
t_tuple	ft_divide_tuple(t_tuple tuple, float scalar);
t_tuple	ft_negate_tuple(t_tuple tuple);
t_color	ft_multiply_color_f(t_color tuple, float scalar);
t_color	ft_add_color(t_color tuple1, t_color tuple2);
t_color	ft_multiply_color(t_color c1, t_color c2);
t_tuple	ft_multiply_tuple(t_tuple c1, t_tuple c2);

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
t_4x4	ft_transpose(t_4x4 matrix);

// MATRIX DETERMINANT
float	ft_calculate_determinant(t_4x4 matrix);
float	ft_determinant_3x3(t_3x3 submx);

// MATRIX TRANSFOMATION
t_4x4	ft_create_identity_matrix(void);
t_4x4	create_translation_mx(float x, float y, float z);
t_4x4	ft_create_shearing_mx(float Xy, float Xz, float Yx, float Yz, float Zx, float Zy);
t_4x4	create_scaling_mx(float x, float y, float z);

// 	ROTATION
t_4x4	rotation_z(float radians);
t_4x4	rotation_x(float radians);
t_4x4	rotation_y(float radians);
t_4x4	ft_rodriguez_rotation(float target_x, float target_y, float target_z);

//	PARSE
int		ft_get_scene(t_scene *scene, char *argv1);
bool	ft_parse_line(t_scene *scene, char *line);
char	*get_one_line(int fd);

//	CREATE AMBIENT
bool	ft_create_ambient(t_scene *scene, char **ambient);
bool	ft_check_rgb(char *colorcode);
bool	ft_apply_rgb(t_color *color, char *original);

//	CREATE LIGHT
bool	ft_create_light(t_scene *scene, char **light);
bool	ft_check_coords(char *coords);

//	CREATE CAMERA
bool	ft_create_camera(t_scene *scene, char **cam);
bool	ft_aim_camera(t_camera *cam1, float fov, char *point_of_view, char *orientation_vector);
t_4x4	view_transform(t_tuple origin, t_tuple direction);
t_4x4	ft_orientation(t_tuple left, t_tuple true_up, t_tuple forward);

//	CREATE SPHERE
bool	ft_create_sphere(t_scene *scene, char **ball);

//	CREATE PLANE
bool	ft_create_plane(t_scene *scene, char **plane);

//	CREATE CYLINDER
bool	ft_create_cylinder(t_scene *scene, char **cyl_data);

//	HOOKS
void	ft_handle_key(mlx_key_data_t keydata, void *param);

//	ERROR EXIT
int		ft_error_exit(t_scene *scene, char *err_msg, int err_code);
void	ft_free_scene(t_scene *scene);

#endif
