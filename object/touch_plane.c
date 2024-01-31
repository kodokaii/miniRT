/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/31 12:19:01 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static void	_set_uv(t_ray *ray, t_touch *touch)
{
	t_vec3	diff;

	kdm_vec3_sub(diff, touch->point, ray->object->pos);
	touch->uv[X] = kdm_vec3_dot(diff, ray->object->x) / PLANE_UV_SIZE;
	touch->uv[Y] = kdm_vec3_dot(diff, ray->object->y) / PLANE_UV_SIZE;
	if (touch->uv[X] < 0.0f)
		touch->uv[X] = 1.0f - fmodf(fabsf(touch->uv[X]), 1.0f);
	else
		touch->uv[X] = fmodf(touch->uv[X], 1.0f);
	if (touch->uv[Y] < 0.0f)
		touch->uv[Y] = 1.0f - fmodf(fabsf(touch->uv[Y]), 1.0f);
	else
		touch->uv[Y] = fmodf(touch->uv[Y], 1.0f);
}

static int	_set_distance(t_ray *ray, float x, t_touch *touch)
{
	if (x < 0.0f)
		return (EXIT_FAILURE);
	else
		touch->distance = x;
	if (kdm_vec3_dot(ray->direction, ray->object->z) < 0.0f)
		touch->side = OUTSIDE;
	else
		touch->side = INSIDE;
	return (EXIT_SUCCESS);
}

static void	_set_tbn(t_ray *ray, t_touch *touch)
{
	kdm_vec3_cpy(touch->normal, ray->object->z);
	if (touch->side == INSIDE)
		kdm_vec3_negate(touch->normal);
	kdm_vec3_normalize(touch->normal);
	kdm_vec3_crossn(touch->tangent, ray->object->z, touch->normal);
	if (!kdm_vec3_dot(touch->tangent, touch->tangent))
		kdm_vec3_cpy(touch->tangent, ray->object->y);
	kdm_vec3_crossn(touch->bitangent, touch->normal, touch->tangent);
}

int	touch_plane(t_ray *ray, float x, t_touch *touch)
{
	touch->ray = *ray;
	if (_set_distance(ray, x, touch))
		return (EXIT_FAILURE);
	get_point(touch->point, ray->origin, ray->direction, touch->distance);
	_set_tbn(ray, touch);
	_set_uv(ray, touch);
	shift_point(touch->point, touch->normal);
	return (EXIT_SUCCESS);
}
