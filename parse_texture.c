/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/31 13:53:21 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_texture(char **str, mlx_texture_t **texture)
{
	size_t	i;
	char	*path;

	i = 0;
	if (*texture)
		return (ft_error("Too many texture !", EXIT_FAILURE));
	*str = ft_skip_blank(*str);
	while ((*str)[i] && !ft_isspace((*str)[i]))
		i++;
	path = ft_strndup(*str, i);
	*texture = mlx_load_png(path);
	free(path);
	if (!*texture)
		return (ft_error("Invalid texture !", EXIT_FAILURE));
	(*str) += i;
	return (EXIT_SUCCESS);
}

int	parse_object_texture(char **str, t_object *object)
{
	int	error;

	*str = ft_skip_blank(*str);
	if (**str == '\n')
		error = EXIT_SUCCESS;
	else if (!parse_identifier(str, "T:"))
		error = parse_texture(str, &object->texture);
	else if (!parse_identifier(str, "B:"))
		error = parse_texture(str, &object->bump_map);
	else
		error = ft_error("Unknown texture identifier !", EXIT_FAILURE);
	if (error)
	{
		if (object->bump_map)
			mlx_delete_texture(object->bump_map);
		if (object->texture)
			mlx_delete_texture(object->texture);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
