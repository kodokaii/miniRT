/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:22:49 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/29 21:04:00 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	_direction(t_vec3 direction, float x, float y, t_rt *rt)
{
	t_vec3	x_vec;
	t_vec3	y_vec;
	t_vec3	z_vec;

	kdm_vec3_scale(x_vec, rt->viewplane.x, x);
	kdm_vec3_scale(y_vec, rt->viewplane.y, y);
	kdm_vec3_scale(z_vec, rt->camera.axis, rt->viewplane.distance);
	kdm_vec3_addv(direction, 3, x_vec, y_vec, z_vec);
}

static void	_sky_color(t_vec3 color, t_touch *touch)
{
	kdm_vec3_lerp(color,
		(t_vec3){0.5f, 0.7f, 1.0f},
		(touch->ray.direction[Z] + 1.0f) / 2,
		(t_vec3){1.0f, 1.0f, 1.0f});
}

static void	_get_color(t_vec3 color, t_touch *touch, t_rt *rt, t_uint iter)
{
	t_vec3	light;	
	t_vec3	color_object;
	t_vec3	reflect_dir;
	t_touch	reflect_touch;

	if (!iter)
		kdm_vec3(color, (t_vec3){0.0f, 0.0f, 0.0f});
	else if (!touch->ray.object)
		_sky_color(color, touch);
	else
	{
		get_light_phong(light, touch, rt);
		kdm_vec3(color_object, touch->ray.object->color);
		if ((int)roundf(touch->uv[X] * 32) % 2 == (int)roundf(touch->uv[Y] * 32) % 2)
			kdm_vec3_sub(color_object, (t_vec3){1.0f, 1.0f, 1.0f}, color_object);
		kdm_vec3_mul(color_object, light, color_object);
		kdm_vec3_reflect(reflect_dir, touch->ray.direction, touch->normal);
		raytracing(touch->point, reflect_dir, &reflect_touch, rt);
		_get_color(color, &reflect_touch, rt, iter - 1);
		kdm_vec3_lerp(color, color,
			touch->ray.object->reflect, color_object);
	}
}

static int	_draw_pixel(float x, float y, t_mlx *mlx)
{
	t_vec3		direction;
	t_touch		touch;
	t_vec3		color;

	_direction(direction, x, y, &mlx->rt);
	raytracing(mlx->rt.camera.pos, direction, &touch, &mlx->rt);
	_get_color(color, &touch, &mlx->rt, 16);
	return (new_pixel(color, 1.0f));
}

void	draw_frame(void *param)
{
	t_mlx	*mlx;

	mlx = param;
	mlx->rt.viewplane.distance = 1 / (2 * tanf(mlx->rt.camera.fov / 2));
	kdm_vec3_crossn(mlx->rt.viewplane.x,
		mlx->rt.camera.axis, (t_vec3){0.0f, 0.0f, 1.0f});
	kdm_vec3_crossn(mlx->rt.viewplane.y,
		mlx->rt.camera.axis, mlx->rt.viewplane.x);
	pixel_iter(mlx->image, mlx, _draw_pixel);
}
