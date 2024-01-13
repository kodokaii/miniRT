/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/13 20:48:38 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	rt_cleanup(t_mlx *mlx)
{
	if (mlx->win)
		mlx_terminate(mlx->win);
	ft_lstclear(&mlx->rt.sphere, free);
	ft_lstclear(&mlx->rt.plane, free);
	ft_lstclear(&mlx->rt.cylinder, free);
}
