#include "../include/minirt.h"

void render_test_gradient(t_scene *s)
{
	printf("Rendering test gradient...\n");
	
	// Clear the image
	for (int y = 0; y < WIDTH; y++)
	{
		for (int x = 0; x < HEIGHT; x++)
		{
			// Create a simple gradient
			uint8_t r = (uint8_t)((float)x / HEIGHT * 255);
			uint8_t g = (uint8_t)((float)y / WIDTH * 255);
			uint8_t b = 128;
			
			// MLX42 uses RGBA format
			uint32_t color = (r) | (g << 8) | (b << 16) | (255 << 24);
			
			mlx_put_pixel(s->image, x, y, color);
		}
	}
	
	printf("Test gradient complete!\n");
}

void render_test_sphere(t_scene *s)
{
	printf("Rendering test sphere...\n");
	
	// Sphere parameters
	int center_x = HEIGHT / 2;
	int center_y = WIDTH / 2;
	int radius = 100;
	
	// Draw a simple sphere
	for (int y = 0; y < WIDTH; y++)
	{
		for (int x = 0; x < HEIGHT; x++)
		{
			// Calculate distance from center
			int dx = x - center_x;
			int dy = y - center_y;
			int distance_squared = dx*dx + dy*dy;
			
			// If inside the sphere
			if (distance_squared <= radius*radius)
			{
				// Simple shading based on distance from center
				float normalized_distance = sqrtf((float)distance_squared) / radius;
				uint8_t intensity = (uint8_t)((1.0f - normalized_distance) * 255);
				
				// Red sphere
				uint32_t color = (intensity) | (0 << 8) | (0 << 16) | (255 << 24);
				
				mlx_put_pixel(s->image, x, y, color);
			}
		}
	}
	
	printf("Test sphere complete!\n");
}

void render_lit_sphere(t_scene *s)
{
	t_ray ray;
	t_list *xs_list;
	t_xs *intersection;
	t_tuple point;
	t_tuple normal;
	t_tuple eye_v;
	t_tuple color;
	t_sphere *sphere;
	int x, y;
	
	sphere = (t_sphere *)s->objects->content;
//	sphere->material = ft_create_material(1, 0.2, 1);  con estos valores si que funciona pero en el archivo .rt
//      los valores son en rgb.
	
//	eye_pos = ft_create_point(0, 0, -1000); si introduzco los valores a mano, no se ve el reflejo de luz, sin embarg
//	si los meto con ft_create_point() si funciona, creo que es por el valor de la w.
	
	// Render the sphere with lighting
	y = 0;
	while(y < 1800)
	{
		x = 0;
		while(x < 2400)
		{
			// Create a ray from the eye through this pixel
			t_tuple pixel_point = ft_create_point(x - 1200, 900 - y, 0);
			t_tuple direction = ft_normalize(ft_substract_tuples(pixel_point, s->camera->origin_point));
			ray = ft_create_ray(s->camera->origin_point, direction);
			xs_list = ft_intersection(ray, *sphere, NULL);
			if (xs_list)
			{
				// Find the hit point (the closest intersection in front of the eye)
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
					// Calculate the actual point of intersection
					point = ft_position(ray, intersection->time);
					// Calculate the normal at the intersection point
					normal = normal_at(*sphere, point);
					// Calculate the eye vector
					eye_v = ft_normalize(ft_negate_tuple(ray.direction));
					// Calculate the color using the lighting function
					color = lighting(sphere->material, *s->light, point, eye_v, normal);
					// Convert color to uint32_t for MLX
					uint32_t pixel_color = ((uint32_t)(color.x * 255) << 24) | 
										 ((uint32_t)(color.y * 255) << 16) | 
										 ((uint32_t)(color.z * 255) << 8) | 
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

