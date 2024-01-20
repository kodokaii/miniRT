/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/19 23:37:32 by nlaerema         ###   ########.fr       */
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
	if (kdm_vec3_norm(rt->camera.axis) == 0.0f)
		return (ft_error("No camera orientation !", EXIT_FAILURE));
	kdm_vec3_normalize(rt->camera.axis);
	rt->camera.yaw = atan2f(rt->camera.axis[Y], rt->camera.axis[X]);
	rt->camera.pitch = asinf(rt->camera.axis[Z]);
	if (parse_value(line, &rt->camera.fov, 0.0f, 180.0f))
		return (EXIT_FAILURE);
	if (rt->camera.fov == 0.0f)
		return (ft_error("No FOV !", EXIT_SUCCESS));
	rt->camera.fov = kdm_rad(rt->camera.fov);
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
