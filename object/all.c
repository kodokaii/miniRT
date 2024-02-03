/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/02/03 11:57:39 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	raytracing(t_vec3 origin, t_vec3 direction, t_hit *hit, t_rt *rt)
{
	static int	(*ray_func[])(t_ray *, t_hit *)
		= {ray_sphere, ray_plane, ray_cylinder, ray_triangle};
	t_hit		current_hit;
	t_list		*current;
	t_ray		ray;

	current = rt->object;
	kdm_vec3_cpy(ray.origin, origin);
	kdm_vec3_normalize_to(ray.direction, direction);
	hit->ray = ray;
	hit->distance = FLT_MAX;
	hit->ray.object = NULL;
	while (current)
	{
		ray.object = current->data;
		if (!ray_func[ray.object->type](&ray, &current_hit))
		{
			if (current_hit.distance <= hit->distance)
				*hit = current_hit;
		}
		current = current->next;
	}
	if (!hit->ray.object)
		return (hit_sky(&ray, hit));
	return (EXIT_SUCCESS);
}
