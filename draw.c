/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/19 22:41:53 by nlaerema         ###   ########.fr       */
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

static int	_get_color(t_touch *touch, t_rt *rt)
{
	t_vec3	light;	
	t_vec3	color;

	get_light_phong(light, touch, rt);
	kdm_vec3_mul(color, light, touch->ray.object->color);
	return (new_pixel(color, 1.0f));
}

static int	_draw_pixel(float x, float y, t_mlx *mlx)
{
	t_vec3		direction;
	t_touch		touch;

	_direction(direction, x, y, &mlx->rt);
	if (!raytracing(mlx->rt.camera.pos, direction, &touch, &mlx->rt))
		return (_get_color(&touch, &mlx->rt));
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
