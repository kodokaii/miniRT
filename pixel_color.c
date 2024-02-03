/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:27:46 by nlaerema          #+#    #+#             */
/*   Updated: 2024/02/03 11:09:58 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	_sky_color(t_vec3 color, t_hit *hit, t_rt *rt)
{
	t_vec3	sky_color;

	kdm_vec3_lerp(sky_color, rt->sky.color_down,
		hit->uv[Y], rt->sky.color_up);
	if (rt->sky.sky_box)
	{
		texture_pixel(color, hit->uv, rt->sky.sky_box);
		kdm_vec3_mul(color, color, sky_color);
	}
	else
		kdm_vec3_cpy(color, sky_color);
}

static void	_object_color(t_vec3 color, t_hit *hit, t_rt *rt)
{
	t_vec3	light;	

	if (hit->ray.object->texture)
	{
		texture_pixel(color, hit->uv, hit->ray.object->texture);
		kdm_vec3_mul(color, color, hit->ray.object->color);
	}
	else
		kdm_vec3_cpy(color, hit->ray.object->color);
	get_light_phong(light, hit, rt);
	kdm_vec3_mul(color, light, color);
	kdm_vec3_scale(color, color, 1 - hit->ray.object->reflect);
}

static void	_reflect_color(t_vec3 color, t_hit *hit, t_rt *rt, t_uint iter)
{
	t_vec3	reflect_dir;
	t_hit	reflect_hit;

	if (!iter || !hit->ray.object->reflect)
		kdm_vec3_cpy(color, (t_vec3){0.0f, 0.0f, 0.0f});
	else
	{
		kdm_vec3_reflect(reflect_dir, hit->ray.direction, hit->normal);
		raytracing(hit->point, reflect_dir, &reflect_hit, rt);
		hit_color(color, &reflect_hit, rt, iter - 1);
		kdm_vec3_scale(color, color, hit->ray.object->reflect);
	}
}

void	texture_pixel(t_vec3 pixel, t_vec2 uv, mlx_texture_t *texture)
{
	t_uint	x;
	t_uint	y;
	uint8_t	*rgba;

	uv[X] = kdm_clamp(uv[X], 0.0f, 1.0f);
	uv[Y] = kdm_clamp(uv[Y], 0.0f, 1.0f);
	x = (int)floorf(uv[X] * (float)(texture->width - 1));
	y = (int)floorf(uv[Y] * (float)(texture->height - 1));
	rgba = &texture->pixels[(x + y * texture->width) * 4];
	pixel[X] = (float)rgba[0] / 255.0f;
	pixel[Y] = (float)rgba[1] / 255.0f;
	pixel[Z] = (float)rgba[2] / 255.0f;
}

void	hit_color(t_vec3 color, t_hit *hit, t_rt *rt, t_uint iter)
{
	t_vec3	color_object;
	t_vec3	reflect_color;

	if (!hit->ray.object)
		_sky_color(color, hit, rt);
	else
	{
		_object_color(color_object, hit, rt);
		_reflect_color(reflect_color, hit, rt, iter);
		kdm_vec3_add(color, color_object, reflect_color);
	}
}
