/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 07:47:07 by mmubina           #+#    #+#             */
/*   Updated: 2026/01/14 21:06:51 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static float	calc_z_offset(t_fdf *fdf)
{
	return (((fdf->map.z_max + fdf->map.z_min) * fdf->cam.zoom
			* fdf->cam.z_scale) / 2.0f);
}

t_point	apply_transforms(t_point p, t_fdf *fdf)
{
	t_point	res;

	res.x = (p.x - (fdf->map.width - 1) / 2.0f);
	res.y = (p.y - (fdf->map.height - 1) / 2.0f);
	res.z = p.z * fdf->cam.z_scale;
	res.x *= fdf->cam.zoom;
	res.y *= fdf->cam.zoom;
	res.z *= fdf->cam.zoom;
	res = project_point(res, fdf);
	res.x += fdf->cam.offset_x;
	res.y += fdf->cam.offset_y + calc_z_offset(fdf);
	res.color = p.color;
	return (res);
}

uint32_t	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	clear_image(mlx_image_t *img)
{
	uint32_t	*pixels;
	uint32_t	i;
	uint32_t	color;

	color = 0xFF0A0A0A;
	pixels = (uint32_t *)img->pixels;
	i = 0;
	while (i < img->width * img->height)
	{
		pixels[i] = color;
		i++;
	}
}

void	draw_map(t_fdf *fdf)
{
	int	x;
	int	y;

	clear_image(fdf->img);
	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			if (x < fdf->map.width - 1)
				draw_line(fdf, apply_transforms(fdf->map.points[y][x], fdf),
					apply_transforms(fdf->map.points[y][x + 1], fdf));
			if (y < fdf->map.height - 1)
				draw_line(fdf, apply_transforms(fdf->map.points[y][x], fdf),
					apply_transforms(fdf->map.points[y + 1][x], fdf));
			x++;
		}
		y++;
	}
}
