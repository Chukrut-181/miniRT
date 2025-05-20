/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:44:53 by igchurru          #+#    #+#             */
/*   Updated: 2025/05/20 13:10:56 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

char	*get_one_line(int fd)
{
	char	c;
	char	*str;
	char	*temp;
	char	*aux;

	str = malloc(1 * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = 0;
	while (read(fd, &c, 1) > 0)
	{
		aux = str;
		temp = malloc(2 * sizeof(char));
		if (!temp)
		return (NULL);
		temp[0] = c;
		temp[1] = 0;
		str = ft_strjoin(aux, temp);
		free(temp);
		free(aux);
		if (c == '\n')
			break ;
	}
	return (str);
}

int	ft_parse_line(t_scene *scene, char *line)
{
	char	**temp;

	if (*line == '#')
		return (0);
	temp = ft_split(line, ' ');
	if (!ft_strncmp(temp[0], "A", 1) && ft_arraylen(temp) == 3
		&& ft_create_ambient(scene, temp))
		return (ft_free_array(temp), 0);
	else if (!ft_strncmp(temp[0], "C", 1) && ft_arraylen(temp) == 4
		&& !ft_create_camera(scene, temp))
		return (ft_free_array(temp), 0);
	else if (!ft_strncmp(temp[0], "L", 1) && ft_arraylen(temp) == 4
		&& !ft_create_light(scene->world, temp))
		return (ft_free_array(temp), 0);
	else if (!ft_strncmp(temp[0], "sp", 2) && ft_arraylen(temp) == 4
		&& !ft_create_sphere(scene, temp))
		return (ft_free_array(temp), 0);
	else if (!ft_strncmp(temp[0], "pl", 2) && ft_arraylen(temp) == 4
		&& !ft_create_plane(scene, temp))
		return (ft_free_array(temp), 0);
	// else if (!ft_strncmp(temp[0], "cy", 2) && ft_arraylen(temp) == 6
	// 	&& !ft_create_cylinder(scene, temp))
	// 	return (ft_free_array(temp), 0);
	else
		return (ft_free_array(temp), 1);
}

static void ft_open_scene(char *argv1, int *fd)
{
	char	*aux;

	aux = ft_strjoin("scenes/", argv1);
	*fd = open(aux, O_RDONLY);
	if (*fd <= 0)
	{
		free(aux);
		ft_error_exit(NULL, "Error\nCould not open scene", 1);
	}
	free(aux);
}

int	ft_get_scene(t_scene *scene, char *argv1)
{
	int		fd;
	char	*line;

	fd = 0;
	ft_open_scene(argv1, &fd);
	line = get_one_line(fd);
	while (line && ft_strlen(line) > 0)
	{
		if (*line != '\n' && ft_parse_line(scene, line))
		{
			free(line);
			ft_error_exit(scene, "Error\nIncorrect format encountered", 1);
		}
		free(line);
		line = get_one_line(fd);
	}
	close(fd);
	if (!scene->ambient || !scene->camera || !scene->world->light || !scene->world->objects)
		ft_error_exit(scene, "Error\nMissing mandatory elements", 1);
	return (0);
}
