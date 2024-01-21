/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/21 13:13:11 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_point(t_vec3 point, t_vec3 origin, t_vec3 direction, float distance)
{
	t_vec3	rayon;

	kdm_vec3_scale(rayon, direction, distance);
	kdm_vec3_add(point, origin, rayon);
}

void	shift_point(t_vec3 point, t_vec3 normal)
{
	t_vec3	shift;

	kdm_vec3_scale(shift, normal, BIAS);
	kdm_vec3_add(point, point, shift);
}
