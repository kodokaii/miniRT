/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_sky.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/30 10:19:29 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static void	_set_uv(t_ray *ray, t_touch *touch)
{
	t_vec3	diff;

	kdm_vec3_normalize_to(diff, ray->direction);
	touch->uv[X] = 0.5
		+ (atan2f(diff[Y], diff[X]) / TAU);
	touch->uv[Y] = 0.5 - (asinf(diff[Z]) / PI);
}

static void	_set_normal(t_ray *ray, t_touch *touch)
{
	kdm_vec3_negate_to(touch->normal, ray->direction);
	kdm_vec3_normalize(touch->normal);
}

int	touch_sky(t_ray *ray, t_touch *touch)
{
	ray->object = NULL;
	touch->ray = *ray;
	touch->distance = NAN;
	touch->side = INSIDE;
	kdm_vec3(touch->point, (t_vec3){NAN, NAN, NAN});
	_set_normal(ray, touch);
	_set_uv(ray, touch);
	return (EXIT_FAILURE);
}
