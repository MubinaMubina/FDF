/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 18:21:13 by mmubina           #+#    #+#             */
/*   Updated: 2026/01/04 11:52:58 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define _USE_MATH_DEFINES
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# include "MLX42.h"
# include "get_next_line.h"

# define WIN_WIDTH 1080
# define WIN_HEIGHT 720

typedef struct s_point
{
	float		x;
	float		y;
	float		z;
}				t_point;

typedef struct s_map
{
	t_point		**points;
	int			width;
	int			height;
	float		z_max;
	float		z_min;
}				t_map;

typedef struct s_cam
{
	float		zoom;
	float		offset_x;
	float		offset_y;
	float		angle_x;
	float		angle_y;
	float		angle_z;
}				t_cam;

typedef struct s_fdf
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_map		map;
	t_cam		cam;
}				t_fdf;

t_map			parse_map(const char *filename);
int				count_width(char *line);
int				count_height(const char *filename);
t_point			*parse_line(char *line, int y, int width);
void			free_map(t_map *map);
void			draw_map(t_fdf *fdf);
void			draw_line(t_fdf *fdf, t_point p1, t_point p2);
void			draw_bresenham(t_fdf *fdf, int x0, int y0, int x1, int y1);
void			put_pixel(mlx_image_t *img, int x, int y, uint32_t color);
uint32_t		get_height_color(float z, float z_max, float z_min);
t_point			isometric_projection(t_point p);
t_point			scale_point(t_point p, float zoom);
t_point			translate_point(t_point p, float tx, float ty);
void			key_hook(mlx_key_data_t keydata, void *param);
void			scroll_hook(double xdelta, double ydelta, void *param);
void			close_hook(void *param);
char			**ft_split(char const *s, char c);
int				ft_atoi(const char *str);
void			*ft_memset(void *b, int c, size_t len);
void			ft_putendl_fd(char *s, int fd);
void			init_z_minmax(t_map *map);
void			free_split_safe(char **split);

#endif