/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/29 21:34:19 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	ray_plane(t_ray *ray, t_touch *touch)
{
	float	b;
	float	c;
	float	x;
	t_vec3	diff;

	kdm_vec3_sub(diff, ray->object->pos, ray->origin);
	b = kdm_vec3_dot(ray->direction, ray->object->z);
	c = kdm_vec3_dot(diff, ray->object->z);
	if (b == 0.0f)
		return (EXIT_FAILURE);
	x = c / b;
	return (touch_plane(ray, x, touch));
}
