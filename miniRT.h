/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/13 22:45:56 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "minilibx/mlx42.h"
# include "libft/libft.h"
# include "kdm/kdm.h"

# define FT_WIDTH		1080
# define FT_HEIGHT		1080

typedef struct s_ambient
{
	float	ratio;
	t_vec3	color;
}	t_ambient;

typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	axis;
	float	fov;
}	t_camera;

typedef struct s_light
{
	t_vec3	pos;
	float	ratio;
	t_vec3	color;
}	t_light;

typedef struct s_sphere
{
	t_vec3	pos;
	float	diameter;
	t_vec3	color;
}	t_sphere;

typedef struct s_plane
{
	t_vec3	pos;
	t_vec3	axis;
	t_vec3	color;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3	pos;
	t_vec3	axis;
	float	diameter;
	float	height;
	t_vec3	color;
}	t_cylinder;

typedef struct s_viewplane
{
	t_vec3	pos;
	t_vec3	x;
	t_vec3	y;
}	t_viewplane;

typedef struct s_rt_count
{
	t_uint	ambient;
	t_uint	camera;
	t_uint	light;
	t_uint	sphere;
	t_uint	plane;
	t_uint	cylinder;
}	t_rt_count;

typedef struct s_rt
{
	t_rt_count	count;
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_list		*sphere;
	t_list		*plane;
	t_list		*cylinder;
}	t_rt;

typedef struct s_mlx
{
	mlx_t		*win;
	mlx_image_t	*image;
	t_rt		rt;
}	t_mlx;

int		parse_value(char **str, float *value, float min, float max);
int		parse_vec3(char **str, t_vec3 vec, float min, float max);
int		parse_color(char **str, t_vec3 color_vec);

int		parse_ambient(t_rt *rt, char **line);
int		parse_camera(t_rt *rt, char **line);
int		parse_light(t_rt *rt, char **line);

int		parse_sphere(t_rt *rt, char **line);
int		parse_plane(t_rt *rt, char **line);
int		parse_cylinder(t_rt *rt, char **line);

int		parse_rt(t_rt *rt, char *file);

void	ft_draw(void *param);

void	ft_resize_hook(int width, int heigth, void *param);
void	ft_scroll_hook(double xdelta, double ydelta, void *param);
void	ft_key_hook(mlx_key_data_t keydata, void *param);

void	rt_cleanup(t_mlx *mlx);

int		ft_pixel(float r, float g, float b, float a);
void	ft_pixel_iter(mlx_image_t *image, t_mlx *mlx,
			int (*f)(float, float, t_mlx *));
#endif
