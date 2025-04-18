#include "../include/minirt.h"

//void render_scene(t_scene *s)
//{
//	t_list *current_obj;
//	t_type obj_type;
//	
//	if (!s->objects)
//		return;
//	current_obj = s->objects;
//	obj_type = *(t_type *)(current_obj->content);
//	if (obj_type == PLANE)
//		render_plane(s);
//	else if (obj_type == SPHERE)
//		render_lit_sphere(s);
//}
//
//void render_plane(t_scene *s)
//{
//	t_plane *plane;
//	t_ray ray;
//	t_xs intersection;
//	t_tuple point;
//	t_tuple normal;
//	t_tuple eye_v;
//	t_tuple color;
//	int x, y;
//	
//	// Get the plane from the scene objects
//	// Assuming the first object in the list is a plane
//	plane = (t_plane *)s->objects->content;
//	
//	y = 0;
//	while (y < WIDTH)
//	{
//		x = 0;
//		while (x < HEIGHT)
//		{
//			t_tuple pixel_point = ft_create_point(x - (WIDTH/2), (HEIGHT/2) - y, 0);
//			t_tuple direction = ft_normalize(ft_substract_tuples(pixel_point, s->camera->viewpoint));
//			ray = ft_create_ray(s->camera->viewpoint, direction);
//			intersection = intersect(plane, &ray);
//			
//			if (intersection.hit)
//			{
//				// Calculate the actual point of intersection
//				point = ft_position(ray, intersection.time);
//				// Get the normal at the intersection point (for a plane, this is constant)
//				normal = plane->n_n_vector;
//				// If the plane has a transform, apply it to the normal
//				if (plane->transform)
//				{
//					t_4x4 inverse_transform = ft_find_inverse(*plane->transform);
//					t_4x4 transpose_inverse = ft_transpose(inverse_transform);
//					normal = ft_multiply_mat_and_tuple(transpose_inverse, normal);
//					normal.w = 0;
//					normal = ft_normalize(normal);
//				}
//				// Calculate the eye vector
//				eye_v = ft_normalize(ft_negate_tuple(ray.direction));
//				// Calculate the color using the lighting function
//				color = lighting(plane->material, *s->light, point, eye_v, normal);
//				// Convert color to uint32_t for MLX
//				uint32_t pixel_color = ((uint32_t)(color.x * 255) << 24) | 
//									 ((uint32_t)(color.y * 255) << 16) | 
//									 ((uint32_t)(color.z * 255) << 8) | 
//									 0xFF;
//				mlx_put_pixel(s->image, x, y, pixel_color);
//			}
//			x++;
//		}
//		y++;
//	}
//}
//	
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

