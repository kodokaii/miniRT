/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/18 00:29:02 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_bool	is_lighting(t_touch *touch, t_phong *phong, t_rt *rt)
{
	float	distance;
	t_vec3	light_point;
	t_vec3	diff;

	if (raytracing(rt->light.pos, phong->light_dir, &distance, rt)
		!= touch->object)
		return (FT_FALSE);
	get_point(light_point, rt->light.pos, phong->light_dir, distance);
	kdm_vec3_sub(diff, light_point, touch->point);
	if (0.0001f < kdm_vec3_dot(diff, diff))
		return (FT_FALSE);
	return (FT_TRUE);
}

void	get_light_phong(t_vec3 light, t_touch *touch, t_rt *rt)
{
	t_phong	phong;

	kdm_vec3_sub(phong.light_dir, touch->point, rt->light.pos);
	kdm_vec3_scale(phong.ambient, rt->ambient.color, rt->ambient.ratio);
	if (is_lighting(touch, &phong, rt))
	{
		kdm_vec3_scale(phong.diffuse, rt->light.color,
			fmax(-kdm_vec3_dot(touch->normal, phong.light_dir), 0.0f));
		kdm_vec3_one(phong.diffuse);
	}
	else
		kdm_vec3_zero(phong.diffuse);
	kdm_vec3_addv(light, 2, phong.ambient, phong.diffuse);
}
