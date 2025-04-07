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

