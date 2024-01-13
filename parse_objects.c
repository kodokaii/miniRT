/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/13 22:47:40 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_sphere(t_rt *rt, char **line)
{
	t_sphere	sphere;
	t_list		*new_sphere;

	if (parse_vec3(line, sphere.pos, -FLT_MAX, FLT_MAX))
		return (EXIT_FAILURE);
	if (parse_value(line, &sphere.diameter, -FLT_MAX, FLT_MAX))
		return (EXIT_FAILURE);
	if (parse_color(line, sphere.color))
		return (EXIT_FAILURE);
	new_sphere = ft_lstnew(ft_memdup(&sphere, sizeof(t_sphere)));
	ft_lstadd_front(&rt->sphere, new_sphere);
	rt->count.sphere++;
	return (EXIT_SUCCESS);
}

int	parse_plane(t_rt *rt, char **line)
{
	t_plane	plane;
	t_list	*new_plane;

	if (parse_vec3(line, plane.pos, -FLT_MAX, FLT_MAX))
		return (EXIT_FAILURE);
	if (parse_vec3(line, plane.axis, -FLT_MAX, FLT_MAX))
		return (EXIT_FAILURE);
	if (parse_color(line, plane.color))
		return (EXIT_FAILURE);
	new_plane = ft_lstnew(ft_memdup(&plane, sizeof(t_plane)));
	ft_lstadd_front(&rt->plane, new_plane);
	rt->count.plane++;
	return (EXIT_SUCCESS);
}

int	parse_cylinder(t_rt *rt, char **line)
{
	t_cylinder	cylinder;
	t_list		*new_cylinder;

	if (parse_vec3(line, cylinder.pos, -FLT_MAX, FLT_MAX))
		return (EXIT_FAILURE);
	if (parse_vec3(line, cylinder.axis, -FLT_MAX, FLT_MAX))
		return (EXIT_FAILURE);
	if (parse_value(line, &cylinder.diameter, -FLT_MAX, FLT_MAX))
		return (EXIT_FAILURE);
	if (parse_value(line, &cylinder.height, -FLT_MAX, FLT_MAX))
		return (EXIT_FAILURE);
	if (parse_color(line, cylinder.color))
		return (EXIT_FAILURE);
	new_cylinder = ft_lstnew(ft_memdup(&cylinder, sizeof(t_cylinder)));
	ft_lstadd_front(&rt->cylinder, new_cylinder);
	rt->count.cylinder++;
	return (EXIT_SUCCESS);
}
