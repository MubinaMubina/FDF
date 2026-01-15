/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:52:28 by mmubina           #+#    #+#             */
/*   Updated: 2026/01/14 18:50:26 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/fdf.h"

// void	draw_line(t_fdf *fdf, t_point p1, t_point p2)
// {
// 	uint32_t	color1;
// 	uint32_t	color2;

// 	color1 = get_height_color(p1.z, fdf->map.z_max, fdf->map.z_min);
// 	color2 = get_height_color(p2.z, fdf->map.z_max, fdf->map.z_min);
// 	draw_bresenham(fdf, p1, p2, color1, color2);
// }

// // not allowed
// void	init_bresenham(int *v, t_point p1, t_point p2, int *xy)
// {
// 	xy[0] = (int)p1.x;
// 	xy[1] = (int)p1.y;
// 	v[0] = abs((int)p2.x - xy[0]);
// 	v[1] = -abs((int)p2.y - xy[1]);
// 	v[2] = (xy[0] < (int)p2.x) ? 1 : -1;
// 	v[3] = (xy[1] < (int)p2.y) ? 1 : -1;
// 	v[4] = v[0] + v[1];
// }

// void	step_bresenham(int *v, int *xy, t_point p2)
// {
// 	v[5] = 2 * v[4];
// 	if (v[5] >= v[1] && xy[0] != (int)p2.x)
// 	{
// 		v[4] += v[1];
// 		xy[0] += v[2];
// 	}
// 	if (v[5] <= v[0] && xy[1] != (int)p2.y)
// 	{
// 		v[4] += v[0];
// 		xy[1] += v[3];
// 	}
// }

// void	draw_bresenham(t_fdf *fdf, t_point p1, t_point p2, uint32_t color1,
// 		uint32_t color2)
// {
// 	int		v[6];
// 	int		xy[2];
// 	float	fraction;

// 	init_bresenham(v, p1, p2, xy);
// 	while (1)
// 	{
// 		if (abs((int)p2.x - (int)p1.x) > abs((int)p2.y - (int)p1.y))
// 			fraction = get_fraction(p1.x, p2.x, xy[0]);
// 		else
// 			fraction = get_fraction(p1.y, p2.y, xy[1]);
// 		put_pixel(fdf->img, xy[0], xy[1], interpolate_color(color1, color2,
// 				fraction));
// 		if (xy[0] == (int)p2.x && xy[1] == (int)p2.y)
// 			break ;
// 		step_bresenham(v, xy, p2);
// 	}
// }

#include "../include/fdf.h"

void	draw_line(t_fdf *fdf, t_point p1, t_point p2)
{
	p1.color = get_height_color(p1.z, fdf->map.z_max, fdf->map.z_min);
	p2.color = get_height_color(p2.z, fdf->map.z_max, fdf->map.z_min);
	draw_bresenham(fdf, p1, p2);
}

void	init_bresenham(int *v, t_point p1, t_point p2, int *xy)
{
	xy[0] = (int)p1.x;
	xy[1] = (int)p1.y;
	v[0] = abs((int)p2.x - xy[0]);
	v[1] = -abs((int)p2.y - xy[1]);
	if (xy[0] < (int)p2.x)
		v[2] = 1;
	else
		v[2] = -1;
	if (xy[1] < (int)p2.y)
		v[3] = 1;
	else
		v[3] = -1;
	v[4] = v[0] + v[1];
}

void	step_bresenham(int *v, int *xy, t_point p2)
{
	v[5] = 2 * v[4];
	if (v[5] >= v[1] && xy[0] != (int)p2.x)
	{
		v[4] += v[1];
		xy[0] += v[2];
	}
	if (v[5] <= v[0] && xy[1] != (int)p2.y)
	{
		v[4] += v[0];
		xy[1] += v[3];
	}
}

void	draw_bresenham(t_fdf *fdf, t_point p1, t_point p2)
{
	int		v[6];
	int		xy[2];
	float	fraction;

	init_bresenham(v, p1, p2, xy);
	while (1)
	{
		if (abs((int)p2.x - (int)p1.x) > abs((int)p2.y - (int)p1.y))
			fraction = get_fraction(p1.x, p2.x, xy[0]);
		else
			fraction = get_fraction(p1.y, p2.y, xy[1]);
		put_pixel(fdf->img, xy[0], xy[1],
			interpolate_color(p1.color, p2.color, fraction));
		if (xy[0] == (int)p2.x && xy[1] == (int)p2.y)
			break ;
		step_bresenham(v, xy, p2);
	}
}
