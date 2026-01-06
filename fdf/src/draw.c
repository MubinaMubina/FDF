/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 07:47:07 by mmubina           #+#    #+#             */
/*   Updated: 2026/01/04 16:43:46 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/fdf.h"

static t_point	apply_transforms(t_point p, t_fdf *fdf)
{
	t_point	res;

	res.x = p.x * fdf->cam.zoom;
	res.y = p.y * fdf->cam.zoom;
	res.z = p.z * (fdf->cam.zoom / 10); // Scale Z relative to zoom
	res = isometric_projection(res);
	res.x += fdf->cam.offset_x;
	res.y += fdf->cam.offset_y;
	return (res);
}

static void	clear_image(mlx_image_t *img)
{
	uint32_t	i;
	uint32_t	total_pixels;

	total_pixels = img->width * img->height;
	i = 0;
	while (i < total_pixels)
	{
		mlx_put_pixel(img, i % img->width, i / img->width, 0x000000FF);
		i++;
	}
}

void	draw_map(t_fdf *fdf)
{
	int	x;
	int	y;

	clear_image(fdf->img);
	y = -1;
	while (++y < fdf->map.height)
	{
		x = -1;
		while (++x < fdf->map.width)
		{
			if (x < fdf->map.width - 1)
				draw_line(fdf, apply_transforms(fdf->map.points[y][x], fdf),
					apply_transforms(fdf->map.points[y][x + 1], fdf));
			if (y < fdf->map.height - 1)
				draw_line(fdf, apply_transforms(fdf->map.points[y][x], fdf),
					apply_transforms(fdf->map.points[y + 1][x], fdf));
		}
	}
}
