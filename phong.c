/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/20 02:39:26 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_bool	is_lighting(t_touch *touch, t_phong *phong, t_rt *rt)
{
	t_vec3	direction;

	kdm_vec3_sub(direction, touch->point, rt->light.pos);
	kdm_vec3_normalize(direction);
	if (raytracing(rt->light.pos, direction, &phong->touch, rt))
		return (FT_FALSE);
	if (phong->touch.ray.object != touch->ray.object
		|| phong->touch.side != touch->side)
		return (FT_FALSE);
	return (FT_TRUE);
}

void	get_light_phong(t_vec3 light, t_touch *touch, t_rt *rt)
{
	t_phong	phong;

	kdm_vec3_scale(phong.ambient, rt->ambient.color, rt->ambient.ratio);
	if (is_lighting(touch, &phong, rt))
	{
		kdm_vec3_scale(phong.diffuse, rt->light.color, fmax(
				-kdm_vec3_dot(touch->normal, phong.touch.ray.direction), 0.0f));
		kdm_vec3_scale(phong.diffuse, phong.diffuse, rt->light.ratio
			/ (0.0001f + 0.0001f * phong.touch.distance + 0.0001f
				* kdm_square(phong.touch.distance)));
	}
	else
		kdm_vec3_zero(phong.diffuse);
	kdm_vec3_addv(light, 2, phong.ambient, phong.diffuse);
}
