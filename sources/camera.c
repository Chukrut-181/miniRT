#include "../include/minirt.h"

t_4x4	ft_orientation(t_tuple left, t_tuple true_up, t_tuple forward)
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

t_4x4	view_transform(t_tuple origin, t_tuple direction)
{
	t_tuple up_normal;
	t_tuple left_vector;
	t_tuple neg_or;
	//t_tuple true_up;
	t_4x4	orientation;
	t_4x4	res;

	direction = ft_normalize(direction);
	up_normal = ft_create_vector(0, 1, 0);
	left_vector = ft_cross_product(direction, up_normal);
	//true_up = ft_cross_product(left, forward);
	orientation = ft_orientation(left_vector, up_normal, direction);
	neg_or = ft_negate_tuple(origin);
	res = ft_multiply_matrices(orientation, create_translation_mx(neg_or.x, neg_or.y, neg_or.z));
	return (res);
}

bool	ft_camera(t_scene *scene, float field_of_view, char *point_of_view, char *orientation_vector)
{
	t_camera	*c;
	t_tuple		origin;
	t_tuple		direction;
	char		**aux;

	c = malloc(sizeof(t_camera));
	if (!c)
		return (false);
	c->hsize = WIDTH;
	c->vsize = HEIGHT;
	c->field_of_view = field_of_view;
	if (!ft_check_coords(orientation_vector) || !ft_check_coords(point_of_view))
		return (free(c), false);
	aux = ft_split(point_of_view, ',');
	origin = ft_create_point(ft_atof(aux[0]), ft_atof(aux[1]), ft_atof(aux[2]));
	free(aux);
	aux = ft_split(orientation_vector, ',');
	direction = ft_create_vector(ft_atof(aux[0]), ft_atof(aux[1]), ft_atof(aux[2]));
	free(aux);
	c->transform = view_transform(origin, direction);
	scene->camera = c;
	return (true);
}

int	ft_create_camera(t_scene *scene, char **cam_data)
{
	float		fov;
	float		half_view;
	int			aspect;

	if (!scene->camera)
		return (1);
	fov = ft_atof(cam_data[3]);
	if(!ft_camera(scene, fov, cam_data[1], cam_data[2]))
		return (1);
	half_view = tanf(fov / 2);
	aspect = ((float)HEIGHT / WIDTH);
	if (aspect >= 1)
	{
		scene->camera->half_width = half_view;
		scene->camera->half_height = half_view / aspect;
	}
	else
	{
		scene->camera->half_width = half_view * aspect;
		scene->camera->half_height = half_view;
	}
	scene->camera->pixel_size = (scene->camera->half_width * 2) / scene->camera->hsize;
	return (0);
}

/* t_camera	ft_create_camera(int hsize, int vsize, float field_of_view)
{
	t_camera	c;
	float		half_view;
	int			aspect;

	c = ft_camera(hsize, vsize, field_of_view);
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
} */

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

