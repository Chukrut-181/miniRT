#include "../include/minirt.h"

static void print_scene_data(t_scene *s)
{
	t_list *current;
	t_sphere *sphere;
	int obj_count = 0;

	// Print ambient light data
	if (s->ambient)
		printf("Ambient light: ratio->%f, rgb->(%f,%f,%f)\n", 
			s->ambient->ratio, 
			s->ambient->color.x, 
			s->ambient->color.y, 
			s->ambient->color.z);
	else
		printf("No ambient light defined\n");

	// Print camera data
	if (s->camera)
		printf("Camera: viewpoint->(%f,%f,%f), n_vector->(%f,%f,%f), fov->%f\n", 
			s->camera->origin_point.x, 
			s->camera->origin_point.y, 
			s->camera->origin_point.z, 
			s->camera->v_orientation.x, 
			s->camera->v_orientation.y, 
			s->camera->v_orientation.z, 
			s->camera->field_of_view);
	else
		printf("No camera defined\n");

	// Print light data
	if (s->light)
		printf("Light: position->(%f,%f,%f), intensity->(%f,%f,%f)\n", 
			s->light->position.x, 
			s->light->position.y, 
			s->light->position.z, 
			s->light->intensity.x, 
			s->light->intensity.y, 
			s->light->intensity.z);
	else
		printf("No light defined\n");

	// Print objects data
	printf("\n--- Objects ---\n");
	current = s->objects;
	while (current)
	{
		obj_count++;
		// Assuming all objects in the list are spheres for now
		sphere = (t_sphere *)current->content;
		printf("Sphere %d: center->(%f,%f,%f), diameter->%f, color->(%f,%f,%f)\n", 
			obj_count,
			sphere->center.x, 
			sphere->center.y, 
			sphere->center.z, 
			sphere->diameter, 
			sphere->material.color.x, 
			sphere->material.color.y, 
			sphere->material.color.z);
		
		// Print transformation matrix
		printf("  Transform matrix:\n");
		for (int i = 0; i < 4; i++)
		{
			printf("  [ ");
			for (int j = 0; j < 4; j++)
				printf("%f ", sphere->transform.data[i][j]);
			printf("]\n");
		}
		
		current = current->next;
	}
	
	if (obj_count == 0)
		printf("No objects defined\n");
}


static	void	parse_line(t_scene *s, char *line)
{
	char **res = ft_split(line, 32);
	if (ft_strcmp(res[0], "A") == 0)
		create_ambient_light(s, res);
	else if (ft_strcmp(res[0], "c") == 0)
		create_camera(res, s);
	else if (ft_strcmp(res[0], "l") == 0)
		create_light(res, s);
	else if (ft_strcmp(res[0], "sp") == 0)
		create_sphere(res, s);
//	else if (ft_strcmp(res[0], "pl") == 0)
//		create_plane(res);
//	else if (ft_strcmp(res[0], "cy") == 0)
//		create_cylinder(res);
	ft_free_array(res);
}

void	parse(t_scene *s, char **argv)
{
	int fd;
	char *line;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	line = ft_get_next_line(fd);
	while (1)
	{
		if (line == NULL)
			break;
		parse_line(s, line);
//		printf("%s\n", line);
		free(line);
		line = ft_get_next_line(fd);
	}
	// pruebas aqui
	print_scene_data(s);
}

//int	main(int argc, char **argv)
//{
//	t_scene s;
//
//	(void)argc;
//	s.mlx = NULL;
//	s.image = NULL;
//	s.objects = NULL;
//	s.camera = NULL;
//	s.ray = NULL;
//	s.ambient = NULL;
////	check_arg(argc, argv);
//	init_mlx(&s);
//	parse(&s, argv);
////	execute(&s);
////	mlx_image_to_window(s->mlx, s->image, 0, 0);
////	mlx_key_hook(s->mlx, ft_handle_key, s->mlx);
////	mlx_loop(s->mlx);
////	mlx_terminate(s->mlx);
//	return (0);
//}
//
