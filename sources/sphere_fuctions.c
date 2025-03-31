/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   things.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:42:33 by igchurru          #+#    #+#             */
/*   Updated: 2025/03/20 10:51:10 by eandres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_sphere	*ft_create_sphere(t_tuple point, float r)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->center.x = point.x;
	sphere->center.y = point.y;
	sphere->center.z = point.z;
	sphere->radius = r;
	sphere->transform = ft_create_identity_matrix();
	return (sphere);
}
//
//void	create_scene(mlx_t *mlx, mlx_image_t *image)
//{
//	t_world world;
//	t_camera camera;
//	t_tuple from, to, up;
//	t_sphere floor;
//	
//	world.light = point_light(ft_create_point(-500, 500, -1000), ft_create_point(0.5, 1, 1));
//	
//	floor.center = ft_create_point(0, 0, 0);
//	floor.radius = 300;
//	floor.material = ft_create_material(1, 0.2, 1);
//	floor.material.ambient = 0.1;
//	floor.material.diffuse = 0.7;
//	floor.material.specular = 0.3;
//	floor.material.shininess = 100.0;
//	ft_lstadd_back(&world.objects, ft_lstnew(floor));
//	floor = ft_create_sphere(ft_create_point(0, 0, 0), 500);
//	floor->transform = scalation(ft_create_point(10, 0.01, 10));
//	floor->material = ft_create_material(1, 0.9, 0.9);
//	floor->material.specular = 0;
//	ft_lstadd_back(&world.objects, ft_lstnew(floor));
//      
//	left_wall = ft_create_sphere(ft_create_point(0, 0, 0), 500);
//	t_4x4 left_wall_transform = ft_multiply_matrices(translation(ft_create_point(0, 0, 5)), ft_multiply_matrices(rotation_y(-M_PI / 4), ft_multiply_matrices(rotation_x(M_PI / 2), scalation(ft_create_point(10, 0.01, 10)))));
//	left_wall->transform = left_wall_transform;
//	left_wall->material = floor->material;
//	ft_lstadd_back(&world.objects, ft_lstnew(left_wall));
//	
//	right_wall = ft_create_sphere(ft_create_point(0, 0, 0), 500);
//	t_4x4 right_wall_transform = ft_multiply_matrices(translation(ft_create_point(0, 0, 5)),ft_multiply_matrices(rotation_y(M_PI / 4), ft_multiply_matrices(rotation_x(M_PI / 2), scalation(ft_create_point(10, 0.01, 10)))));
//	right_wall->transform = right_wall_transform;
//	right_wall->material = floor->material;
//	ft_lstadd_back(&world.objects, ft_lstnew(right_wall));
//	
//	middle = ft_create_sphere(ft_create_point(0, 0, 0), 300);
//	middle->transform = translation(ft_create_point(-0.5, 1, 0.5));
//	middle->material = ft_create_material(0.1, 0.8, 0.1);
//	middle->material.diffuse = 0.7;
//	middle->material.specular = 0.3;
//	ft_lstadd_back(&world.objects, ft_lstnew(middle));
//	
//	right = ft_create_sphere(ft_create_point(0, 0, 0), 100);
//	right->transform = ft_multiply_matrices(
//		translation(ft_create_point(1.5, 0.5, -0.5)),
//		scalation(ft_create_point(0.5, 0.5, 0.5))
//	);
//	right->material = ft_create_material(0.5, 1, 0.1);
//	right->material.diffuse = 0.7;
//	right->material.specular = 0.3;
//	ft_lstadd_back(&world.objects, ft_lstnew(right));
//	
//	left = ft_create_sphere(ft_create_point(0, 0, 0), 300);
//	left->transform = ft_multiply_matrices(
//		translation(ft_create_point(-1.5, 0.33, -0.75)),
//		scalation(ft_create_point(0.33, 0.33, 0.33))
//	);
//	left->material = ft_create_material(1, 0.8, 0.1);
//	left->material.diffuse = 0.7;
//	left->material.specular = 0.3;
//	ft_lstadd_back(&world.objects, ft_lstnew(left));
//	
//	camera = ft_camera(1200, 900, M_PI / 3);
//	from = ft_create_point(0, 1.5, -5);
//	to = ft_create_point(0, 1, 0);
//	up = ft_create_vector(0, 1, 0);
//	camera.transform = view_transform(from, to, up);
//	
//	render(camera, world, mlx, image);
//}
//
//void	render(t_camera camera, t_world world, mlx_t *mlx, mlx_image_t *image)
//{
//	(void)mlx;
//	t_ray ray;
//	t_tuple color;
//	int x, y;
//	
//	y = 0;
//	while (y < camera.vsize)
//	{
//		x = 0;
//		while (x < camera.hsize)
//		{
//			ray = ray_for_pixel(camera, x, y);
//			color = color_at(world, ray);
//			uint32_t pixel_color = ((uint32_t)(color.x * 255) << 24) | ((uint32_t)(color.y * 255) << 16) | ((uint32_t)(color.z * 255) << 8) | 0xFF;
//			mlx_put_pixel(image, x - 1200,900 -  y, pixel_color);
//			x++;
//		}
//		y++;
//	}
//}
//
//void	test_render()
//{
//	t_world w;
//	t_camera c;
//	t_tuple from;
//	t_tuple up;
//	t_tuple to;
//	mlx_image_t *image;
//
//	w = ft_default_world();
//	c = ft_camera(11, 11, M_PI / 2);
//	from = ft_create_point(0, 0, -5);
//	to = ft_create_point(0, 0, 0);
//	up = ft_create_vector(0, 1, 0);
//	c.transform = view_transform(from, to, up);
//	image = render(c, w);
//	pixel_at(image, 5, 5) = color(0.38066, 0.47583, 0.2855);
//}
//
