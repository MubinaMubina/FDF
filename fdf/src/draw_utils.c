/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 07:47:13 by mmubina           #+#    #+#             */
/*   Updated: 2026/01/04 16:59:38 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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
	uint32_t	color;

	color = get_height_color(p1.z, fdf->map.z_max, fdf->map.z_min);
	draw_bresenham(fdf, p1, p2, color);
}

/* ** We use an array for variables to stay under the 5-variable Norm limit.
** v[0] = dx, v[1] = dy, v[2] = sx, v[3] = sy, v[4] = err, v[5] = e2
*/
void	draw_bresenham(t_fdf *fdf, t_point p1, t_point p2, uint32_t color)
{
	int	v[6];
	int	cur_x;
	int	cur_y;

	cur_x = (int)p1.x;
	cur_y = (int)p1.y;
	v[0] = abs((int)p2.x - cur_x);
	v[1] = -abs((int)p2.y - cur_y);
	v[2] = -1;
	if (cur_x < (int)p2.x)
		v[2] = 1;
	v[3] = -1;
	if (cur_y < (int)p2.y)
		v[3] = 1;
	v[4] = v[0] + v[1];
	while (1)
	{
		put_pixel(fdf->img, cur_x, cur_y, color);
		if (cur_x == (int)p2.x && cur_y == (int)p2.y)
			break ;
		v[5] = 2 * v[4];
		if (v[5] >= v[1] && cur_x != (int)p2.x)
		{
			v[4] += v[1];
			cur_x += v[2];
		}
		if (v[5] <= v[0] && cur_y != (int)p2.y)
		{
			v[4] += v[0];
			cur_y += v[3];
		}
	}
}
