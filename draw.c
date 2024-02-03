/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:22:49 by nlaerema          #+#    #+#             */
/*   Updated: 2024/02/02 18:25:53 by nlaerema         ###   ########.fr       */
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

static int	_draw_pixel(float x, float y, t_mlx *mlx)
{
	t_vec3		direction;
	t_hit		hit;
	t_vec3		color;

	_direction(direction, x, y, &mlx->rt);
	raytracing(mlx->rt.camera.pos, direction, &hit, &mlx->rt);
	hit_color(color, &hit, &mlx->rt, 8);
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
