/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_triangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/02/03 13:22:44 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static float	_clamp_edge(t_ray *ray, float distance, t_vec3 from, t_vec3 to)
{
	t_vec3	point;
	t_vec3	point_edge;
	t_vec3	triangle_edge;
	t_vec3	cross;
	float	angle;

	if (0.0f <= distance)
	{
		get_point(point, ray->origin, ray->direction, distance);
		kdm_vec3_sub(triangle_edge, to, from);
		kdm_vec3_sub(point_edge, point, from);
		kdm_vec3_cross(cross, triangle_edge, point_edge);
		angle = kdm_vec3_dot(ray->object->z, cross);
		if (angle < 0)
			return (INVALID_DISTANCE);
	}
	return (distance);
}

int	ray_triangle(t_ray *ray, t_hit *hit)
{
	float	b;
	float	c;
	float	x;
	t_vec3	delta;

	kdm_vec3_sub(delta, ray->object->pos, ray->origin);
	b = kdm_vec3_dot(ray->direction, ray->object->z);
	c = kdm_vec3_dot(delta, ray->object->z);
	if (b == 0.0f)
		return (EXIT_FAILURE);
	x = c / b;
	x = _clamp_edge(ray, x, ray->object->vertex1, ray->object->vertex2);
	x = _clamp_edge(ray, x, ray->object->vertex2, ray->object->vertex3);
	x = _clamp_edge(ray, x, ray->object->vertex3, ray->object->vertex1);
	return (hit_triangle(ray, x, hit));
}
