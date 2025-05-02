#include "../include/minirt.h"

void render_scene(t_scene *s)
{
	t_list *current = s->objects;

	current = s->objects;
	while (current)
	{
		t_type obj_type = *(t_type *)(current->content);
		
		if (obj_type == PLANE)
			render_single_plane(s, (t_plane *)current->content);
		else if (obj_type == SPHERE)
			render_single_sphere(s, (t_sphere *)current->content);
		current = current->next;
	}
}

static t_ray ray_pixel(t_camera *camera, int x, int y)
{
	// convertir coordenadas de pixel a coordenadas normalizadas (-1 a 1)
	float pixel_x = (float)x / WIDTH * 2 - 1;
	float pixel_y = 1 - (float)y / HEIGHT * 2;
	
	// ajustar según el campo de vision (FOV)
//	float aspect_ratio = (float)WIDTH / HEIGHT;
//	float fov_factor = tanf(camera->field_of_view / 2);
//	
//	pixel_x *= fov_factor * aspect_ratio;
//	pixel_y *= fov_factor;
	
	// crear un punto en el espacio de la camara
	// usamos -1 para la coordenada z para que el rayo apunte hacia adelante (-Z)
	t_tuple pixel_point = ft_create_point(pixel_x, pixel_y, -1);
	
	// transformar el punto al espacio mundial usando la matriz de transformacion de la camara
	t_tuple world_point = ft_multiply_mat_and_tuple(camera->transform, pixel_point);
	
	// crear el rayo desde la posicion de la camara hacia el punto mundial
	t_tuple direction = ft_normalize(ft_substract_tuples(world_point, camera->viewpoint));
	return (ft_create_ray(camera->viewpoint, direction));
}

//t_xs	calculate_intersection(t_scene *s, t_ray *ray)
//{
//	t_list *current;
//	t_type obj_type;
//
//	current = s->objects;
//	while (current)
//	{
//		obj_type = *(t_type *)(current->content);
//		if (obj_type == PLANE)
//			res = intersect((t_plane *)current->content, ray);
//	}
//}

void render_single_plane(t_scene *s, t_plane *plane)
{
	t_ray ray;
	t_xs intersection;
	t_tuple point;
	t_tuple normal;
	t_tuple eye_v;
	t_color color;
	int x, y;
	
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = ray_pixel(s->camera, x, y);
			intersection = intersect(plane, &ray);
			
			if (intersection.hit)
			{
				// Calcular el punto real de intersección
				point = ft_position(ray, intersection.time);
				// Obtener la normal en el punto de intersección
				normal = normal_at_plane(*plane, point);
				// Calcular el vector de vista
				eye_v = ft_normalize(ft_negate_tuple(ray.direction));
				// Calcular el color usando la función de iluminación
				color = lighting(plane->material, *s->light, point, eye_v, normal);
				// Convertir color a uint32_t para MLX
				uint32_t pixel_color = ((uint32_t)(color.r) << 24) | 
									 ((uint32_t)(color.g) << 16) | 
									 ((uint32_t)(color.b) << 8) | 
									 0xFF;
				mlx_put_pixel(s->image, x, y, pixel_color);
			}
			x++;
		}
		y++;
	}
}

void render_single_sphere(t_scene *s, t_sphere *sphere)
{
	t_ray ray;
	t_list *xs_list;
	t_xs *intersection;
	t_tuple point;
	t_tuple normal;
	t_tuple eye_v;
	t_color color;
	int x, y;
	
	y = 0;
	while(y < HEIGHT)
	{
		x = 0;
		while(x < WIDTH)
		{
			ray = ray_pixel(s->camera, x, y);
			xs_list = ft_intersection(ray, *sphere, NULL);
			
			if (xs_list)
			{
				intersection = NULL;
				while (xs_list)
				{
					t_xs *current = (t_xs *)xs_list->content;
					if (current->hit)
					{
						intersection = current;
						break;
					}
					xs_list = xs_list->next;
				}
				if (intersection)
				{
					// Calcular el punto real de intersección
					point = ft_position(ray, intersection->time);
					// Calcular la normal en el punto de intersección
					normal = normal_at(*sphere, point);
					// Calcular el vector de vista
					eye_v = ft_normalize(ft_negate_tuple(ray.direction));
					// Calcular el color usando la función de iluminación
					color = lighting(sphere->material, *s->light, point, eye_v, normal);
					// Convertir color a uint32_t para MLX
					uint32_t pixel_color = ((uint32_t)(color.r) << 24) | 
										 ((uint32_t)(color.g) << 16) | 
										 ((uint32_t)(color.b) << 8) | 
										 0xFF;
					mlx_put_pixel(s->image, x, y, pixel_color);
				}
				ft_lstclear(&xs_list, free);
			}
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

