/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v0                                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:08:55 by v0                #+#    #+#             */
/*   Updated: 2025/04/22 15:25:07 by eandres          ###   ########.fr       */
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

int	main(int argc, char **argv);

//	MINIRT
int	ft_minirt(void);

//	TUPLE CREATION
t_tuple	ft_create_point(float x, float y, float z);
t_color	ft_create_color(float x, float y, float z);
t_tuple	ft_create_vector(float x, float y, float z);
int		ft_check_equality(t_tuple tuple1, t_tuple tuple2);
t_point	create_point(double x, double y, double z);
t_tuple	point_tp(t_point p);

//	TUPLE OPERATIONS
t_tuple	ft_add_tuples(t_tuple tuple1, t_tuple tuple2);
t_tuple	ft_substract_tuples(t_tuple tuple1, t_tuple tuple2);
t_tuple	ft_multiply_tuple_f(t_tuple tuple, float scalar);
t_tuple	ft_divide_tuple(t_tuple tuple, float scalar);
t_tuple	ft_negate_tuple(t_tuple tuple);
t_tuple	ft_multiply_colors(t_tuple c1, t_tuple c2);
t_color	ft_multiply_color_f(t_color tuple, float scalar);
t_color	ft_add_color(t_color tuple1, t_color tuple2);
t_color	ft_multiply_color(t_color c1, t_color c2);
t_tuple	ft_multiply_tuple(t_tuple c1, t_tuple c2);
t_tuple	ft_substract_point(t_point tuple1, t_point tuple2);

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
t_4x4	create_scaling_mx(float x, float y, float z);
t_4x4	ft_create_shearing_mx(float Xy, float Xz, float Yx, float Yz, float Zx, float Zy);

// 	ROTATION
t_4x4	rotation_z(float radians);
t_4x4	rotation_x(float radians);
t_4x4	rotation_y(float radians);
t_4x4 ft_rotate_plane(float target_x, float target_y, float target_z);

//	RAY
t_ray	ft_create_ray(t_tuple origin, t_tuple direction);
t_tuple	ft_position(t_ray ray, float t);
t_list	*ft_intersection_sphere(t_ray ray, t_shape sphere, t_list *xs_list);
void	ft_identify_hit(t_list *xs_list);

//	LIGHT
t_material	ft_create_material(char *rgb_code);
t_tuple	normal_at(t_sphere sphere, t_tuple world_point);
t_tuple	reflect(t_tuple in, t_tuple normal);
t_light	point_light(t_tuple position, t_tuple color);
//t_color	lighting(t_material mat, t_light light, t_tuple point, t_tuple eyev, t_tuple normalv);

//	CAMERA
t_4x4		view_transform(t_tuple from, t_tuple to, t_tuple up);
t_camera	ft_camera(int hsize, int vsize, float field_of_view);
//t_ray	ray_for_pixel(t_camera c, float px, float py);
mlx_image_t *ft_render(mlx_t *mlx, t_camera camera, t_world world);
t_4x4	ft_orientation(t_tuple left, t_tuple true_up, t_tuple forward);

//	WORLD
t_world ft_default_world(void);
t_list *ft_find_hit(t_list *intersections);
t_comps	prepare_computations(t_list *intersection, t_ray ray);
t_list *ft_intersect_world(t_world world, t_ray ray);
t_tuple	color_at(t_world world, t_ray ray);
t_list *ft_sort_intersections(t_list *intersections);

//	PARSE
void	parse(t_scene *s, char **argv);
int	create_ambient_light(t_scene *s, char **res);
int	create_camera(char **str, t_scene *s);
int	create_light(char **res, t_scene *s);
int	create_sphere(char **res, t_scene *s);
int	check_rgb(char *str, t_scene *data);

//	EXECUTE
void render_scene(t_scene *s);
// t_tuple	normal_at_plane(t_plane plane, t_tuple world_point);
// t_xs	intersect(t_plane *plane, t_ray *ray);
t_tuple	shade_hit(t_scene s, t_comps comps);
bool	intersec_plane(t_shape *shape, t_list **inter);
bool	intersec_sphere(t_shape *shape, t_list **inter);

// CYLINDER
t_list	*ft_intersect_cylinder(t_ray ray, t_cyl cylinder, t_list *xs_list);
t_tuple	normal_at_cylinder(t_cyl cylinder, t_tuple world_point);

//	PARSE
int	ft_get_scene(t_scene *scene, char *argv1);
int ft_parse_line(t_scene *scene, char *line);
char	*get_one_line(int fd);

//	CREATE AMBIENT
int		ft_create_ambient(t_scene *scene, char **ambient);
bool	ft_check_rgb(char *colorcode);
bool	ft_apply_rgb(t_color *color, char *original);

//	CREATE LIGHT
int		ft_create_light(t_scene *scene, char **light);
bool	ft_check_coords(char *coords);

//	CREATE CAMERA
int		ft_create_camera(t_scene *scene, char **cam);
bool	ft_check_orientation_vector(char *orientation);

//	CREATE SPHERE
int	ft_create_sphere(t_scene *scene, char **ball);

//	CREATE CYLINDER
int		ft_create_cylinder(t_scene *scene, char **cyl);

//	CREATE PLANE
int	ft_create_plane(t_scene *scene, char **plane);

//	HOOKS
void	ft_handle_key(mlx_key_data_t keydata, void *param);

//	ERROR EXIT
int		ft_error_exit(char *err_msg, int err_code);
void	ft_free_scene(t_scene *scene);

//	TEST FUNCTIONS (to be removed)
void	ft_minigun(mlx_image_t	*image);
void	ft_draw_clock(mlx_image_t *image);
int		ft_test_matrix_functions(void);
int		ft_test_ray(void);
int		ft_test_intersection(void);
void	test_reflection(void);
void	test_lighting(void);
void	ft_render_billiard_ball(mlx_image_t *image);

#endif
