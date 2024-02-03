/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/29 21:33:48 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static float	_clamp_height(t_ray *ray, float distance)
{
	t_vec3	point;
	t_vec3	delta;
	float	h;

	if (0.0f <= distance)
	{
		get_point(point, ray->origin, ray->direction, distance);
		kdm_vec3_sub(delta, point, ray->object->pos);
		h = kdm_vec3_dot(delta, ray->object->z);
		if (h < 0 || ray->object->height < h)
			return (INVALID_DISTANCE);
	}
	return (distance);
}

int	ray_cylinder(t_ray *ray, t_hit *hit)
{
	float	a;
	float	b;
	float	c;
	float	x[2];
	t_vec3	delta;

	kdm_vec3_sub(delta, ray->origin, ray->object->pos);
	a = kdm_vec3_dot(ray->direction, ray->direction)
		- kdm_square(kdm_vec3_dot(ray->direction, ray->object->z));
	b = 2.0f * (kdm_vec3_dot(ray->direction, delta)
			- kdm_vec3_dot(ray->direction, ray->object->z)
			* kdm_vec3_dot(delta, ray->object->z));
	c = kdm_vec3_dot(delta, delta)
		- kdm_square(kdm_vec3_dot(delta, ray->object->z))
		- kdm_square(ray->object->width / 2);
	if (kdm_quadratic_equation(x, a, b, c))
		return (EXIT_FAILURE);
	if (x[1] < x[0])
		ft_swap_float(x, x + 1);
	x[0] = _clamp_height(ray, x[0]);
	x[1] = _clamp_height(ray, x[1]);
	return (hit_cylinder(ray, x, hit));
}
