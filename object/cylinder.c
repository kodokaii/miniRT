/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/21 13:14:27 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static float	_clamp_height(t_ray *ray, float distance)
{
	t_vec3	point;
	t_vec3	diff;
	float	h;

	if (0.0f <= distance)
	{
		get_point(point, ray->origin, ray->direction, distance);
		kdm_vec3_sub(diff, point, ray->object->data.cylinder.pos);
		h = kdm_vec3_dot(diff, ray->object->data.cylinder.axis);
		if (h < 0 || ray->object->data.cylinder.height < h)
			return (INVALID_DISTANCE);
	}
	return (distance);
}

static int	_set_distance(float x[2], t_touch *touch)
{
	if (x[0] < 0.0f && x[1] < 0.0f)
		return (EXIT_FAILURE);
	else if (x[0] < 0.0f)
		touch->distance = x[1];
	else
		touch->distance = x[0];
	if (0.0f < x[0])
		touch->side = OUTSIDE;
	else
		touch->side = INSIDE;
	return (EXIT_SUCCESS);
}

static void	_set_normal(t_ray *ray, t_touch *touch)
{
	t_vec3	hypo;
	t_vec3	height;

	kdm_vec3_sub(hypo, touch->point, ray->object->data.cylinder.pos);
	kdm_vec3_scale(height, ray->object->data.cylinder.axis,
		kdm_vec3_dot(hypo, ray->object->data.cylinder.axis));
	kdm_vec3_sub(touch->normal, hypo, height);
	if (touch->side == INSIDE)
		kdm_vec3_negate(touch->normal);
	kdm_vec3_normalize(touch->normal);
}

static int	_update_touch(t_ray *ray, float x[2], t_touch *touch)
{
	touch->ray = *ray;
	if (_set_distance(x, touch))
		return (EXIT_FAILURE);
	get_point(touch->point, ray->origin, ray->direction, touch->distance);
	_set_normal(ray, touch);
	shift_point(touch->point, touch->normal);
	return (EXIT_SUCCESS);
}

int	ray_cylinder(t_ray *ray, t_touch *touch)
{
	float	a;
	float	b;
	float	c;
	float	x[2];
	t_vec3	diff;

	kdm_vec3_sub(diff, ray->origin, ray->object->data.cylinder.pos);
	a = kdm_vec3_dot(ray->direction, ray->direction)
		- kdm_square(kdm_vec3_dot(ray->direction,
				ray->object->data.cylinder.axis));
	b = 2.0f * (kdm_vec3_dot(ray->direction, diff)
			- kdm_vec3_dot(ray->direction, ray->object->data.cylinder.axis)
			* kdm_vec3_dot(diff, ray->object->data.cylinder.axis));
	c = kdm_vec3_dot(diff, diff)
		- kdm_square(kdm_vec3_dot(diff, ray->object->data.cylinder.axis))
		- kdm_square(ray->object->data.cylinder.radius);
	if (kdm_quadratic_equation(x, a, b, c))
		return (EXIT_FAILURE);
	if (x[1] < x[0])
		ft_swap_float(x, x + 1);
	x[0] = _clamp_height(ray, x[0]);
	x[1] = _clamp_height(ray, x[1]);
	return (_update_touch(ray, x, touch));
}
