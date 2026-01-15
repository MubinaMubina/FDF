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
