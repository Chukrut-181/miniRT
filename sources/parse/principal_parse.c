#include "../../include/minirt.h"

static	void	parse_line(t_scene *s, char *line)
{
	char **res = ft_split(line, 32);
	if (ft_strcmp(res[0], "A") == 0)
		create_ambient_light(s, res);
	else if (ft_strcmp(res[0], "C") == 0)
		create_camera(res, s);
	else if (ft_strcmp(res[0], "L") == 0)
		create_light(res, s);
	else if (ft_strcmp(res[0], "sp") == 0)
		create_sphere(res, s);
//	else if (ft_strcmp(res[0], "pl") == 0)
//		create_plane(res);
//	else if (ft_strcmp(res[0], "cy") == 0)
//		create_cylinder(res);
	ft_free_array(res);
}

static	void	parse(t_scene *s, char **argv)
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
	
}

int	main(int argc, char **argv)
{
	t_scene s;

	(void)argc;
	s.mlx = NULL;
	s.image = NULL;
	s.objects = NULL;
	s.camera = NULL;
	s.ray = NULL;
	s.ambient = NULL;
//	check_arg(argc, argv);
//	init_mlx(scene);
	parse(&s, argv);
	return (0);
}

