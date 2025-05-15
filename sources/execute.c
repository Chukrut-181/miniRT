#include "../include/minirt.h"

static void	write_pixel(double w, double h, t_color color, t_scene *scene)
{
	int				rr;
	int				gg;
	int				bb;
	int				color_code;
	unsigned char	*dst;

	rr = color.r * 255;
	gg = color.g * 255;
	bb = color.b * 255;
	color_code = rr << 16 | gg << 8 | bb;
	dst = scene->img.data + (int)h * scene->img.size_line + (int)w * (scene->img.bits_per_pixel / 8);
	*(unsigned int *)dst = color_code;
}

static	t_color	calculate_inter(t_world worl, t_ray ray)
{
	t_list	*inter_list;
	t_xs	*hit;
	t_comps	comps;

	inter_list = ft_intersect_world(worl, ray);
	if (!inter_list)
		return (ft_create_color(0, 0, 0));
	hit = ft_find_hit(inter_list);
	if (!hit || hit->time <= EPSILON || hit->intersec == false)
		return (free(hit), ft_create_color(0, 0, 0));
	comps = prepare_computations(hit, ray);
	return (shade_hit(worl, comps));
}

static t_ray	ray_for_pixel(t_camera cam, double x, double y)
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
	double y;
	double x;
	t_color color;
	t_ray	ray;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = ray_for_pixel(*s->camera, x, y);
			color = calculate_inter(*s->world, ray);
			write_pixel(x, y, color, s);
			x++;
		}
		y++;
	}
}

//void render_lit_sphere(t_scene *s)
//{
//	t_sphere *sphere;
//	t_ray ray;
//	t_list *xs_list;
//	t_xs *intersection;
//	t_tuple point;
//	t_tuple normal;
//	t_tuple eye_v;
//	t_tuple color;
//	int x, y;
//	
////	sphere.center = ft_create_point(0, 0, 0);
////	sphere.diameter = 500*2;
////	sphere.material = ft_create_material(1, 0.2, 1);  // Purple/magenta color
////	sphere.material.ambient = 0.1;
////	sphere.material.diffuse = 0.7;
////	sphere.material.specular = 0.3;
////	sphere.material.shininess = 100.0;
//	sphere = (t_sphere *)s->objects->content;
//
//	y = 0;
//	while(y < 1800)
//	{
//		x = 0;
//		while(x < 2400)
//		{
//			// Create a ray from the eye through this pixel
//			t_tuple pixel_point = ft_create_point(x - 1200,900 - y, 0);
//			t_tuple direction = ft_normalize(ft_substract_tuples(pixel_point, s->camera->viewpoint));
//			ray = ft_create_ray(s->camera->viewpoint, direction);
//			// Find intersections
//			xs_list = ft_intersection(ray, *sphere, NULL);
//			// If we hit the sphere
//			if (xs_list)
//			{
//				// Find the hit point (the closest intersection in front of the eye)
//				intersection = NULL;
//				while (xs_list)
//				{
//					t_xs *current = (t_xs *)xs_list->content;
//					if (current->hit)
//					{
//						intersection = current;
//						break;
//					}
//					xs_list = xs_list->next;
//				}
//				if (intersection)
//				{
//					// Calculate the actual point of intersection
//					point = ft_position(ray, intersection->time);
//					// Calculate the normal at the intersection point
//					normal = normal_at(*sphere, point);
//					// Calculate the eye vector
//					eye_v = ft_normalize(ft_negate_tuple(ray.direction));
//					// Calculate the color using the lighting function
//					color = lighting(sphere->material, *s->light, point, eye_v, normal);
//					// Convert color to uint32_t for MLX
//					uint32_t pixel_color = ((uint32_t)(color.x * 255) << 24) | 
//										 ((uint32_t)(color.y * 255) << 16) | 
//										 ((uint32_t)(color.z * 255) << 8) | 
//										 0xFF;
//					mlx_put_pixel(s->image, x, y, pixel_color);
//				}
//				ft_lstclear(&xs_list, free);
//			}
//			x++;
//		}
//		y++;
//	}
//}

