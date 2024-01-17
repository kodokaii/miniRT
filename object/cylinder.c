/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/17 23:33:00 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static float	_clamp_height(t_vec3 origin, t_vec3 direction,
					float distance, t_object *object)
{
	t_vec3	point;
	t_vec3	diff;
	float	h;

	if (0 <= distance)
	{
		get_point(point, origin, direction, distance);
		kdm_vec3_sub(diff, point, object->data.cylinder.pos);
		h = kdm_vec3_dot(diff, object->data.cylinder.axis);
		if (h < 0 || object->data.cylinder.height < h)
			return (INVALID_DISTANCE);
	}
	return (distance);
}

static float	_get_distance(t_vec3 origin, t_vec3 direction,
					float x[2], t_object *object)
{
	x[0] = _clamp_height(origin, direction, x[0], object);
	x[1] = _clamp_height(origin, direction, x[1], object);
	if (x[0] < 0.0f)
		return (x[1]);
	else if (x[1] < 0.0f)
		return (x[0]);
	else
		return (fmin(x[0], x[1]));
}

void	normal_cylinder(t_vec3 normal, t_vec3 point, t_object *object)
{
	t_vec3	diff;
	t_vec3	height;

	kdm_vec3_sub(diff, point, object->data.cylinder.pos);
	kdm_vec3_scale(height, object->data.cylinder.axis,
		kdm_vec3_dot(diff, object->data.cylinder.axis));
	kdm_vec3_sub(normal, point, object->data.cylinder.pos);
}

int	ray_cylinder(t_vec3 origin, t_vec3 direction, float *d, t_object *object)
{
	float	a;
	float	b;
	float	c;
	float	x[2];
	t_vec3	diff;

	kdm_vec3_sub(diff, origin, object->data.cylinder.pos);
	a = kdm_vec3_dot(direction, direction)
		- kdm_square(kdm_vec3_dot(direction, object->data.cylinder.axis));
	b = 2.0f * (kdm_vec3_dot(direction, diff)
			- kdm_vec3_dot(direction, object->data.cylinder.axis)
			* kdm_vec3_dot(diff, object->data.cylinder.axis));
	c = kdm_vec3_dot(diff, diff)
		- kdm_square(kdm_vec3_dot(diff, object->data.cylinder.axis))
		- kdm_square(object->data.cylinder.radius);
	if (kdm_quadratic_equation(x, a, b, c))
		return (EXIT_FAILURE);
	*d = _get_distance(origin, direction, x, object);
	if (*d < 0.0f)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
