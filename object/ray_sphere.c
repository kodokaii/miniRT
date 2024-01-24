/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/23 12:43:39 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	ray_sphere(t_ray *ray, t_touch *touch)
{
	float	a;
	float	b;
	float	c;
	float	x[2];
	t_vec3	diff;

	kdm_vec3_sub(diff, ray->origin, ray->object->data.sphere.pos);
	a = kdm_vec3_dot(ray->direction, ray->direction);
	b = 2 * kdm_vec3_dot(ray->direction, diff);
	c = kdm_vec3_dot(diff, diff) - kdm_square(ray->object->data.sphere.radius);
	if (kdm_quadratic_equation(x, a, b, c))
		return (EXIT_FAILURE);
	if (x[1] < x[0])
		ft_swap_float(x, x + 1);
	return (touch_sphere(ray, x, touch));
}
