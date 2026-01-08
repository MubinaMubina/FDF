/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 07:47:07 by mmubina           #+#    #+#             */
/*   Updated: 2026/01/08 00:14:44 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/fdf.h"

// t_point	apply_transforms(t_point p, t_fdf *fdf)
// {
// 	t_point	res;

// 	// 1. Pivot Fix: Center the map coordinates on (0,0)
// 	res.x = p.x - (fdf->map.width / 2);
// 	res.y = p.y - (fdf->map.height / 2);
// 	res.z = p.z;
// 	// 2. Apply Scale/Zoom
// 	res.x *= fdf->cam.zoom;
// 	res.y *= fdf->cam.zoom;
// 	res.z *= (fdf->cam.zoom * fdf->cam.z_scale);
// 	// 3. Apply Projection (Isometric or 2D)
// 	res = project_point(res, fdf);
// 	// 4. Offset to Center of Window
// 	res.x += fdf->cam.offset_x;
// 	res.y += fdf->cam.offset_y;
// 	res.color = p.color;
// 	return (res);
// }

// // void	draw_map(t_fdf *fdf)
// // {
// // 	int	x;
// // 	int	y;

// // 	// Pure Black Background
// // 	ft_memset(fdf->img->pixels, 0, fdf->img->width * fdf->img->height
// // 		* sizeof(int32_t));
// // 	y = 0;
// // 	while (y < fdf->map.height)
// // 	{
// // 		x = 0;
// // 		while (x < fdf->map.width)
// // 		{
// // 			if (x < fdf->map.width - 1)
// // 				draw_line(fdf, apply_transforms(fdf->map.points[y][x], fdf),
// // 					apply_transforms(fdf->map.points[y][x + 1], fdf));
// // 			if (y < fdf->map.height - 1)
// // 				draw_line(fdf, apply_transforms(fdf->map.points[y][x], fdf),
// // 					apply_transforms(fdf->map.points[y + 1][x], fdf));
// // 			x++;
// // 		}
// // 		y++;
// // 	}
// // }

// static void	clear_image(mlx_image_t *img)
// {
// 	uint32_t	i;
// 	uint32_t	total_pixels;

// 	total_pixels = img->width * img->height;
// 	i = 0;
// 	while (i < total_pixels)
// 	{
// 		mlx_put_pixel(img, i % img->width, i / img->width, 0x000000FF);
// 		i++;
// 	}
// }

// void	draw_map(t_fdf *fdf)
// {
// 	int	x;
// 	int	y;

// 	clear_image(fdf->img);
// 	y = -1;
// 	while (++y < fdf->map.height)
// 	{
// 		x = -1;
// 		while (++x < fdf->map.width)
// 		{
// 			if (x < fdf->map.width - 1)
// 				draw_line(fdf, apply_transforms(fdf->map.points[y][x], fdf),
// 					apply_transforms(fdf->map.points[y][x + 1], fdf));
// 			if (y < fdf->map.height - 1)
// 				draw_line(fdf, apply_transforms(fdf->map.points[y][x], fdf),
// 					apply_transforms(fdf->map.points[y + 1][x], fdf));
// 		}
// 	}
// }
#include "../include/fdf.h"

t_point	apply_transforms(t_point p, t_fdf *fdf)
{
	t_point	res;

	res.x = p.x - (fdf->map.width / 2.0f);
	res.y = p.y - (fdf->map.height / 2.0f);
	res.z = p.z;
	res.x *= fdf->cam.zoom;
	res.y *= fdf->cam.zoom;
	res.z *= (fdf->cam.zoom * fdf->cam.z_scale);
	res = project_point(res, fdf);
	res.x += fdf->cam.offset_x;
	res.y += fdf->cam.offset_y;
	res.color = p.color;
	return (res);
}

void	clear_image(mlx_image_t *img)
{
	uint32_t	*pixels;
	uint32_t	i;

	pixels = (uint32_t *)img->pixels;
	i = 0;
	while (i < img->width * img->height)
	{
		pixels[i] = 0x000000FF;
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

