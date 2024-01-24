/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/23 13:13:44 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static void	_set_uv(t_ray *ray, t_touch *touch)
{
	(void)ray;
	touch->uv[X] = 0.0f;
	touch->uv[Y] = 0.0f;
}

static int	_set_distance(t_ray *ray, float x, t_touch *touch)
{
	if (x < 0.0f)
		return (EXIT_FAILURE);
	else
		touch->distance = x;
	if (kdm_vec3_dot(ray->direction, ray->object->data.plane.axis) < 0.0f)
		touch->side = OUTSIDE;
	else
		touch->side = INSIDE;
	return (EXIT_SUCCESS);
}

static void	_set_normal(t_ray *ray, t_touch *touch)
{
	kdm_vec3_cpy(touch->normal, ray->object->data.plane.axis);
	if (touch->side == INSIDE)
		kdm_vec3_negate(touch->normal);
	kdm_vec3_normalize(touch->normal);
}

int	touch_plane(t_ray *ray, float x, t_touch *touch)
{
	touch->ray = *ray;
	if (_set_distance(ray, x, touch))
		return (EXIT_FAILURE);
	get_point(touch->point, ray->origin, ray->direction, touch->distance);
	_set_normal(ray, touch);
	_set_uv(ray, touch);
	shift_point(touch->point, touch->normal);
	return (EXIT_SUCCESS);
}
