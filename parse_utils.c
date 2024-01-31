/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/31 11:36:28 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_value(char **str, float *value, float min, float max)
{
	char	*end;

	*value = ft_strtof(*str, &end);
	if (end == *str)
		return (ft_error("Missing value !", EXIT_FAILURE));
	if (!ft_isspace(*end) && *end != ',')
		return (ft_error("Invalid value syntax !", EXIT_FAILURE));
	if (*value < min || max < *value)
		return (ft_error("Value out of range !", EXIT_FAILURE));
	*str = end;
	return (EXIT_SUCCESS);
}

int	parse_vec3(char **str, t_vec3 vec, float min, float max)
{
	if (parse_value(str, vec + X, min, max))
		return (EXIT_FAILURE);
	*str = ft_skip_blank(*str);
	if (**str != ',')
		return (ft_error("Missing comma !", EXIT_FAILURE));
	(*str)++;
	if (parse_value(str, vec + Y, min, max))
		return (EXIT_FAILURE);
	*str = ft_skip_blank(*str);
	if (**str != ',')
		return (ft_error("Missing comma !", EXIT_FAILURE));
	(*str)++;
	if (parse_value(str, vec + Z, min, max))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parse_color(char **str, t_vec3 color)
{
	if (parse_vec3(str, color, 0.0f, 255.0f))
		return (EXIT_FAILURE);
	color[X] /= 255.0f;
	color[Y] /= 255.0f;
	color[Z] /= 255.0f;
	return (EXIT_SUCCESS);
}

int	parse_identifier(char **line, char *identifier)
{
	size_t	i;

	i = 0;
	while ((*line)[i] && (*line)[i] == identifier[i])
		i++;
	if (!ft_isspace((*line)[i]))
		return (EXIT_FAILURE);
	(*line) += i;
	return (EXIT_SUCCESS);
}

int	add_object(t_rt *rt, t_object *object)
{
	t_list	*new_object;

	if (object->type == INVALID_OBJECT)
		return (EXIT_FAILURE);
	new_object = ft_lstnew(ft_memdup(object, sizeof(t_object)));
	ft_lstadd_front(&rt->object, new_object);
	rt->count.object[object->type]++;
	return (EXIT_SUCCESS);
}
