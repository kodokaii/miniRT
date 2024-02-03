/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/02/03 13:07:33 by nlaerema         ###   ########.fr       */
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
	if (parse_material(line, &object))
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
	if (!kdm_vec3_dot(object.z, object.z))
		return (ft_error("No plane orientation !", EXIT_FAILURE));
	kdm_vec3_normalize(object.z);
	if (parse_material(line, &object))
		return (EXIT_FAILURE);
	kdm_vec3_crossn(object.x, (t_vec3){0, 1, 0}, object.z);
	if (!kdm_vec3_dot(object.x, object.x))
		kdm_vec3_cpy(object.x, (t_vec3){1, 0, 0});
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
	if (!kdm_vec3_dot(object.z, object.z))
		return (ft_error("No cylinder orientation !", EXIT_FAILURE));
	kdm_vec3_normalize(object.z);
	if (parse_value(line, &object.width, -FLT_MAX, FLT_MAX))
		return (EXIT_FAILURE);
	if (parse_value(line, &object.height, -FLT_MAX, FLT_MAX))
		return (EXIT_FAILURE);
	if (parse_material(line, &object))
		return (EXIT_FAILURE);
	kdm_vec3_crossn(object.x, (t_vec3){0, 1, 0}, object.z);
	if (!kdm_vec3_dot(object.x, object.x))
		kdm_vec3_cpy(object.x, (t_vec3){1, 0, 0});
	kdm_vec3_crossn(object.y, object.z, object.x);
	return (add_object(rt, &object));
}

int	parse_triangle(t_rt *rt, char **line)
{
	t_object	object;
	t_vec3		delta1;
	t_vec3		delta2;

	object = (t_object){.type = TRIANGLE};
	if (parse_vec3(line, object.vertex1, -FLT_MAX, FLT_MAX))
		return (EXIT_FAILURE);
	if (parse_vec3(line, object.vertex2, -FLT_MAX, FLT_MAX))
		return (EXIT_FAILURE);
	if (parse_vec3(line, object.vertex3, -FLT_MAX, FLT_MAX))
		return (EXIT_FAILURE);
	if (parse_material(line, &object))
		return (EXIT_FAILURE);
	kdm_vec3_addv(object.pos, 3,
		object.vertex1, object.vertex2, object.vertex3);
	kdm_vec3_divs(object.pos, object.pos, 3);
	kdm_vec3_sub(delta1, object.vertex2, object.vertex1);
	kdm_vec3_sub(delta2, object.vertex3, object.vertex1);
	kdm_vec3_crossn(object.z, delta1, delta2);
	kdm_vec3_crossn(object.x, (t_vec3){0, 1, 0}, object.z);
	if (!kdm_vec3_dot(object.x, object.x))
		kdm_vec3_cpy(object.x, (t_vec3){1, 0, 0});
	kdm_vec3_crossn(object.y, object.z, object.x);
	return (add_object(rt, &object));
}

int	add_object(t_rt *rt, t_object *object)
{
	t_list	*new_object;

	if (object->type == INVALID_OBJECT)
		return (EXIT_FAILURE);
	new_object = ft_lstnew(ft_memdup(object, sizeof(t_object)));
	ft_lstadd_front(&rt->object, new_object);
	rt->count.object[object->type]++;
	return (EXIT_SUCCESS);
}
