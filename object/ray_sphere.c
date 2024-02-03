/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/29 21:34:48 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	ray_sphere(t_ray *ray, t_hit *hit)
{
	float	a;
	float	b;
	float	c;
	float	x[2];
	t_vec3	delta;

	kdm_vec3_sub(delta, ray->origin, ray->object->pos);
	a = kdm_vec3_dot(ray->direction, ray->direction);
	b = 2 * kdm_vec3_dot(ray->direction, delta);
	c = kdm_vec3_dot(delta, delta) - kdm_square(ray->object->width / 2);
	if (kdm_quadratic_equation(x, a, b, c))
		return (EXIT_FAILURE);
	if (x[1] < x[0])
		ft_swap_float(x, x + 1);
	return (hit_sphere(ray, x, hit));
}
