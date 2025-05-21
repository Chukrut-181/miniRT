#include "../include/minirt.h"

static int color_to_int(t_color color)
{
	int r;
	int g;
	int b;
	int res;

	color.r = fmaxf(0.0f, fminf(1.0f, color.r));
	color.g = fmaxf(0.0f, fminf(1.0f, color.g));
	color.b = fmaxf(0.0f, fminf(1.0f, color.b));

	r = (int)(color.r * 255.0f);
	g = (int)(color.g * 255.0f);
	b = (int)(color.b * 255.0f);

	res = ((0 << 24) | (r << 16) | (g << 8) | b);
	return (res);
}

static void write_pixel(t_img *img, int x, int y, int color)
{
	char *dst;
	
	dst = img->data + (y * img->size_line + x * (img->bits_per_pixel / 8));
	if (img->endian == 0)
	{
		dst[0] = (color) & 0xFF;
		dst[1] = (color >> 8) & 0xFF;
		dst[2] = (color >> 16) & 0xFF;
		dst[3] = (color >> 24) & 0xFF;
	}
	else
	{
		dst[0] = (color >> 24) & 0xFF;
		dst[1] = (color >> 16) & 0xFF;
		dst[2] = (color >> 8) & 0xFF;
		dst[3] = (color) & 0xFF;
	}
}

static t_ray ray_for_pixel(t_camera camera, int px, int py)
{
	float x_offset;
	float y_offset;
	float world_x;
	float world_y;
	t_tuple pixel;
	t_tuple origin;
	t_tuple direction;
	t_4x4 inverse;
	
	x_offset = (px + 0.5) * camera.pixel_size;
	y_offset = (py + 0.5) * camera.pixel_size;
	world_x = camera.half_width - x_offset;
	world_y = camera.half_height - y_offset;
	pixel = ft_create_point(world_x, world_y, -1);
	origin = ft_create_point(0, 0, 0);

	inverse = find_inverse(camera.transform);
	pixel = multiply_mat_and_tuple(inverse, pixel);
	origin = multiply_mat_and_tuple(inverse, origin);
	direction = normalize(substract_tuples(pixel, origin));
	return (create_ray(origin, direction));
}

static	t_color calculate_inter(t_world world, t_ray ray)
{
	t_list *intersections;
	t_xs *hit;
	t_comps comps;
	t_color color;

	intersections = ft_intersect_world(world, ray);
	hit = ft_find_hit(intersections);
	if (hit && hit->time > 0)
	{
		comps = prepare_computations(hit, ray);
		color = shade_hit(world, comps);
	}
	else
		color = ft_create_color(0, 0, 0);
	if (intersections)
		ft_lstclear(&intersections, free);
	return (color);
}

void render_scene(t_scene *s)
{
	int			x;
	int			y;
	t_ray		ray;
	t_color		color;
	int			pixel_color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = ray_for_pixel(*s->camera, x, y);
			color = calculate_inter(*s->world, ray);
			pixel_color = color_to_int(color);
			write_pixel(&s->img, x, y, pixel_color);
			x++;
		}
		y++;
		if (y % 10 == 0)
			write(1, ".", 1);
	}
	write(1, "\n", 1);
}
