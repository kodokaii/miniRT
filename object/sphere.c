/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/17 23:32:32 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	normal_sphere(t_vec3 normal, t_vec3 point, t_object *object)
{
	kdm_vec3_sub(normal, point, object->data.sphere.pos);
}

int	ray_sphere(t_vec3 origin, t_vec3 direction, float *d, t_object *object)
{
	float	a;
	float	b;
	float	c;
	float	x[2];
	t_vec3	diff;

	kdm_vec3_sub(diff, origin, object->data.sphere.pos);
	a = kdm_vec3_dot(direction, direction);
	b = 2 * kdm_vec3_dot(direction, diff);
	c = kdm_vec3_dot(diff, diff) - kdm_square(object->data.sphere.radius);
	if (kdm_quadratic_equation(x, a, b, c) || (x[0] < 0.0f && x[1] < 0.0f))
		return (EXIT_FAILURE);
	if (x[0] < 0.0f)
		*d = x[1];
	else if (x[1] < 0.0f)
		*d = x[0];
	else
		*d = fmin(x[0], x[1]);
	return (EXIT_SUCCESS);
}
