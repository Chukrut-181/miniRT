#include "../include/minirt.h"

static	t_4x4	ft_orientation(t_tuple left, t_tuple true_up, t_tuple forward)
{
	t_4x4	matrix;

	matrix = ft_create_identity_matrix();
	matrix.data[0][0] = left.x;
	matrix.data[0][1] = left.y;
	matrix.data[0][2] = left.z;

	matrix.data[1][0] = true_up.x;
	matrix.data[1][1] = true_up.y;
	matrix.data[1][2] = true_up.z;

	matrix.data[2][0] = forward.x;
	matrix.data[2][1] = forward.y;
	matrix.data[2][2] = forward.z;
	return (matrix);
}

t_4x4	view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple forward;
	t_tuple upn;
	t_tuple left;
	t_tuple true_up;
	t_4x4	orientation;
	t_4x4	res;

	forward = ft_normalize(ft_substract_tuples(to, from));
	upn = ft_normalize(up);
	left = ft_cross_product(forward, upn);
	true_up = ft_cross_product(left, forward);
	orientation = ft_orientation(left, true_up, forward);
	res = ft_multiply_matrices(orientation, translation(ft_negate_tuple(from)));
	return (res);
}

t_camera	ft_create_camera(int hsize, int vsize, float field_of_view)
{
	t_camera	c;

	c.hsize = hsize;
	c.vsize = vsize;
	c.field_of_view = field_of_view;
	c.transform = ft_create_identity_matrix();
	return (c);
}

t_camera	ft_camera(int hsize, int vsize, float field_of_view)
{
	t_camera	c;
	float		half_view;
	int		aspect;

	c = ft_create_camera(hsize, vsize, field_of_view);
	half_view = tanf(c.field_of_view / 2);
	aspect = ((float)c.hsize / c.vsize);
	if (aspect >= 1)
	{
		 c.half_width = half_view;
		c.half_height = half_view / aspect;
	}
	else
	{
		c.half_width = half_view * aspect;
		c.half_height = half_view;
	}
	c.pixel_size = (c.half_width * 2) / c.hsize;
	return (c);
}

t_ray	ray_for_pixel(t_camera c, float px, float py)
{
	float	 xoffset;
	float	 yoffset;
	float	 world_x;
	float	 world_y;
	t_tuple	pixel;
	t_tuple	origin;
	t_tuple	direction;

	xoffset = (px + 0.5) * c.pixel_size;
	yoffset = (py + 0.5) * c.pixel_size;
	
	world_x = c.half_width - xoffset;
	world_y = c.half_height - yoffset;
	
	pixel = ft_multiply_mat_and_tuple(ft_find_inverse(c.transform), ft_create_point(world_x, world_y, -1));
	origin = ft_multiply_mat_and_tuple(ft_find_inverse(c.transform), ft_create_point(0, 0, 0));
	direction = ft_normalize(ft_substract_tuples(pixel, origin));
	return (ft_create_ray(origin, direction));
}

void	create_scene(mlx_t *mlx, mlx_image_t *image)
{
	t_world world;
	t_camera camera;
	t_tuple from, to, up;
	t_sphere *floor, *left_wall, *right_wall, *middle, *right, *left;
	
	world.light = point_light(ft_create_point(-10, 10, -10), ft_create_point(1, 1, 1));
	world.objects = NULL;
	
	floor = ft_create_sphere(ft_create_point(0, 0, 0), 500);
	floor->transform = scalation(ft_create_point(10, 0.01, 10));
	floor->material = ft_create_material(1, 0.9, 0.9);
	floor->material.specular = 0;
	ft_lstadd_back(&world.objects, ft_lstnew(floor));
	
	left_wall = ft_create_sphere(ft_create_point(0, 0, 0), 500);
	t_4x4 left_wall_transform = ft_multiply_matrices(translation(ft_create_point(0, 0, 5)), ft_multiply_matrices(rotation_y(-M_PI / 4), ft_multiply_matrices(rotation_x(M_PI / 2), scalation(ft_create_point(10, 0.01, 10)))));
	left_wall->transform = left_wall_transform;
	left_wall->material = floor->material;
	ft_lstadd_back(&world.objects, ft_lstnew(left_wall));
	
	right_wall = ft_create_sphere(ft_create_point(0, 0, 0), 500);
	t_4x4 right_wall_transform = ft_multiply_matrices(translation(ft_create_point(0, 0, 5)),ft_multiply_matrices(rotation_y(M_PI / 4), ft_multiply_matrices(rotation_x(M_PI / 2), scalation(ft_create_point(10, 0.01, 10)))));
	right_wall->transform = right_wall_transform;
	right_wall->material = floor->material;
	ft_lstadd_back(&world.objects, ft_lstnew(right_wall));
	
	middle = ft_create_sphere(ft_create_point(0, 0, 0), 300);
	middle->transform = translation(ft_create_point(-0.5, 1, 0.5));
	middle->material = ft_create_material(0.1, 0.8, 0.1);
	middle->material.diffuse = 0.7;
	middle->material.specular = 0.3;
	ft_lstadd_back(&world.objects, ft_lstnew(middle));
	
	right = ft_create_sphere(ft_create_point(0, 0, 0), 100);
	right->transform = ft_multiply_matrices(
		translation(ft_create_point(1.5, 0.5, -0.5)),
		scalation(ft_create_point(0.5, 0.5, 0.5))
	);
	right->material = ft_create_material(0.5, 1, 0.1);
	right->material.diffuse = 0.7;
	right->material.specular = 0.3;
	ft_lstadd_back(&world.objects, ft_lstnew(right));
	
	left = ft_create_sphere(ft_create_point(0, 0, 0), 300);
	left->transform = ft_multiply_matrices(
		translation(ft_create_point(-1.5, 0.33, -0.75)),
		scalation(ft_create_point(0.33, 0.33, 0.33))
	);
	left->material = ft_create_material(1, 0.8, 0.1);
	left->material.diffuse = 0.7;
	left->material.specular = 0.3;
	ft_lstadd_back(&world.objects, ft_lstnew(left));
	
	camera = ft_camera(1200, 900, M_PI / 3);
	from = ft_create_point(0, 1.5, -5);
	to = ft_create_point(0, 1, 0);
	up = ft_create_vector(0, 1, 0);
	camera.transform = view_transform(from, to, up);
	
	render(camera, world, mlx, image);
}

void	render(t_camera camera, t_world world, mlx_t *mlx, mlx_image_t *image)
{
	(void)mlx;
	t_ray ray;
	t_tuple color;
	int x, y;
	
	y = 0;
	while (y < camera.vsize)
	{
		x = 0;
		while (x < camera.hsize)
		{
			ray = ray_for_pixel(camera, x, y);
			color = color_at(world, ray);
			uint32_t pixel_color = ((uint32_t)(color.x * 255) << 24) | ((uint32_t)(color.y * 255) << 16) | ((uint32_t)(color.z * 255) << 8) | 0xFF;
			mlx_put_pixel(image, x - 1200,900 -  y, pixel_color);
			x++;
		}
		y++;
	}
}

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
