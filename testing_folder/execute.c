#include "../include/minirt.h"

static	void	write_pixel(t_color color, uint8_t *pixel)
{
	ft_memset(pixel, color.r * 255, 1);
	ft_memset(pixel + 1, color.g * 255, 1);
	ft_memset(pixel + 2, color.b * 255, 1);
	ft_memset(pixel + 3, 255, 1);
}

static	t_color	calculate_inter(t_world worl, t_ray ray)
{
	t_list	*inter_list;
	t_list	*hit_list;
	t_comps	comps;

	inter_list = ft_intersect_world(worl, ray);
	if (inter_list == NULL)
		return (ft_create_color(0, 0, 0));
	hit_list = ft_find_hit(inter_list);
	if (hit_list == NULL)
		return (ft_create_color(0, 0, 0));
	comps = prepare_computations(hit_list, ray);
	return (shade_hit(worl, comps));
}

static t_ray	ray_for_pixel(t_camera cam, int x, int y)
{
	double		xoffset;
	double		yoffset;
	double		world_x;
	double		world_y;
	t_tuple		p[2];
	t_tuple		multil;
	t_tuple		direction;

	xoffset = (x + 0.5) * cam.pixel_size;
	yoffset = (y + 0.5) * cam.pixel_size;
	world_x = cam.half_width - xoffset;
	world_y = cam.half_height - yoffset;
	p[0] = ft_create_point(world_x, world_y, -1);
	multil = ft_multiply_mat_and_tuple(cam.transform, (p[0]));
	p[1] = ft_create_point(multil.x, multil.y, multil.z);
	direction = ft_normalize(ft_substract_tuples(p[1], cam.origin));
	return (ft_create_ray(cam.origin, direction));
}

void render_scene(t_scene *s)
{
	size_t y;
	size_t x;
	size_t p;
	t_color color;
	t_ray	ray;

	p = 0;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = ray_for_pixel(*s->camera, x, y);
			color = calculate_inter(*s->world, ray);
			write_pixel(color, s->image->pixels + p);
			x++;
			p += 4;
		}
		y++;
	}
}
