/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 07:47:07 by mmubina           #+#    #+#             */
/*   Updated: 2026/01/04 12:13:25 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"

static t_point	apply_transforms(t_point p, t_fdf *fdf)
{
	t_point	result;

	result = isometric_projection(p);
	result = scale_point(result, fdf->cam.zoom);
	result = translate_point(result, fdf->cam.offset_x, fdf->cam.offset_y);
	return (result);
}

static void	clear_image(mlx_image_t *img)
{
	int	i;

	i = 0;
	while (i < (int)(img->width * img->height))
	{
		((uint32_t *)img->pixels)[i] = 0x000000FF;
		i++;
	}
}

static void	draw_horizontal_lines(t_fdf *fdf)
{
	int		x;
	int		y;
	t_point	p1;
	t_point	p2;

	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width - 1)
		{
			p1 = apply_transforms(fdf->map.points[y][x], fdf);
			p2 = apply_transforms(fdf->map.points[y][x + 1], fdf);
			draw_line(fdf, p1, p2);
			x++;
		}
		y++;
	}
}

void	draw_map(t_fdf *fdf)
{
	int		x;
	int		y;
	t_point	p1;
	t_point	p2;

	if (!fdf || !fdf->map.points || fdf->map.height <= 1)
		return ;
	clear_image(fdf->img);
	draw_horizontal_lines(fdf);
	y = 0;
	while (y < fdf->map.height - 1)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			p1 = apply_transforms(fdf->map.points[y][x], fdf);
			p2 = apply_transforms(fdf->map.points[y + 1][x], fdf);
			draw_line(fdf, p1, p2);
			x++;
		}
		y++;
	}
}