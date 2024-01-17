/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/17 22:50:55 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	normal_object(t_vec3 normal, t_vec3 point, t_object *object)
{
	static void	(*normal_func[])(t_vec3, t_vec3, t_object*)
		= {normal_sphere, normal_plane, normal_cylinder};

	normal_func[object->type](normal, point, object);
}

t_object	*raytracing(t_vec3 origin, t_vec3 direction, float *d, t_rt *rt)
{
	static int	(*ray_func[])(t_vec3, t_vec3, float*, t_object*)
		= {ray_sphere, ray_plane, ray_cylinder};
	t_list		*current;
	float		distance;
	t_object	*object;
	t_object	*best_object;

	*d = FLT_MAX;
	best_object = NULL;
	current = rt->object;
	while (current)
	{
		object = current->data;
		if (!ray_func[object->type](origin, direction, &distance, object))
		{
			if (distance <= *d)
			{
				*d = distance;
				best_object = object;
			}
		}
		current = current->next;
	}
	return (best_object);
}
