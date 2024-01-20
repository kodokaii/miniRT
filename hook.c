/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/20 01:33:42 by nlaerema         ###   ########.fr       */
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
}

void	move_camera(t_vec2 mouse_pos, t_mlx *mlx)
{
	t_vec3	right;
	t_vec3	front;
	t_vec3	top;

	mlx->rt.camera.yaw = mlx->rt.camera.yaw
		+ (mlx->mouse_pos[X] - mouse_pos[X]) * SENSITIVITY;
	mlx->rt.camera.pitch = kdm_clamp(mlx->rt.camera.pitch
			+ (mlx->mouse_pos[Y] - mouse_pos[Y]) * SENSITIVITY,
			kdm_rad(-89.99f), kdm_rad(89.99));
	mlx->rt.camera.axis[X] = cosf(mlx->rt.camera.pitch)
		* cosf(mlx->rt.camera.yaw);
	mlx->rt.camera.axis[Y] = cosf(mlx->rt.camera.pitch)
		* sinf(mlx->rt.camera.yaw);
	mlx->rt.camera.axis[Z] = sinf(mlx->rt.camera.pitch);
	kdm_vec3(top, (t_vec3){0.0f, 0.0f, 1.0f});
	kdm_vec3_crossn(right, mlx->rt.camera.axis, top);
	kdm_vec3_crossn(front, top, right);
	kdm_vec3_scale(top, top, SPEED);
	kdm_vec3_scale(right, right, SPEED);
	kdm_vec3_scale(front, front, SPEED);
	if (mlx_is_key_down(mlx->win, MLX_KEY_W))
		kdm_vec3_add(mlx->rt.camera.pos, mlx->rt.camera.pos, front);
	if (mlx_is_key_down(mlx->win, MLX_KEY_S))
		kdm_vec3_sub(mlx->rt.camera.pos, mlx->rt.camera.pos, front);
	if (mlx_is_key_down(mlx->win, MLX_KEY_D))
		kdm_vec3_add(mlx->rt.camera.pos, mlx->rt.camera.pos, right);
	if (mlx_is_key_down(mlx->win, MLX_KEY_A))
		kdm_vec3_sub(mlx->rt.camera.pos, mlx->rt.camera.pos, right);
	if (mlx_is_key_down(mlx->win, MLX_KEY_SPACE))
		kdm_vec3_add(mlx->rt.camera.pos, mlx->rt.camera.pos, top);
	if (mlx_is_key_down(mlx->win, MLX_KEY_LEFT_CONTROL))
		kdm_vec3_sub(mlx->rt.camera.pos, mlx->rt.camera.pos, top);
}

void	move_hook(void *param)
{
	t_mlx	*mlx;
	t_vec2	mouse_pos;

	mlx = param;
	get_mouse_pos(mouse_pos, mlx);
	move_camera(mouse_pos, mlx);
	kdm_vec2_cpy(mlx->mouse_pos, mouse_pos);
}
