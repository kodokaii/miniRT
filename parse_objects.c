/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/31 13:57:13 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_sphere(t_rt *rt, char **line)
{
	t_object	object;

	object = (t_object){.type = SPHERE};
	if (parse_vec3(line, object.pos, -FLT_MAX, FLT_MAX))
		return (EXIT_FAILURE);
	if (parse_value(line, &object.width, -FLT_MAX, FLT_MAX))
		return (EXIT_FAILURE);
	if (parse_color(line, object.color))
		return (EXIT_FAILURE);
	if (parse_value(line, &object.reflect, 0.0f, 1.0f))
		return (EXIT_FAILURE);
	if (parse_object_texture(line, &object))
		return (EXIT_FAILURE);
	if (parse_object_texture(line, &object))
		return (EXIT_FAILURE);
	kdm_vec3(object.x, (t_vec3){1.0f, 0.0f, 0.0f});
	kdm_vec3(object.y, (t_vec3){0.0f, 1.0f, 0.0f});
	kdm_vec3(object.z, (t_vec3){0.0f, 0.0f, 1.0f});
	return (add_object(rt, &object));
}

int	parse_plane(t_rt *rt, char **line)
{
	t_object	object;

	object = (t_object){.type = PLANE};
	if (parse_vec3(line, object.pos, -FLT_MAX, FLT_MAX))
		return (EXIT_FAILURE);
	if (parse_vec3(line, object.z, -FLT_MAX, FLT_MAX))
		return (EXIT_FAILURE);
	if (kdm_vec3_dot(object.z, object.z) == 0.0f)
		return (ft_error("No plane orientation !", EXIT_FAILURE));
	kdm_vec3_normalize(object.z);
	if (parse_color(line, object.color))
		return (EXIT_FAILURE);
	if (parse_value(line, &object.reflect, 0.0f, 1.0f))
		return (EXIT_FAILURE);
	if (parse_object_texture(line, &object))
		return (EXIT_FAILURE);
	if (parse_object_texture(line, &object))
		return (EXIT_FAILURE);
	kdm_vec3_crossn(object.x, (t_vec3){0, 1, 0}, object.z);
	kdm_vec3_crossn(object.y, object.z, object.x);
	return (add_object(rt, &object));
}

int	parse_cylinder(t_rt *rt, char **line)
{
	t_object	object;

	object = (t_object){.type = CYLINDER};
	if (parse_vec3(line, object.pos, -FLT_MAX, FLT_MAX))
		return (EXIT_FAILURE);
	if (parse_vec3(line, object.z, -FLT_MAX, FLT_MAX))
		return (EXIT_FAILURE);
	if (kdm_vec3_dot(object.z, object.z) == 0.0f)
		return (ft_error("No cylinder orientation !", EXIT_FAILURE));
	kdm_vec3_normalize(object.z);
	if (parse_value(line, &object.width, -FLT_MAX, FLT_MAX))
		return (EXIT_FAILURE);
	if (parse_value(line, &object.height, -FLT_MAX, FLT_MAX))
		return (EXIT_FAILURE);
	if (parse_color(line, object.color))
		return (EXIT_FAILURE);
	if (parse_value(line, &object.reflect, 0.0f, 1.0f))
		return (EXIT_FAILURE);
	if (parse_object_texture(line, &object))
		return (EXIT_FAILURE);
	if (parse_object_texture(line, &object))
		return (EXIT_FAILURE);
	kdm_vec3_crossn(object.x, (t_vec3){0, 1, 0}, object.z);
	kdm_vec3_crossn(object.y, object.z, object.x);
	return (add_object(rt, &object));
}
