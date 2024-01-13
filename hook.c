/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/13 22:10:33 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_resize_hook(int width, int heigth, void *param)
{
	t_mlx	*mlx;

	mlx = param;
}

void	ft_scroll_hook(double xdelta, double ydelta, void *param)
{
	int		mouse_pos[2];
	t_mlx	*mlx;

	(void)xdelta;
	mlx = param;
	mlx_get_mouse_pos(mlx->win, mouse_pos, mouse_pos + 1);
}

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_mlx	*mlx;

	mlx = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(mlx->win);
}
