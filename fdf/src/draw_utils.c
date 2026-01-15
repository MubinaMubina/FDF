/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 07:47:13 by mmubina           #+#    #+#             */
/*   Updated: 2026/01/14 18:58:08 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/fdf.h"

// void	put_pixel(mlx_image_t *img, int x, int y, uint32_t color)
// {
// 	if (x < 0 || x >= (int)img->width || y < 0 || y >= (int)img->height)
// 		return ;
// 	mlx_put_pixel(img, x, y, color);
// }

// uint32_t	get_height_color(float z, float z_max, float z_min)
// {
// 	float	ratio;
// 	uint8_t	r;
// 	uint8_t	g;
// 	uint8_t	b;

// 	if (z_max == z_min)
// 		return (0xFFFFFFFF);
// 	ratio = (z - z_min) / (z_max - z_min);
// 	if (ratio < 0.2f)
// 	{
// 		r = 0;
// 		g = (uint8_t)(100 + 155 * (ratio / 0.2f));
// 		b = 255;
// 	}
// 	else if (ratio < 0.4f)
// 	{
// 		r = 0;
// 		g = 255;
// 		b = (uint8_t)(255 * (1.0f - (ratio - 0.2f) / 0.2f));
// 	}
// 	else if (ratio < 0.6f)
// 	{
// 		r = (uint8_t)(255 * ((ratio - 0.4f) / 0.2f));
// 		g = 255;
// 		b = 0;
// 	}
// 	else if (ratio < 0.8f)
// 	{
// 		r = 255;
// 		g = (uint8_t)(255 * (1.0f - (ratio - 0.6f) / 0.2f));
// 		b = 0;
// 	}
// 	else
// 	{
// 		r = 255;
// 		g = (uint8_t)(100 * (1.0f - (ratio - 0.8f) / 0.2f));
// 		b = 0;
// 	}
// 	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
// }

// float	get_fraction(float x1, float x2, float x)
// {
// 	if (x1 != x2)
// 		return ((x - x1) / (x2 - x1));
// 	return (0.0f);
// }

// uint32_t	interpolate_color(uint32_t color_a, uint32_t color_b,
// 		float fraction)
// {
// 	uint8_t	r_a;
// 	uint8_t	g_a;
// 	uint8_t	b_a;
// 	uint8_t	r_b;
// 	uint8_t	g_b;
// 	uint8_t	b_b;
// 	uint8_t	r;
// 	uint8_t	g;
// 	uint8_t	b;

// 	r_a = (color_a >> 24) & 0xFF;
// 	g_a = (color_a >> 16) & 0xFF;
// 	b_a = (color_a >> 8) & 0xFF;
// 	r_b = (color_b >> 24) & 0xFF;
// 	g_b = (color_b >> 16) & 0xFF;
// 	b_b = (color_b >> 8) & 0xFF;
// 	r = (uint8_t)(r_a + (r_b - r_a) * fraction);
// 	g = (uint8_t)(g_a + (g_b - g_a) * fraction);
// 	b = (uint8_t)(b_a + (b_b - b_a) * fraction);
// 	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
// }

// void	draw_line(t_fdf *fdf, t_point p1, t_point p2)
// {
// 	uint32_t	color1;
// 	uint32_t	color2;

// 	color1 = get_height_color(p1.z, fdf->map.z_max, fdf->map.z_min);
// 	color2 = get_height_color(p2.z, fdf->map.z_max, fdf->map.z_min);
// 	draw_bresenham(fdf, p1, p2, color1, color2);
// }

// void	draw_bresenham(t_fdf *fdf, t_point p1, t_point p2, uint32_t color1,
// 		uint32_t color2)
// {
// 	int		v[6];
// 	int		cur_x;
// 	int		cur_y;
// 	float	fraction;
// 	uint32_t	current_color;

// 	cur_x = (int)p1.x;
// 	cur_y = (int)p1.y;
// 	v[0] = abs((int)p2.x - cur_x);
// 	v[1] = -abs((int)p2.y - cur_y);
// 	v[2] = -1;
// 	if (cur_x < (int)p2.x)
// 		v[2] = 1;
// 	v[3] = -1;
// 	if (cur_y < (int)p2.y)
// 		v[3] = 1;
// 	v[4] = v[0] + v[1];
// 	while (1)
// 	{
// 		if (abs((int)p2.x - (int)p1.x) > abs((int)p2.y - (int)p1.y))
// 			fraction = get_fraction(p1.x, p2.x, cur_x);
// 		else
// 			fraction = get_fraction(p1.y, p2.y, cur_y);
// 		current_color = interpolate_color(color1, color2, fraction);
// 		put_pixel(fdf->img, cur_x, cur_y, current_color);
// 		if (cur_x == (int)p2.x && cur_y == (int)p2.y)
// 			break ;
// 		v[5] = 2 * v[4];
// 		if (v[5] >= v[1] && cur_x != (int)p2.x)
// 		{
// 			v[4] += v[1];
// 			cur_x += v[2];
// 		}
// 		if (v[5] <= v[0] && cur_y != (int)p2.y)
// 		{
// 			v[4] += v[0];
// 			cur_y += v[3];
// 		}
// 	}
// }

// #include "../include/fdf.h"

// void	put_pixel(mlx_image_t *img, int x, int y, uint32_t color)
// {
// 	if (x < 0 || x >= (int)img->width || y < 0 || y >= (int)img->height)
// 		return ;
// 	mlx_put_pixel(img, x, y, color);
// }

// uint32_t	get_height_color(float z, float z_max, float z_min)
// {
// 	float	ratio;
// 	uint8_t	r;
// 	uint8_t	g;
// 	uint8_t	b;

// 	if (z_max == z_min)
// 		return (0xFFFFFFFF);
// 	ratio = (z - z_min) / (z_max - z_min);
// 	if (ratio < 0.25f)
// 	{
// 		r = 0;
// 		g = (uint8_t)(100 + 155 * (ratio / 0.25f));
// 		b = 255;
// 	}
// 	else if (ratio < 0.5f)
// 	{
// 		r = 0;
// 		g = 255;
// 		b = (uint8_t)(255 * (1.0f - (ratio - 0.25f) / 0.25f));
// 	}
// 	else if (ratio < 0.75f)
// 	{
// 		r = (uint8_t)(255 * ((ratio - 0.5f) / 0.25f));
// 		g = 255;
// 		b = 0;
// 	}
// 	else
// 	{
// 		r = 255;
// 		g = (uint8_t)(255 * (1.0f - (ratio - 0.75f) / 0.25f));
// 		b = 0;
// 	}
// 	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
// }

// float	get_fraction(float x1, float x2, float x)
// {
// 	if (x1 != x2)
// 		return ((x - x1) / (x2 - x1));
// 	return (0.0f);
// }

// uint32_t	interpolate_color(uint32_t color_a, uint32_t color_b,
// 		float fraction)
// {
// 	uint8_t	r_a;
// 	uint8_t	g_a;
// 	uint8_t	b_a;
// 	uint8_t	r_b;
// 	uint8_t	g_b;
// 	uint8_t	b_b;
// 	uint8_t	r;
// 	uint8_t	g;
// 	uint8_t	b;

// 	r_a = (color_a >> 24) & 0xFF;
// 	g_a = (color_a >> 16) & 0xFF;
// 	b_a = (color_a >> 8) & 0xFF;
// 	r_b = (color_b >> 24) & 0xFF;
// 	g_b = (color_b >> 16) & 0xFF;
// 	b_b = (color_b >> 8) & 0xFF;
// 	r = (uint8_t)(r_a + (r_b - r_a) * fraction);
// 	g = (uint8_t)(g_a + (g_b - g_a) * fraction);
// 	b = (uint8_t)(b_a + (b_b - b_a) * fraction);
// 	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
// }

// void	draw_line(t_fdf *fdf, t_point p1, t_point p2)
// {
// 	uint32_t	color1;
// 	uint32_t	color2;

// 	color1 = get_height_color(p1.z, fdf->map.z_max, fdf->map.z_min);
// 	color2 = get_height_color(p2.z, fdf->map.z_max, fdf->map.z_min);
// 	draw_bresenham(fdf, p1, p2, color1, color2);
// }

// void	draw_bresenham(t_fdf *fdf, t_point p1, t_point p2, uint32_t color1,
// 		uint32_t color2)
// {
// 	int		v[6];
// 	int		cur_x;
// 	int		cur_y;
// 	float	fraction;
// 	uint32_t	current_color;

// 	cur_x = (int)p1.x;
// 	cur_y = (int)p1.y;
// 	v[0] = abs((int)p2.x - cur_x);
// 	v[1] = -abs((int)p2.y - cur_y);
// 	v[2] = -1;
// 	if (cur_x < (int)p2.x)
// 		v[2] = 1;
// 	v[3] = -1;
// 	if (cur_y < (int)p2.y)
// 		v[3] = 1;
// 	v[4] = v[0] + v[1];
// 	while (1)
// 	{
// 		if (abs((int)p2.x - (int)p1.x) > abs((int)p2.y - (int)p1.y))
// 			fraction = get_fraction(p1.x, p2.x, cur_x);
// 		else
// 			fraction = get_fraction(p1.y, p2.y, cur_y);
// 		current_color = interpolate_color(color1, color2, fraction);
// 		put_pixel(fdf->img, cur_x, cur_y, current_color);
// 		if (cur_x == (int)p2.x && cur_y == (int)p2.y)
// 			break ;
// 		v[5] = 2 * v[4];
// 		if (v[5] >= v[1] && cur_x != (int)p2.x)
// 		{
// 			v[4] += v[1];
// 			cur_x += v[2];
// 		}
// 		if (v[5] <= v[0] && cur_y != (int)p2.y)
// 		{
// 			v[4] += v[0];
// 			cur_y += v[3];
// 		}
// 	}
// }

#include "../include/fdf.h"

void	put_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	uint32_t	*pixels;
	uint32_t	index;

	if (x < 0 || x >= (int)img->width || y < 0 || y >= (int)img->height)
		return ;
	pixels = (uint32_t *)img->pixels;
	index = (uint32_t)(y * img->width + x);
	pixels[index] = color;
}

uint32_t	get_height_color(float z, float z_max, float z_min)
{
	float	ratio;
	uint8_t	rgb[3];

	if (z_max == z_min)
		return (0xFFFFFFFF);
	ratio = (z - z_min) / (z_max - z_min);
	rgb[0] = (uint8_t)(50 + (205 * ratio));
	rgb[1] = (uint8_t)(50 + (205 * ratio));
	rgb[2] = (uint8_t)255;
	return ((rgb[0] << 24) | (rgb[1] << 16) | (rgb[2] << 8) | 0xFF);
}

float	get_fraction(float x1, float x2, float x)
{
	if (x1 != x2)
		return ((x - x1) / (x2 - x1));
	return (0.0f);
}

uint32_t	interpolate_color(uint32_t c1, uint32_t c2, float fraction)
{
	uint8_t	rgb[3];

	rgb[0] = (uint8_t)((c1 >> 24 & 0xFF) + ((c2 >> 24 & 0xFF)
				- (c1 >> 24 & 0xFF)) * fraction);
	rgb[1] = (uint8_t)((c1 >> 16 & 0xFF) + ((c2 >> 16 & 0xFF)
				- (c1 >> 16 & 0xFF)) * fraction);
	rgb[2] = (uint8_t)((c1 >> 8 & 0xFF) + ((c2 >> 8 & 0xFF) - (c1 >> 8 & 0xFF))
			* fraction);
	return ((rgb[0] << 24) | (rgb[1] << 16) | (rgb[2] << 8) | 0xFF);
}
