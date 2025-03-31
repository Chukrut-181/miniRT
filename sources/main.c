/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: igchurru <igchurru@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/19 11:26:57 by igchurru		  #+#	#+#			 */
/*   Updated: 2025/03/24 12:20:11 by eandres          ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "../include/minirt.h"

// 1.inicializar
// 2.check argument
// 3.init mlx
// 4.parse
// 5.render (execute)
// 6.clean all

//static	void	init_mlx(t_scene *scene)
//{
//	scene->mlx = mlx_init(800, 600, "miniRT", true);
//	if (!scene->mlx)
//	{
//		write(2, "Error\n", 6);
//		exit(1);
//	}
//	scene->mlx_image = mlx_new_image(scene->mlx, 800, 600);
//	if (!scene->mlx_image)
//	{
//		write(2, "Error\n", 6);
//		mlx_terminate(mlx);
//		exit(1);
//	}
//}
//
//static	void	check_arg(int argc, char **argv)
//{
//	if (argc != 2 || ft_strncmp(argv[1], ".rt", 3) == 1);
//	{
//		write(2, "Error\n", 6);
//		exit(1);
//	}
//}

int	main(int argc, char **argv)
{
	t_scene *scene;

	(void)argc;
	scene = NULL;
//	check_arg(argc, argv);
//	init_mlx(scene);
	parse(scene, argv);
	return (0);
}
