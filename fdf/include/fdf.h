/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 18:21:13 by mmubina           #+#    #+#             */
/*   Updated: 2026/01/14 19:18:23 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "MLX42.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

/* Projection Types */
# define ISOMETRIC 0
# define PARALLEL 1

typedef struct s_point
{
	float		x;
	float		y;
	float		z;
	uint32_t color; // The missing field
}				t_point;

typedef struct s_map
{
	int			width;
	int			height;
	t_point		**points;
	float		z_min;
	float		z_max;
}				t_map;

typedef struct s_cam
{
	float		zoom;
	double		angle_x;
	double		angle_y;
	double		angle_z;
	float		z_scale;
	int			offset_x;
	int			offset_y;
	int			type;
}				t_cam;

typedef struct s_fdf
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_map		map;
	t_cam		cam;
}				t_fdf;

char			**ft_split(char const *s, char c);
int				ft_atoi(const char *str);
void			*ft_memset(void *b, int c, size_t len);
void			ft_putendl_fd(char *s, int fd);

int				count_width(char *line);
int				count_height(const char *filename);
t_point			*parse_line(char *line, int y, int width);
void			free_map(t_map *map);
void			draw_map(t_fdf *fdf);
void			draw_line(t_fdf *fdf, t_point p1, t_point p2);
void			draw_bresenham(t_fdf *fdf, t_point p1, t_point p2);
void			put_pixel(mlx_image_t *img, int x, int y, uint32_t color);
uint32_t		get_height_color(float z, float z_max, float z_min);
float			get_fraction(float x1, float x2, float x);
uint32_t		interpolate_color(uint32_t color_a, uint32_t color_b,
					float fraction);
t_point			project_point(t_point p, t_fdf *fdf);
void			key_hook(mlx_key_data_t keydata, void *param);
void			scroll_hook(double xdelta, double ydelta, void *param);
char			**ft_split(char const *s, char c);
int				ft_atoi(const char *str);
void			*ft_memset(void *b, int c, size_t len);
void			ft_putendl_fd(char *s, int fd);
void			init_z_minmax(t_map *map);
void			free_split_safe(char **split);
void			resize_hook(int32_t width, int32_t height, void *param);
void			set_view(t_fdf *f, double x, double y, double z, int type);
void			isometric(float *x, float *y, float z);
uint32_t		lerp_color(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2,
					uint8_t g2, uint8_t b2, float t);
void			init_bresenham(int *v, t_point p1, t_point p2, int *xy);
void			step_bresenham(int *v, int *xy, t_point p2);
int				open_and_allocate(const char *filename, t_map *map);
void			read_map_lines(int fd, t_map *map);
t_map			parse_map(const char *filename);
uint32_t		get_rgba(int r, int g, int b, int a);

#endif