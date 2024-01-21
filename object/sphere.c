/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/21 13:14:08 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

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
	kdm_vec3_sub(touch->normal, touch->point, ray->object->data.sphere.pos);
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

int	ray_sphere(t_ray *ray, t_touch *touch)
{
	float	a;
	float	b;
	float	c;
	float	x[2];
	t_vec3	diff;

	kdm_vec3_sub(diff, ray->origin, ray->object->data.sphere.pos);
	a = kdm_vec3_dot(ray->direction, ray->direction);
	b = 2 * kdm_vec3_dot(ray->direction, diff);
	c = kdm_vec3_dot(diff, diff) - kdm_square(ray->object->data.sphere.radius);
	if (kdm_quadratic_equation(x, a, b, c))
		return (EXIT_FAILURE);
	if (x[1] < x[0])
		ft_swap_float(x, x + 1);
	return (_update_touch(ray, x, touch));
}
