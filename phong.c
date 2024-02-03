/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/02/01 17:33:21 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	_get_params(t_phong *phong, t_light *light,
			t_hit *hit, t_rt *rt)
{
	phong->distance = kdm_vec3_distance(hit->point, light->pos);
	phong->attenuation = light->ratio / (0.0001f
			+ 0.0001f * phong->distance
			+ 0.0001f * kdm_square(phong->distance));
	kdm_vec3_sub(phong->light_dir, light->pos, hit->point);
	kdm_vec3_sub(phong->view_dir, rt->camera.pos, hit->point);
	kdm_vec3_reflect(phong->reflect_dir, phong->light_dir, hit->normal);
	kdm_vec3_normalize(phong->light_dir);
	kdm_vec3_normalize(phong->view_dir);
	kdm_vec3_normalize(phong->reflect_dir);
	kdm_vec3_zero(phong->ambient);
	kdm_vec3_zero(phong->diffuse);
	kdm_vec3_zero(phong->specular);
}

static void	_get_direct_light(t_vec3 direct_light, t_light *light,
			t_hit *hit, t_rt *rt)
{
	t_phong	phong;

	_get_params(&phong, light, hit, rt);
	if (raytracing(hit->point, phong.light_dir, &phong.hit, rt)
		|| phong.distance < phong.hit.distance)
	{
		phong.diffuse_ratio = kdm_vec3_dot(hit->normal, phong.light_dir);
		kdm_vec3_scale(phong.diffuse, light->color,
			fmaxf(phong.diffuse_ratio, 0.0f));
		phong.specular_ratio = -kdm_vec3_dot(phong.view_dir, phong.reflect_dir);
		kdm_vec3_scale(phong.specular, light->color,
			powf(fmaxf(phong.specular_ratio, 0.0f), 4));
	}
	kdm_vec3_addv(direct_light, 3,
		phong.ambient, phong.diffuse, phong.specular);
	kdm_vec3_cpy(direct_light, phong.diffuse);
	kdm_vec3_scale(direct_light, direct_light, phong.attenuation);
}

void	get_light_phong(t_vec3 all_light, t_hit *hit, t_rt *rt)
{
	t_list	*current;
	t_vec3	direct_light;

	current = rt->light;
	kdm_vec3_scale(all_light, rt->ambient.color, rt->ambient.ratio);
	while (current)
	{
		_get_direct_light(direct_light, current->data, hit, rt);
		kdm_vec3_add(all_light, all_light, direct_light);
		current = current->next;
	}
	all_light[X] = fminf(all_light[X], 1.0f);
	all_light[Y] = fminf(all_light[Y], 1.0f);
	all_light[Z] = fminf(all_light[Z], 1.0f);
}
