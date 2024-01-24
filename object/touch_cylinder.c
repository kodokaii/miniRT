/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/23 14:21:47 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static void	_set_uv(t_ray *ray, t_touch *touch)
{
	t_vec3	diff;

	kdm_vec3_sub(diff, touch->point, touch->ray.object->data.cylinder.pos);
	touch->uv[X] = 0.5 + atan2f(touch->point[X], touch->point[Z]) / TAU;
	touch->uv[Y] = kdm_vec3_dot(diff, ray->object->data.cylinder.axis)
		/ (2 * ray->object->data.cylinder.radius);
}

static int	_set_distance(float x[2], t_touch *touch)
{
	if (x[0] < 0.0f && x[1] < 0.0f)
		return (EXIT_FAILURE);
	else if (x[0] < 0.0f)
	{
		touch->distance = x[1];
		touch->side = INSIDE;
	}
	else
	{
		touch->distance = x[0];
		touch->side = OUTSIDE;
	}
	return (EXIT_SUCCESS);
}

static void	_set_normal(t_ray *ray, t_touch *touch)
{
	t_vec3	diff;
	t_vec3	height;

	kdm_vec3_sub(diff, touch->point, ray->object->data.cylinder.pos);
	kdm_vec3_scale(height, ray->object->data.cylinder.axis,
		kdm_vec3_dot(diff, ray->object->data.cylinder.axis));
	kdm_vec3_sub(touch->normal, diff, height);
	if (touch->side == INSIDE)
		kdm_vec3_negate(touch->normal);
	kdm_vec3_normalize(touch->normal);
}

int	touch_cylinder(t_ray *ray, float x[2], t_touch *touch)
{
	touch->ray = *ray;
	if (_set_distance(x, touch))
		return (EXIT_FAILURE);
	get_point(touch->point, ray->origin, ray->direction, touch->distance);
	_set_normal(ray, touch);
	_set_uv(ray, touch);
	shift_point(touch->point, touch->normal);
	return (EXIT_SUCCESS);
}
