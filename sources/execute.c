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

//void render_basic_sphere(t_scene *s)
//{
//	printf("Rendering basic ray-traced sphere...\n");
//	
//	if (!s->objects || !s->objects->content)
//	{
//		printf("Error: No objects in scene\n");
//		return;
//	}
//	t_sphere *sphere = (t_sphere *)s->objects->content;
//	
//	sphere->material.color = ft_create_vector(1.0, 0.2, 0.2); // Red
//	sphere->material.ambient = 0.1;
//	sphere->material.diffuse = 0.7;
//	sphere->material.specular = 0.2;
//	sphere->material.shininess = 200.0;
//	
//	sphere->transform = ft_create_identity_matrix();
//	if (!s->camera)
//	{
//		printf("Error: No camera in scene\n");
//		return;
//	}
//	if (!s->light)
//	{
//		printf("Error: No light in scene\n");
//		return;
//	}
//	printf("Camera position: (%f, %f, %f)\n", 
//		   s->camera->origin_point.x, s->camera->origin_point.y, s->camera->origin_point.z);
//	printf("Sphere center: (%f, %f, %f), diameter: %f\n", 
//		   sphere->center.x, sphere->center.y, sphere->center.z, sphere->diameter);
//	for (int y = 0; y < WIDTH; y++)
//	{
//		for (int x = 0; x < HEIGHT; x++)
//		{
//			mlx_put_pixel(s->image, x, y, 0x000000FF);
//		}
//	}
//	t_camera camera = ft_camera(HEIGHT, WIDTH, s->camera->field_of_view);
//	camera.origin_point = s->camera->origin_point;
//	camera.transform = s->camera->transform;
//	int hit_count = 0;
//	
//	for (int y = 0; y < WIDTH; y++)
//	{
//		for (int x = 0; x < HEIGHT; x++)
//		{
//			// Use ray_for_pixel instead of manual calculation
//			t_ray ray = ray_for_pixel(camera, x, y);
//			// Find intersections
//			t_list *xs_list = ft_intersection(ray, *sphere, NULL);
//			if (xs_list)
//			{
//				t_list *hit_node = ft_find_hit(xs_list);
//				if (hit_node)
//				{
//					hit_count++;
//					t_xs *hit = (t_xs *)hit_node->content;
//					t_tuple point = ft_position(ray, hit->time);
//					t_tuple normal = normal_at(*sphere, point);
//					t_tuple eye_v = ft_negate_tuple(ray.direction);
//					t_tuple color = lighting(sphere->material, *s->light, point, eye_v, normal);
//					if (color.x > 1) color.x = 1;
//					if (color.y > 1) color.y = 1;
//					if (color.z > 1) color.z = 1;
//					
//					uint32_t mlx_color = 
//						((uint32_t)(color.x * 255)) | 
//						((uint32_t)(color.y * 255) << 8) |
//						((uint32_t)(color.z * 255) << 16) | 
//						(255 << 24);
//					
//					mlx_put_pixel(s->image, x, y, mlx_color);
//				}
//				t_list *current = xs_list;
//				while (current)
//				{
//					t_list *next = current->next;
//					if (current->content)
//						free(current->content);
//					free(current);
//					current = next;
//				}
//			}
//		}
//		if (y % 50 == 0)
//			printf("Progress: %d%%\n", y * 100 / WIDTH);
//	}
//	printf("Rendering complete! Sphere hit count: %d pixels\n", hit_count);
//}
//
