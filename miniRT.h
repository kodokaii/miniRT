/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/01/20 01:35:26 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "minilibx/mlx42.h"
# include "libft/libft.h"
# include "kdm/kdm.h"

# define WIDTH				512
# define HEIGHT				512

# define INVALID_DISTANCE	-FLT_MAX

# define OBJECT_COUNT		3

# define INVALID_OBJECT		-1
# define SPHERE				0
# define PLANE				1
# define CYLINDER			2

# define SPEED				1.5f
# define SENSITIVITY		0.7f

typedef enum s_side
{
	OUTSIDE,
	INSIDE,
}	t_side;

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
	float	yaw;
	float	pitch;
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
	float	radius;
}	t_sphere;

typedef struct s_plane
{
	t_vec3	pos;
	t_vec3	axis;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3	pos;
	t_vec3	axis;
	float	radius;
	float	height;
}	t_cylinder;

typedef struct s_viewplane
{
	float	distance;
	t_vec3	x;
	t_vec3	y;
}	t_viewplane;

typedef struct s_rt_count
{
	t_uint	ambient;
	t_uint	camera;
	t_uint	light;
	t_uint	object[OBJECT_COUNT];
}	t_rt_count;

typedef union u_object_data
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
}	t_object_data;

typedef struct s_object
{
	int				type;
	t_vec3			color;
	t_object_data	data;
}	t_object;

typedef struct s_rt
{
	t_rt_count	count;
	t_viewplane	viewplane;
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_list		*object;
}	t_rt;

typedef struct s_mlx
{
	mlx_t		*win;
	mlx_image_t	*image;
	t_vec2		mouse_pos;
	float		ratio;
	t_rt		rt;
}	t_mlx;

typedef struct s_ray
{
	t_object	*object;
	t_vec3		origin;
	t_vec3		direction;
}	t_ray;

typedef struct s_touch
{
	t_ray	ray;
	float	distance;
	t_side	side;		
	t_vec3	point;
	t_vec3	normal;
}	t_touch;

typedef struct s_phong
{
	t_vec3	ambient;
	t_vec3	diffuse;
	t_vec3	specular;
	t_touch	touch;
}	t_phong;

int			parse_value(char **str, float *value, float min, float max);
int			parse_vec3(char **str, t_vec3 vec, float min, float max);
int			parse_color(char **str, t_vec3 color_vec);
int			add_object(t_rt *rt, t_object *object);

int			parse_ambient(t_rt *rt, char **line);
int			parse_camera(t_rt *rt, char **line);
int			parse_light(t_rt *rt, char **line);

int			parse_sphere(t_rt *rt, char **line);
int			parse_plane(t_rt *rt, char **line);
int			parse_cylinder(t_rt *rt, char **line);

int			parse_rt(t_rt *rt, char *file);

void		draw_frame(void *param);

void		get_light_phong(t_vec3 light, t_touch *touch, t_rt *rt);

int			ray_sphere(t_ray *ray, t_touch *touch);
int			ray_plane(t_ray *ray, t_touch *touch);
int			ray_cylinder(t_ray *ray, t_touch *touch);
int			raytracing(t_vec3 origin, t_vec3 direction,
				t_touch *touch, t_rt *rt);

void		get_point(t_vec3 point, t_vec3 origin,
				t_vec3 direction, float distance);

void		resize_hook(int width, int heigth, void *param);
void		key_hook(mlx_key_data_t keydata, void *param);
void		move_hook(void *param);

void		rt_cleanup(t_mlx *mlx);

void		get_mouse_pos(t_vec2 mouse_pos, t_mlx *mlx);
int			new_pixel(t_vec3 color, float a);
void		pixel_iter(mlx_image_t *image, t_mlx *mlx,
				int (*f)(float, float, t_mlx *));
#endif
