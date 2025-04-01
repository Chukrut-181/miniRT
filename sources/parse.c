/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:44:53 by igchurru          #+#    #+#             */
/*   Updated: 2025/04/01 12:10:29 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

ft_parse_line(t_scene *scene, char *line)
{
	char	**temp;

	temp = ft_split(line, ' ');
	if (!ft_strcmp(temp[0], "A") && ft_arraylen(temp) == 3 && !create_ambient(scene, temp))
		return (ft_free_array(temp), 0);
}

int	ft_get_scene(t_scene *scene, char *argv1)
{
	int		fd;
	char	*aux;
	char 	*line;
	
	aux = ft_strjoin("scenes/", argv1);
	fd = open(aux, O_RDONLY);
	if (fd < 0)
	{
		free(aux);
		ft_error_exit("Error: Could not open scene\n", 1);
	}
	free(aux);
	line = ft_get_next_line(fd);
	while (line)
	{
		if (*line != '\n' && ft_parse_line(scene, line));
		{
			free(line);
			ft_error_exit("Error: Incorrect format encountered\n", 1);
		}
		free(line);
		line = ft_get_next_line(fd);
	}
	close(fd);
}
// 	char	**line_split;

// 	line_split = splitstr(line, ' ');
// 	if (!ft_strcmp(line_split[0], "A") && splitlen(line_split) == 3
// 		&& !create_ambient(data, line_split))
// 		return (splitfree(line_split), 0);
// 	else if (!ft_strcmp(line_split[0], "C") && splitlen(line_split) == 4
// 		&& !create_camera(data, line_split))
// 		return (splitfree(line_split), 0);
// 	else if (!ft_strcmp(line_split[0], "L") && splitlen(line_split) == 4
// 		&& !create_light(data, line_split))
// 		return (splitfree(line_split), 0);
// 	else if (!ft_strcmp(line_split[0], "sp") && splitlen(line_split) == 4
// 		&& !create_sphere(data, line_split))
// 		return (splitfree(line_split), 0);
// 	else if (!ft_strcmp(line_split[0], "cy") && splitlen(line_split) == 6
// 		&& !create_cylinder(data, line_split))
// 		return (splitfree(line_split), 0);
// 	else if (!ft_strcmp(line_split[0], "pl") && splitlen(line_split) == 4
// 		&& !create_plane(data, line_split))
// 		return (splitfree(line_split), 0);
// 	else
// 		return (splitfree(line_split),
// 			printfd(STDERR_FILENO, BAD_ELEM_FORMAT), 1);
// }