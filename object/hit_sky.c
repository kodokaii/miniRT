/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sky.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/30 10:19:29 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static void	_set_uv(t_ray *ray, t_hit *hit)
{
	t_vec3	delta;

	kdm_vec3_normalize_to(delta, ray->direction);
	hit->uv[X] = 0.5
		+ (atan2f(delta[Y], delta[X]) / TAU);
	hit->uv[Y] = 0.5 - (asinf(delta[Z]) / PI);
}

static void	_set_normal(t_ray *ray, t_hit *hit)
{
	kdm_vec3_negate_to(hit->normal, ray->direction);
	kdm_vec3_normalize(hit->normal);
}

int	hit_sky(t_ray *ray, t_hit *hit)
{
	ray->object = NULL;
	hit->ray = *ray;
	hit->distance = NAN;
	hit->side = INSIDE;
	kdm_vec3(hit->point, (t_vec3){NAN, NAN, NAN});
	_set_normal(ray, hit);
	_set_uv(ray, hit);
	return (EXIT_FAILURE);
}
