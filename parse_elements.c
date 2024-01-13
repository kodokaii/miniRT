/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/13 22:46:48 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_ambient(t_rt *rt, char **line)
{
	if (0 < rt->count.ambient)
		return (ft_error("Too many ambient !", EXIT_FAILURE));
	if (parse_value(line, &rt->ambient.ratio, 0.0f, 1.0f))
		return (EXIT_FAILURE);
	if (parse_color(line, rt->ambient.color))
		return (EXIT_FAILURE);
	rt->count.ambient++;
	return (EXIT_SUCCESS);
}

int	parse_camera(t_rt *rt, char **line)
{
	if (0 < rt->count.camera)
		return (ft_error("Too many camera !", EXIT_FAILURE));
	if (parse_vec3(line, rt->camera.pos, -FLT_MAX, FLT_MAX))
		return (EXIT_FAILURE);
	if (parse_vec3(line, rt->camera.axis, -FLT_MAX, FLT_MAX))
		return (EXIT_FAILURE);
	if (parse_value(line, &rt->camera.fov, 0.0f, 180.0f))
		return (EXIT_FAILURE);
	rt->count.camera++;
	return (EXIT_SUCCESS);
}

int	parse_light(t_rt *rt, char **line)
{
	if (0 < rt->count.light)
		return (ft_error("Too many light !", EXIT_FAILURE));
	if (parse_vec3(line, rt->light.pos, -FLT_MAX, FLT_MAX))
		return (EXIT_FAILURE);
	if (parse_value(line, &rt->light.ratio, 0.0, 1.0f))
		return (EXIT_FAILURE);
	if (parse_color(line, rt->light.color))
		return (EXIT_FAILURE);
	rt->count.light++;
	return (EXIT_SUCCESS);
}
