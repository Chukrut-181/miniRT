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

	matrix.data[2][0] = forward.x * -1;
	matrix.data[2][1] = forward.y * -1;
	matrix.data[2][2] = forward.z * -1;
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

	(void)field_of_view;
	c = malloc(sizeof(t_camera));
	if (!c)
		return (false);
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

	if (!scene->camera)
		return (1);
	fov = ft_atof(cam_data[3]);
	if(!ft_camera(scene, fov, cam_data[1], cam_data[2]))
		return (1);
	*scene->camera = camera(HEIGHT, WIDTH, fov);
	t_tuple	origin_tp = ft_multiply_mat_and_tuple(scene->camera->transform, ft_create_vector(0, 0, 0));
	scene->camera->origin = ft_create_point(origin_tp.x, origin_tp.y, origin_tp.z);
	return (0);
}

t_camera	camera(int hsize, int vsize, double field_of_view)
{
	t_camera	c;
	float		half_view;
	float			aspect;

	c.hsize = hsize;
	c.vsize = vsize;
	c.field_of_view = field_of_view;
	half_view = tan(((field_of_view * M_PI) / 180.0) / 2);
	aspect = (c.hsize / c.vsize);
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
