/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewplane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/15 11:47:32 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_viewplane(t_rt *rt)
{
	rt->viewplane.distance = 1 / (2 * tanf(rt->camera.fov / 2));
	kdm_vec3_crossn(rt->viewplane.x,
		rt->camera.axis, (t_vec3){0.0f, 0.0f, 1.0f});
	kdm_vec3_crossn(rt->viewplane.y, rt->camera.axis, rt->viewplane.x);
}
