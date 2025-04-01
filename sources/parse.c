/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igchurru <igchurru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:44:53 by igchurru          #+#    #+#             */
/*   Updated: 2025/04/01 15:00:36 by igchurru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	ft_parse_line(t_scene *scene, char *line)
{
	char	**temp;

	temp = ft_split(line, ' ');
	if (!ft_strncmp(temp[0], "A", 1) && ft_arraylen(temp) == 3
		&& !ft_create_ambient(scene, temp))
		return (ft_free_array(temp), 0);
	else
		return (ft_free_array(temp), 1);
}

int	ft_get_scene(t_scene *scene, char *argv1)
{
	int		fd;
	char	*aux;
	char	*line;

	aux = ft_strjoin("scenes/", argv1);
	fd = open(aux, O_RDONLY);
	if (fd < 0)
	{
		free(aux);
		ft_error_exit("Error: Could not open scene", 1);
	}
	free(aux);
	line = ft_get_next_line(fd);
	while (line)
	{
		if (*line != '\n' && ft_parse_line(scene, line))
		{
			free(line);
			ft_error_exit("Error: Incorrect format encountered", 1);
		}
		free(line);
		line = ft_get_next_line(fd);
	}
	close(fd);
	return (0);
}
