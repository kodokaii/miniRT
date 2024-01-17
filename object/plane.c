/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/17 22:44:47 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	normal_plane(t_vec3 normal, t_vec3 point, t_object *object)
{
	(void)point;
	kdm_vec3_cpy(normal, object->data.plane.axis);
}

int	ray_plane(t_vec3 origin, t_vec3 direction, float *d, t_object *object)
{
	float	b;
	float	c;
	t_vec3	diff;

	kdm_vec3_sub(diff, object->data.plane.pos, origin);
	b = kdm_vec3_dot(direction, object->data.plane.axis);
	c = kdm_vec3_dot(diff, object->data.plane.axis);
	if (b == 0.0f)
		return (EXIT_FAILURE);
	*d = c / b;
	if (*d < 0.0f)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
