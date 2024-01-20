/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:09:23 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/20 01:01:52 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	_init(t_mlx *mlx)
{
	mlx->win = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!mlx->win)
		return (EXIT_FAILURE);
	mlx->image = mlx_new_image(mlx->win, WIDTH, HEIGHT);
	if (!mlx->image)
		return (EXIT_FAILURE);
	mlx->ratio = WIDTH / HEIGHT;
	if (mlx_image_to_window(mlx->win, mlx->image, 0, 0) == -1)
		return (EXIT_FAILURE);
	get_mouse_pos(mlx->mouse_pos, mlx);
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	static t_mlx	mlx = {};

	if (argc < 2)
		return (ft_error("./miniRT <file.rt>", EXIT_FAILURE));
	if (2 < argc)
		return (ft_error("Too many arguments", EXIT_FAILURE));
	if (parse_rt(&mlx.rt, argv[1]))
		return (rt_cleanup(&mlx), EXIT_FAILURE);
	if (_init(&mlx))
		return (ft_error("Init MLX failed !", EXIT_FAILURE));
	mlx_resize_hook(mlx.win, &resize_hook, &mlx);
	mlx_key_hook(mlx.win, &key_hook, &mlx);
	mlx_loop_hook(mlx.win, &move_hook, &mlx);
	mlx_loop_hook(mlx.win, &draw_frame, &mlx);
	mlx_loop(mlx.win);
	rt_cleanup(&mlx);
}
