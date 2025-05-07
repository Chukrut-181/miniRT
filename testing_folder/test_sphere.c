#include "../include/minirt.h"

/* static t_ray	ft_transform_ray(t_ray ray, t_4x4 *m)
{
	t_ray	transformed;

	transformed.origin = *ft_multiply_mat_and_tuple(m, &ray.origin);
	transformed.direction = *ft_multiply_mat_and_tuple(m, &ray.direction);
	return (transformed);
}

static t_4x4 *ft_transformation_test(void) { t_4x4	*transform; transform =  NULL; transform = ft_find_inverse(create_scalation_mx(ft_create_point(0.25, 1, 1)));
	if (!transform)
		return (write(1, "matriz caca\n", 12), NULL);
	return (transform);
} */

//void	ft_render_sphere(mlx_image_t *image)
//{
//	t_sphere	sphere;
//	t_ray		ray;
//	t_tuple		ray_origin;
//	t_tuple		direction;
//	t_list		*xs_list;
//	t_xs		*aux;
//	int			x;
//	int			y;
//
//	sphere = *ft_create_sphere(ft_create_point(0, 0, 0), 500);
//	ray_origin = ft_create_point(0, 0, -1000);
//	xs_list = NULL;
//	x = 0;
//	while (x < 2400)
//	{
//		y = 0;
//		while (y < 1800)
//		{	
//			direction = ft_create_vector(x - 1200, 900 - y, 1000);
//			direction = ft_normalize(direction);
//			ray = ft_create_ray(ray_origin, direction);
//			xs_list = ft_intersection(ray, sphere, xs_list);
//			while (xs_list)
//			{
//				aux = (t_xs *)xs_list->content;
//				if (aux->hit == 1)
//				{
//					mlx_put_pixel(image, x, y, 0xFFFFFFFF);
//					break ;
//				}
//				xs_list = xs_list->next;
//			}
//			ft_lstclear(&xs_list, free);
//			y++;
//		}
//		x++;
//	}
//}

//void render_lit_sphere(t_scene *s)
//{
//	t_sphere sphere;
//	t_light light;
//	t_tuple eye_pos;
//	t_ray ray;
//	t_list *xs_list;
//	t_xs *intersection;
//	t_tuple point;
//	t_tuple normal;
//	t_tuple eye_v;
//	t_tuple color;
//	int x, y;
//	
//	sphere.center = ft_create_point(0, 0, 0);
//	sphere.diameter = 500*2;
//	sphere.material = ft_create_material(1, 0.2, 1);  // Purple/magenta color
//	sphere.material.ambient = 0.1;
//	sphere.material.diffuse = 0.7;
//	sphere.material.specular = 0.3;
//	sphere.material.shininess = 100.0;
//	sphere.transform = ft_create_identity_matrix();
//	
//	light = point_light(ft_create_point(-500, 500, -1000), ft_create_point(0.5, 1, 1));
//	// Eye position
//	eye_pos = ft_create_point(0, 0, -1000);
//	
//	// Render the sphere with lighting
//	y = 0;
//	while(y < 1800)
//	{
//		x = 0;
//		while(x < 2400)
//		{
//			// Create a ray from the eye through this pixel
//			t_tuple pixel_point = ft_create_point(x - 1200,900 - y, 0);
//			t_tuple direction = ft_normalize(ft_substract_tuples(pixel_point, eye_pos));
//			ray = ft_create_ray(eye_pos, direction);
//			// Find intersections
//			xs_list = ft_intersection(ray, sphere, NULL);
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
//					normal = normal_at(sphere, point);
//					// Calculate the eye vector
//					eye_v = ft_normalize(ft_negate_tuple(ray.direction));
//					// Calculate the color using the lighting function
//					color = lighting(sphere.material, light, point, eye_v, normal);
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
//
