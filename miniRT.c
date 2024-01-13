/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:09:23 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/13 22:32:25 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_draw(void *param)
{
	t_mlx		*mlx;

	mlx = param;
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
	rt_cleanup(&mlx);
}
