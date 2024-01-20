/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/20 02:35:52 by nlaerema         ###   ########.fr       */
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
	kdm_vec3_normalize(direction);
}

static void	_get_color(t_vec3 color, t_touch *touch, t_rt *rt, t_uint iter)
{
	t_vec3	light;	
	t_vec3	color_object;
	t_vec3	reflect_point;
	t_vec3	reflect_dir;
	t_touch	reflect_touch;

	if (iter)
	{
		get_light_phong(light, touch, rt);
		kdm_vec3_mul(color_object, light, touch->ray.object->color);
		if (touch->ray.object->type == SPHERE)
		{
			kdm_vec3_scale(reflect_point, touch->normal, 0.001f);
			kdm_vec3_add(reflect_point, reflect_point, touch->point);
			kdm_vec3_reflect(reflect_dir, touch->ray.direction, touch->normal);
			if (!raytracing(reflect_point, reflect_dir, &reflect_touch, rt))
			{
				_get_color(color, &reflect_touch, rt, iter - 1);
				kdm_vec3_lerp(color, color_object, 0.8f, color);
			}
		}
		else
			kdm_vec3_cpy(color, color_object);
	}
}

static int	_draw_pixel(float x, float y, t_mlx *mlx)
{
	t_vec3		direction;
	t_touch		touch;
	t_vec3		color;

	_direction(direction, x, y, &mlx->rt);
	if (!raytracing(mlx->rt.camera.pos, direction, &touch, &mlx->rt))
	{
		kdm_vec3(color, (t_vec3){0.0f, 0.0f, 0.0f});
		_get_color(color, &touch, &mlx->rt, 10);
		return (new_pixel(color, 1.0f));
	}
	else
		return (0X000000FF);
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
