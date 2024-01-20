/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/18 15:44:58 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

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

static int	_update_touch(t_ray *ray, float x, t_touch *touch)
{
	touch->ray = *ray;
	if (_set_distance(ray, x, touch))
		return (EXIT_FAILURE);
	get_point(touch->point, ray->origin, ray->direction, touch->distance);
	_set_normal(ray, touch);
	return (EXIT_SUCCESS);
}

int	ray_plane(t_ray *ray, t_touch *touch)
{
	float	b;
	float	c;
	float	x;
	t_vec3	diff;

	kdm_vec3_sub(diff, ray->object->data.plane.pos, ray->origin);
	b = kdm_vec3_dot(ray->direction, ray->object->data.plane.axis);
	c = kdm_vec3_dot(diff, ray->object->data.plane.axis);
	if (b == 0.0f)
		return (EXIT_FAILURE);
	x = c / b;
	return (_update_touch(ray, x, touch));
}
