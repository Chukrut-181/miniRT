#include "../include/minirt.h"

// 1.inicializar
// 2.check argument
// 3.init mlx
// 4.parse
// 5.render (execute)
// 6.clean all

static	void	init_mlx(t_scene *scene)
{
	scene->mlx = mlx_init(2400, 1800, "miniRT", true);
	if (!scene->mlx)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	scene->image = mlx_new_image(scene->mlx, 2400, 1800);
	if (!scene->image)
	{
		write(2, "Error\n", 6);
		mlx_terminate(scene->mlx);
		exit(1);
	}
}

static	void	check_arg(int argc, char **argv)
{
	if (argc != 2 || ft_strncmp(argv[1], ".rt", 3) == 1)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	t_scene scene;

	if (argc != 2)
	{
		write(2, "Error\nUsage: ./miniRT scene.rt\n", 37);
		return (1);
	}
	ft_memset(&scene, 0, sizeof(t_scene));
//	s.mlx = NULL;
//	s.image = NULL;
//	s.objects = NULL;
//	s.camera = NULL;
//	s.ray = NULL;
//	s.ambient = NULL;
	check_arg(argc, argv);
	init_mlx(&scene);
	parse(&scene, argv);
//	render_scene(&scene);
//	render_test_gradient(&scene);
//	render_test_sphere(&scene);
//	render_basic_sphere(&scene);
	render_lit_sphere(&scene);
	mlx_image_to_window(scene.mlx, scene.image, 0, 0);
	mlx_key_hook(scene.mlx, ft_handle_key, &scene);
	mlx_loop(scene.mlx);
	mlx_terminate(scene.mlx);
	return (0);
}

