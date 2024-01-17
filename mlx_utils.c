/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/16 15:25:44 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	new_pixel(float r, float g, float b, float a)
{
	int	color;

	color = ((int)roundf(fmin(r, 1.0f) * 0xff)) << 24;
	color |= ((int)roundf(fmin(g, 1.0f) * 0xff)) << 16;
	color |= ((int)roundf(fmin(b, 1.0f) * 0xff)) << 8;
	color |= (int)roundf(fmin(a, 1.0f) * 0xff);
	return (color);
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
