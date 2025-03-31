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

