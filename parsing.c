/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/02/03 15:13:05 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	_parse(t_rt *rt, char **line)
{
	if (**line == '#' || **line == '\n')
		return (EXIT_SUCCESS);
	else if (!parse_identifier(line, "A"))
		return (parse_ambient(rt, line));
	else if (!parse_identifier(line, "C"))
		return (parse_camera(rt, line));
	else if (!parse_identifier(line, "S"))
		return (parse_sky(rt, line));
	else if (!parse_identifier(line, "l"))
		return (parse_light(rt, line));
	else if (!parse_identifier(line, "sp"))
		return (parse_sphere(rt, line));
	else if (!parse_identifier(line, "pl"))
		return (parse_plane(rt, line));
	else if (!parse_identifier(line, "cy"))
		return (parse_cylinder(rt, line));
	else if (!parse_identifier(line, "tr"))
		return (parse_triangle(rt, line));
	else
		return (ft_error("Unknown identifier !", EXIT_FAILURE));
}

static int	_parse_line(t_rt *rt, char *line)
{
	line = ft_skip_blank(line);
	if (_parse(rt, &line))
		return (EXIT_FAILURE);
	if (*line != '#' && *ft_skip_blank(line) != '\n')
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

static int	_check_essential(t_rt *rt)
{
	if (rt->count.ambient < 1)
		return (ft_error("Missing ambient !", EXIT_FAILURE));
	if (rt->count.camera < 1)
		return (ft_error("Missing camera !", EXIT_FAILURE));
	if (rt->count.light < 1)
		return (ft_error("Missing light !", EXIT_FAILURE));
	if (rt->count.sky < 1)
		return (ft_error("Missing sky !", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

int	parse_rt(t_rt *rt, char *file)
{
	t_uint	line_count;
	t_buf	line;
	int		fd;

	line_count = 1;
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
			ft_dprintf(2, "line: %d\n", line_count);
			return (ft_buf_free(&line), ft_close(&fd), EXIT_FAILURE);
		}
		ft_buf_free(&line);
		line = ft_gnl(fd);
		line_count++;
	}
	return (ft_buf_free(&line), ft_close(&fd), _check_essential(rt));
}
