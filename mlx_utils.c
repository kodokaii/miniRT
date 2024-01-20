/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/20 01:13:15 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_mouse_pos(t_vec2 mouse_pos, t_mlx *mlx)
{
	int	x;
	int	y;

	mlx_get_mouse_pos(mlx->win, &x, &y);
	mouse_pos[X] = (2 * (float)x / (float)mlx->win->width - 1) * mlx->ratio;
	mouse_pos[Y] = (2 * (float)y / (float)mlx->win->height - 1);
}

int	new_pixel(t_vec3 color, float a)
{
	int	pixel;

	pixel = ((int)roundf(kdm_clamp(color[X], 0.0f, 1.0f) * 0xff)) << 24;
	pixel |= ((int)roundf(kdm_clamp(color[Y], 0.0f, 1.0f) * 0xff)) << 16;
	pixel |= ((int)roundf(kdm_clamp(color[Z], 0.0f, 1.0f) * 0xff)) << 8;
	pixel |= ((int)roundf(kdm_clamp(a, 0.0f, 1.0f) * 0xff));
	return (pixel);
}

void	pixel_iter(mlx_image_t *image, t_mlx *mlx,
			int (*f)(float, float, t_mlx *))
{
	int		color;
	t_uint	x;
	t_uint	y;

	x = 0;
	while (x < image->width)
	{
		y = 0;
		while (y < image->height)
		{
			color = (*f)(
					(2 * (float)x / (float)image->width - 1) * mlx->ratio,
					2 * (float)y / (float)image->height - 1,
					mlx);
			mlx_put_pixel(image, x, y, color);
			y++;
		}
		x++;
	}
}
