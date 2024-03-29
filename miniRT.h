/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2024/02/03 18:14:50 by nlaerema         ###   ########.fr       */
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

# define OBJECT_COUNT		4

# define INVALID_OBJECT		-1
# define SPHERE				0
# define PLANE				1
# define CYLINDER			2
# define TRIANGLE			3

# define SPEED				1.5f
# define SENSITIVITY		0.7f

# define BIAS				0.01f
# define PLANE_UV_SIZE		100.0f
# define TRIANGLE_UV_SIZE	50.0f

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

typedef struct s_sky
{
	t_vec3			color_up;
	t_vec3			color_down;
	mlx_texture_t	*sky_box;
}	t_sky;

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
	t_uint	sky;
	t_uint	object[OBJECT_COUNT];
}	t_rt_count;

typedef struct s_object
{
	int				type;
	float			reflect;
	float			width;
	float			height;
	t_vec3			pos;
	t_vec3			vertex1;
	t_vec3			vertex2;
	t_vec3			vertex3;
	t_vec3			x;
	t_vec3			y;
	t_vec3			z;
	t_vec3			color;
	mlx_texture_t	*bump_map;
	mlx_texture_t	*texture;
}	t_object;

typedef struct s_rt
{
	t_rt_count	count;
	t_viewplane	viewplane;
	t_ambient	ambient;
	t_camera	camera;
	t_sky		sky;
	t_list		*light;
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

typedef struct s_hit
{
	t_ray	ray;
	float	distance;
	t_side	side;		
	t_vec3	point;
	t_vec3	normal;
	t_vec2	uv;
}	t_hit;

typedef struct s_phong
{
	float	distance;
	float	attenuation;
	float	ambient_ratio;
	float	diffuse_ratio;
	float	specular_ratio;
	t_vec3	light_dir;
	t_vec3	view_dir;
	t_vec3	reflect_dir;
	t_vec3	ambient;
	t_vec3	diffuse;
	t_vec3	specular;
	t_hit	hit;
}	t_phong;

int			parse_value(char **str, float *value, float min, float max);
int			parse_vec3(char **str, t_vec3 vec, float min, float max);
int			parse_color(char **str, t_vec3 color_vec);
int			parse_identifier(char **line, char *identifier);
int			parse_texture(char **str, mlx_texture_t **texture);
int			parse_object_texture(char **str, t_object *object);
int			parse_material(char **line, t_object *object);

int			parse_ambient(t_rt *rt, char **line);
int			parse_camera(t_rt *rt, char **line);
int			parse_sky(t_rt *rt, char **line);
int			parse_light(t_rt *rt, char **line);

int			parse_sphere(t_rt *rt, char **line);
int			parse_plane(t_rt *rt, char **line);
int			parse_cylinder(t_rt *rt, char **line);
int			parse_triangle(t_rt *rt, char **line);
int			add_object(t_rt *rt, t_object *object);

int			parse_rt(t_rt *rt, char *file);

void		draw_frame(void *param);

void		get_light_phong(t_vec3 light, t_hit *hit, t_rt *rt);
void		texture_pixel(t_vec3 pixel, t_vec2 uv, mlx_texture_t *texture);
void		hit_color(t_vec3 color, t_hit *hit, t_rt *rt, t_uint iter);

void		get_point(t_vec3 point, t_vec3 origin,
				t_vec3 direction, float distance);
void		shift_point(t_vec3 point, t_vec3 normal);

int			ray_sphere(t_ray *ray, t_hit *hit);
int			ray_plane(t_ray *ray, t_hit *hit);
int			ray_cylinder(t_ray *ray, t_hit *hit);
int			ray_triangle(t_ray *ray, t_hit *hit);
int			raytracing(t_vec3 origin, t_vec3 direction,
				t_hit *hit, t_rt *rt);

int			hit_sphere(t_ray *ray, float x[2], t_hit *hit);
int			hit_cylinder(t_ray *ray, float x[2], t_hit *hit);
int			hit_plane(t_ray *ray, float x, t_hit *hit);
int			hit_triangle(t_ray *ray, float x, t_hit *hit);
int			hit_sky(t_ray *ray, t_hit *hit);

void		resize_hook(int width, int heigth, void *param);
void		key_hook(mlx_key_data_t keydata, void *param);
void		move_hook(void *param);

void		rt_cleanup(t_mlx *mlx);

void		get_mouse_pos(t_vec2 mouse_pos, t_mlx *mlx);
int			new_pixel(t_vec3 color, float a);
void		pixel_iter(mlx_image_t *image, t_mlx *mlx,
				int (*f)(float, float, t_mlx *));
#endif
