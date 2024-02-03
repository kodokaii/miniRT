/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/02/01 17:57:17 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static void	_set_uv(t_ray *ray, t_hit *hit)
{
	t_vec3	delta;

	kdm_vec3_sub(delta, hit->point, ray->object->pos);
	hit->uv[X] = kdm_vec3_dot(delta, ray->object->x) / PLANE_UV_SIZE;
	hit->uv[Y] = kdm_vec3_dot(delta, ray->object->y) / PLANE_UV_SIZE;
	if (hit->uv[X] < 0.0f)
		hit->uv[X] = 1.0f - fmodf(fabsf(hit->uv[X]), 1.0f);
	else
		hit->uv[X] = fmodf(hit->uv[X], 1.0f);
	if (hit->uv[Y] < 0.0f)
		hit->uv[Y] = 1.0f - fmodf(fabsf(hit->uv[Y]), 1.0f);
	else
		hit->uv[Y] = fmodf(hit->uv[Y], 1.0f);
}

static int	_set_distance(t_ray *ray, float x, t_hit *hit)
{
	if (x < 0.0f)
		return (EXIT_FAILURE);
	else
		hit->distance = x;
	if (kdm_vec3_dot(ray->direction, ray->object->z) < 0.0f)
		hit->side = OUTSIDE;
	else
		hit->side = INSIDE;
	return (EXIT_SUCCESS);
}

static void	_get_tbn(t_mat3 tbn, t_ray *ray, t_hit *hit)
{
	kdm_vec3_cpy(tbn[Z], ray->object->z);
	if (hit->side == INSIDE)
		kdm_vec3_negate(tbn[Z]);
	kdm_vec3_normalize(tbn[Z]);
	kdm_vec3_crossn(tbn[X], ray->object->z, tbn[Z]);
	if (!kdm_vec3_dot(tbn[X], tbn[X]))
		kdm_vec3_cpy(tbn[X], (t_vec3){1, 0, 0});
	kdm_vec3_crossn(tbn[Y], tbn[Z], tbn[X]);
}

static void	_set_normal(t_ray *ray, t_hit *hit)
{
	t_vec3	bump;
	t_mat3	tbn;

	_get_tbn(tbn, ray, hit);
	if (hit->ray.object->bump_map)
	{
		texture_pixel(bump, hit->uv, hit->ray.object->bump_map);
		kdm_vec3_scale(bump, bump, 2);
		kdm_vec3_sub(bump, bump, (t_vec3){1.0f, 1.0f, 1.0f});
		kdm_vec3_scale(tbn[X], tbn[X], bump[X]);
		kdm_vec3_scale(tbn[Y], tbn[Y], bump[Y]);
		kdm_vec3_scale(tbn[Z], tbn[Z], bump[Z]);
		kdm_vec3_addv(hit->normal, 3, tbn[X], tbn[Y], tbn[Z]);
		kdm_vec3_normalize(hit->normal);
	}
	else
		kdm_vec3_cpy(hit->normal, tbn[Z]);
}

int	hit_plane(t_ray *ray, float x, t_hit *hit)
{
	hit->ray = *ray;
	if (_set_distance(ray, x, hit))
		return (EXIT_FAILURE);
	get_point(hit->point, ray->origin, ray->direction, hit->distance);
	_set_uv(ray, hit);
	_set_normal(ray, hit);
	shift_point(hit->point, hit->normal);
	return (EXIT_SUCCESS);
}
