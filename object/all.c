/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/31 11:54:51 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	raytracing(t_vec3 origin, t_vec3 direction, t_touch *touch, t_rt *rt)
{
	static int	(*ray_func[])(t_ray *, t_touch *)
		= {ray_sphere, ray_plane, ray_cylinder};
	t_touch		current_touch;
	t_list		*current;
	t_ray		ray;

	current = rt->object;
	kdm_vec3_cpy(ray.origin, origin);
	kdm_vec3_normalize_to(ray.direction, direction);
	touch->ray = ray;
	touch->distance = FLT_MAX;
	touch->ray.object = NULL;
	while (current)
	{
		ray.object = current->data;
		if (!ray_func[ray.object->type](&ray, &current_touch))
		{
			if (current_touch.distance <= touch->distance)
				*touch = current_touch;
		}
		current = current->next;
	}
	if (!touch->ray.object)
		return (touch_sky(&ray, touch));
	return (EXIT_SUCCESS);
}
