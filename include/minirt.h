/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:08:55 by eandres           #+#    #+#             */
/*   Updated: 2025/05/28 10:40:52 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../lib/libft/libft.h"
# include "../lib/minilibx/mlx.h"
# include <math.h>
# include <float.h>
# include <stdio.h>
# include <unistd.h>
# include "structures.h"

# define EPSILON 0.00001

# define HEIGHT 1200
# define WIDTH 1800

# ifndef M_PI
#  define M_PI 3.1415926
# endif

//	MAIN
int			main(int argc, char **argv);

//	TUPLE CREATION
t_tuple		ft_create_point(float x, float y, float z);
t_tuple		create_vector(float x, float y, float z);
int			check_equality(t_tuple tuple1, t_tuple tuple2);
t_point		create_point(double x, double y, double z);
t_tuple		negate_tuple(t_tuple tuple);

//	TUPLE OPERATIONS
t_tuple		add_tuples(t_tuple tuple1, t_tuple tuple2);
t_tuple		substract_tuples(t_tuple tuple1, t_tuple tuple2);
t_tuple		multiply_tuples(t_tuple c1, t_tuple c2);
t_tuple		multiply_tuple_f(t_tuple tuple, float scalar);
t_tuple		divide_tuple(t_tuple tuple, float scalar);

//	VECTOR OPERATIONS
float		get_magnitude(t_tuple v);
t_tuple		normalize(t_tuple v);
float		dot_product(t_tuple v1, t_tuple v2);
t_tuple		cross_product(t_tuple v1, t_tuple v2);

//	COLOR OPERATIONS
t_color		multiply_color_f(t_color tuple, float scalar);
t_color		add_colors(t_color tuple1, t_color tuple2);
t_color		multiply_colors(t_color c1, t_color c2);
t_color		ft_create_color(float x, float y, float z);
t_tuple		color_tp(t_color p);

//	MATRIX OPERATIONS
int			check_matrix_equality(t_4x4 matrix1, t_4x4 matrix2);
t_4x4		multiply_matrices(t_4x4 matrix1, t_4x4 matrix2);
t_tuple		multiply_mat_and_tuple(t_4x4 matrix, t_tuple tuple);
t_4x4		find_inverse(t_4x4 matrix);

// MATRIX DETERMINANT
float		calculate_determinant(t_4x4 matrix);
float		determinant_3x3(t_3x3 submx);
t_4x4		transpose(t_4x4 matrix);

// MATRIX TRANSFOMATION
t_4x4		create_identity_matrix(void);
t_4x4		create_translation_mx(float x, float y, float z);
t_4x4		create_scaling_mx(float x, float y, float z);

// 	ROTATION
t_4x4		rotation_z(float radians);
t_4x4		rotation_x(float radians);
t_4x4		rotation_y(float radians);
t_4x4		rodriguez_rotation(float target_x, float target_y, float target_z);

//	RAY
t_ray		create_ray(t_tuple origin, t_tuple direction);
t_tuple		ft_position(t_ray ray, float t);
void		identify_hit(t_list *xs_list);

//	LIGHT & SHADING
t_tuple		reflect(t_tuple in, t_tuple normal);
t_color		lighting(t_comps comp, t_world *world, bool in_shadow);

//	LIGHT & SHADING UTILS
t_tuple		normal_at(t_shape *shape, t_tuple point);
t_color		effective_color(t_material m, t_color color, float intensity);
t_light		point_light(t_tuple position, t_color color);

//	PARSE
int			get_scene(t_scene *scene, char *argv1);
int			parse_line(t_scene *scene, char *line);
char		*get_one_line(int fd);

//	CREATE AMBIENT
bool		create_ambient(t_world *world, char **ambient);
bool		check_rgb(char *colorcode);
bool		apply_rgb(t_color *color, char *original);

//	CREATE LIGHT
bool		create_light(t_world *world, char **light);
bool		check_coords(char *coords);

//	CREATE CAMERA
bool		create_camera(t_scene *scene, char **cam);
t_4x4		view_transform(t_tuple origin, t_tuple direction);
t_4x4		ft_orientation(t_tuple left, t_tuple true_up, t_tuple forward);

//	CREATE SPHERE
t_material	create_material(char *rgb_code);
bool		create_sphere(t_scene *scene, char **ball);

//	CREATE PLANE
bool		create_plane(t_scene *scene, char **plane);

//	CREATE CYLINDER
bool		create_cylinder(t_scene *scene, char **cyl_data);
void		abcd_for_cyl(t_abcd *data, t_ray ray);

//	CREATE CUBE
bool	create_cube(t_scene *scene, char **temp);
bool    intersect_cube(t_shape *shape, t_list **inter, t_ray ray);

//	EXECUTE
void		render_scene(t_scene *s);
t_color		shade_hit(t_world w, t_comps comps);

//	INTERSECTIONS
bool		intersect_plane(t_shape *shape, t_list **inter);
bool		intersect_sphere(t_shape *shape, t_list **inter);
bool		intersect_cylinder(t_shape *shape, t_list **inter, t_ray ray);
bool		ft_intersections(t_ray ray, t_shape *shape, t_list **inter);

//	INTERSECTION UTILS
void		solve_quadratic_equation(t_abcd data, float *t);
void		update_inter(t_list **inter, t_shape *shape, float time);
void		identify_hit(t_list *xs_list);
t_ray		transform(t_ray ray, t_4x4	matrix);
t_list		*ft_intersect_world(t_world world, t_ray ray);

//	WORLD
t_xs		*ft_find_hit(t_list *intersections);
t_comps		prepare_computations(t_xs *hit, t_ray ray);

//	HOOKS
int			key_hook(int keycode, t_scene *data);
int			close_hook(t_scene *data);

//	ERROR EXIT
int			ft_error_exit(t_scene *failed_scene, char *err_msg, int err_code);
void		ft_free_scene(t_scene *scene);

#endif
