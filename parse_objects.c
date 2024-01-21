/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/21 13:39:58 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_sphere(t_rt *rt, char **line)
{
	t_object	object;
	float		diameter;

	object.type = SPHERE;
	if (parse_vec3(line, object.data.sphere.pos, -FLT_MAX, FLT_MAX))
		return (EXIT_FAILURE);
	if (parse_value(line, &diameter, -FLT_MAX, FLT_MAX))
		return (EXIT_FAILURE);
	object.data.sphere.radius = diameter / 2;
	if (parse_color(line, object.color))
		return (EXIT_FAILURE);
	if (parse_value(line, &object.reflect, 0.0f, 1.0f))
		return (EXIT_FAILURE);
	return (add_object(rt, &object));
}

int	parse_plane(t_rt *rt, char **line)
{
	t_object	object;

	object.type = PLANE;
	if (parse_vec3(line, object.data.plane.pos, -FLT_MAX, FLT_MAX))
		return (EXIT_FAILURE);
	if (parse_vec3(line, object.data.plane.axis, -FLT_MAX, FLT_MAX))
		return (EXIT_FAILURE);
	if (kdm_vec3_norm(object.data.plane.axis) == 0.0f)
		return (ft_error("No plane orientation !", EXIT_FAILURE));
	kdm_vec3_normalize(object.data.plane.axis);
	if (parse_color(line, object.color))
		return (EXIT_FAILURE);
	if (parse_value(line, &object.reflect, 0.0f, 1.0f))
		return (EXIT_FAILURE);
	return (add_object(rt, &object));
}

int	parse_cylinder(t_rt *rt, char **line)
{
	t_object	object;
	float		diameter;

	object.type = CYLINDER;
	if (parse_vec3(line, object.data.cylinder.pos, -FLT_MAX, FLT_MAX))
		return (EXIT_FAILURE);
	if (parse_vec3(line, object.data.cylinder.axis, -FLT_MAX, FLT_MAX))
		return (EXIT_FAILURE);
	if (kdm_vec3_norm(object.data.cylinder.axis) == 0.0f)
		return (ft_error("No cylinder orientation !", EXIT_FAILURE));
	kdm_vec3_normalize(object.data.cylinder.axis);
	if (parse_value(line, &diameter, -FLT_MAX, FLT_MAX))
		return (EXIT_FAILURE);
	object.data.cylinder.radius = diameter / 2;
	if (parse_value(line, &object.data.cylinder.height, -FLT_MAX, FLT_MAX))
		return (EXIT_FAILURE);
	if (parse_color(line, object.color))
		return (EXIT_FAILURE);
	if (parse_value(line, &object.reflect, 0.0f, 1.0f))
		return (EXIT_FAILURE);
	return (add_object(rt, &object));
}
