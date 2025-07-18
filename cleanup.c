/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/31 13:58:24 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	_free_object(t_object *object)
{
	if (object->bump_map)
		mlx_delete_texture(object->bump_map);
	if (object->texture)
		mlx_delete_texture(object->texture);
	free(object);
}

void	rt_cleanup(t_mlx *mlx)
{
	if (mlx->win)
		mlx_terminate(mlx->win);
	if (mlx->rt.sky.sky_box)
		mlx_delete_texture(mlx->rt.sky.sky_box);
	ft_lstclear(&mlx->rt.light, free);
	ft_lstclear(&mlx->rt.object, (void (*)(void *))_free_object);
}
