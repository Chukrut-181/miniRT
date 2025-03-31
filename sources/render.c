#include "../include/minirt.h"

//int	ray_object(t_list *object, t_ray *r, t_xs *inter)
//{
//}
//
//int	calculate_inter(t_scene *scene, t_ray *r, t_xs *inter)
//{
//	t_list		*temp_list;
//	t_xs		temp_inter;
//	int		hit;
//
//	hit = 0;
//	inter->time = INFINITY;
//	temp_list = scene->objects;
//	while (temp_list)
//	{
//		if (ray_object(temp_list, r, &temp_inter) == 1)
//		{
//			if (temp_inter.time < inter->time && temp_inter.time > 0)
//			{
//				*inter = temp_inter;
//				hit = 1;
//			}
//		}
//		temp_list = temp_list->next;
//	}
//	return (hit);
//}
//
//t_tuple	check_inter(t_scene *scene, int i, int j)
//{
//	t_ray	r;
//	t_ray	new_ray;
//	t_xs	intersection;
//	t_tuple	color;
//
//	r = ray_for_pixel(scene->camear, i, j); 
//	transform_ray(&r, scene->camera->mat, &new_ray);
//	calculate_inter(scene, &new_ray, &intersection);
//	if (calculate_inter == 1)
//	{
//		color = get_color(intersection, scene, new_ray);
//		return (color);
//	}
//	color = ft_create_point(0, 0, 0);
//	return (color);
//}
//
//void	put_image(t_scene *scene)
//{
//	int i, j;
//	t_tuple pixel_color;
//
//	i = 0;
//	while (i < scene->image->height)
//	{
//		j = 0;
//		while (j < scene->image->width)
//		{
//			pixel_color = check_inter(scene, i, j);
//			write_pixel(scene->image, x, y, pixel_color);
//			i++;
//		}
//		j++;
//	}	
//}
//
//void	render(t_scene *scene)
//{
//	put_image(scene);
//}
