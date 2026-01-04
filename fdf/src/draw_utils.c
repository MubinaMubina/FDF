/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 07:47:13 by mmubina           #+#    #+#             */
/*   Updated: 2026/01/04 08:03:38 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	if (x < 0 || x >= (int)img->width || y < 0 || y >= (int)img->height)
		return ;
	mlx_put_pixel(img, x, y, color);
}

uint32_t	get_height_color(float z, float z_max, float z_min)
{
	float	ratio;
	uint8_t	r;
	uint8_t	g;

	if (z_max == z_min)
		ratio = 0.5f;
	else
		ratio = (z - z_min) / (z_max - z_min);
	r = (uint8_t)(255 * ratio);
	g = (uint8_t)(255 * (1.0f - ratio));
	return ((r << 24) | (g << 16) | (100 << 8) | 0xFF);
}

void	draw_line(t_fdf *fdf, t_point p1, t_point p2)
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;

	x0 = (int)p1.x;
	y0 = (int)p1.y;
	x1 = (int)p2.x;
	y1 = (int)p2.y;
	draw_bresenham(fdf, x0, y0, x1, y1);
}

void	draw_bresenham(t_fdf *fdf, int x0, int y0, int x1, int y1)
{
	int dx;
	int dy;
	int sx;
	int sy;
	int err;

	dx = (x1 - x0 < 0) ? -(x1 - x0) : (x1 - x0);
	dy = (y1 - y0 < 0) ? -(y1 - y0) : (y1 - y0);
	sx = (x0 < x1) ? 1 : -1;
	sy = (y0 < y1) ? 1 : -1;
	err = dx - dy;
	while (1)
	{
		put_pixel(fdf->img, x0, y0, 0xFFFFFFFF);
		if (x0 == x1 && y0 == y1)
			break ;
		if (2 * err > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (2 * err < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}