/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/13 22:58:29 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	_parse_identifier(char **line, char *identifier)
{
	size_t	i;

	i = 0;
	while ((*line)[i] && (*line)[i] == identifier[i])
		i++;
	if (!ft_isspace((*line)[i]))
		return (EXIT_FAILURE);
	(*line) += i;
	return (EXIT_SUCCESS);
}

static int	_parse_line(t_rt *rt, char *line)
{
	int	error;

	line = ft_skip_blank(line);
	if (*line == '\n')
		error = EXIT_SUCCESS;
	else if (!_parse_identifier(&line, "A"))
		error = parse_ambient(rt, &line);
	else if (!_parse_identifier(&line, "C"))
		error = parse_camera(rt, &line);
	else if (!_parse_identifier(&line, "L"))
		error = parse_light(rt, &line);
	else if (!_parse_identifier(&line, "sp"))
		error = parse_sphere(rt, &line);
	else if (!_parse_identifier(&line, "pl"))
		error = parse_plane(rt, &line);
	else if (!_parse_identifier(&line, "cy"))
		error = parse_cylinder(rt, &line);
	else
		return (ft_error("Unknown identifier !", EXIT_FAILURE));
	if (error)
		return (EXIT_FAILURE);
	if (*ft_skip_blank(line) != '\n')
		return (ft_error("Too many Value !", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

static int	_check_extension(char *file)
{
	file = ft_strrchr(file, '.');
	if (!file || ft_strcmp(file, ".rt"))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parse_rt(t_rt *rt, char *file)
{
	t_buf	line;
	int		fd;

	if (_check_extension(file))
		return (ft_error("Invalid extension !", EXIT_FAILURE));
	fd = open(file, O_RDONLY);
	if (fd == INVALID_FD)
		return (ft_error("Can't open file !", EXIT_FAILURE));
	line = ft_gnl(fd);
	if (line.size == INVALID_SIZE)
		return (ft_error("Can't read file !", EXIT_FAILURE));
	while (0 < line.size)
	{
		if (_parse_line(rt, line.buf))
		{
			ft_buf_free(&line);
			ft_close(&fd);
			return (EXIT_FAILURE);
		}
		ft_buf_free(&line);
		line = ft_gnl(fd);
	}
	ft_buf_free(&line);
	ft_close(&fd);
	return (EXIT_SUCCESS);
}
