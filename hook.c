/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/18 00:25:49 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	resize_hook(int width, int heigth, void *param)
{
	t_mlx	*mlx;

	mlx = param;
	mlx->ratio = (float)width / (float)heigth;
	mlx_resize_image(mlx->image, width, heigth);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_mlx	*mlx;

	mlx = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(mlx->win);
	if (keydata.key == MLX_KEY_RIGHT)
		mlx->rt.camera.pos[X] += 1;
	if (keydata.key == MLX_KEY_LEFT)
		mlx->rt.camera.pos[X] += -1;
	if (keydata.key == MLX_KEY_UP)
		mlx->rt.camera.pos[Y] += 1;
	if (keydata.key == MLX_KEY_DOWN)
		mlx->rt.camera.pos[Y] += -1;
	if (keydata.key == MLX_KEY_SPACE)
		mlx->rt.camera.pos[Z] += 1;
	if (keydata.key == MLX_KEY_LEFT_SHIFT)
		mlx->rt.camera.pos[Z] += -1;
}
