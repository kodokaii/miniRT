/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/31 14:32:26 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	_sky_color(t_vec3 color, t_touch *touch, t_rt *rt)
{
	t_vec3	sky_color;

	kdm_vec3_lerp(sky_color, rt->sky.color_down,
		touch->uv[Y], rt->sky.color_up);
	if (rt->sky.sky_box)
	{
		texture_pixel(color, touch->uv, rt->sky.sky_box);
		kdm_vec3_mul(color, color, sky_color);
	}
	else
		kdm_vec3_cpy(color, sky_color);
}

static void	_object_color(t_vec3 color, t_touch *touch)
{
	if (touch->ray.object->texture)
	{
		texture_pixel(color, touch->uv, touch->ray.object->texture);
		kdm_vec3_mul(color, color, touch->ray.object->color);
	}
	else
		kdm_vec3_cpy(color, touch->ray.object->color);
}

void	texture_pixel(t_vec3 pixel, t_vec2 uv, mlx_texture_t *texture)
{
	t_uint	x;
	t_uint	y;
	uint8_t	*rgba;

	uv[X] = kdm_clamp(uv[X], 0.0f, 1.0f);
	uv[Y] = kdm_clamp(uv[Y], 0.0f, 1.0f);
	x = (int)floorf(uv[X] * (float)texture->width);
	y = (int)floorf(uv[Y] * (float)texture->height);
	rgba = &texture->pixels[(x + y * texture->width) * 4];
	pixel[X] = (float)rgba[0] / 255.0f;
	pixel[Y] = (float)rgba[1] / 255.0f;
	pixel[Z] = (float)rgba[2] / 255.0f;
}

void	touch_color(t_vec3 color, t_touch *touch, t_rt *rt, t_uint iter)
{
	t_vec3	light;	
	t_vec3	color_object;
	t_vec3	reflect_dir;
	t_touch	reflect_touch;

	if (!iter)
		kdm_vec3(color, (t_vec3){0.0f, 0.0f, 0.0f});
	else if (!touch->ray.object)
		_sky_color(color, touch, rt);
	else
	{
		get_light_phong(light, touch, rt);
		_object_color(color_object, touch);
		kdm_vec3_mul(color_object, light, color_object);
		kdm_vec3_reflect(reflect_dir, touch->ray.direction, touch->normal);
		raytracing(touch->point, reflect_dir, &reflect_touch, rt);
		touch_color(color, &reflect_touch, rt, iter - 1);
		kdm_vec3_lerp(color, color,
			touch->ray.object->reflect, color_object);
	}
}
