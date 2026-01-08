/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 07:42:07 by mmubina           #+#    #+#             */
/*   Updated: 2026/01/07 21:51:05 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/fdf.h"

// void	init_camera(t_fdf *fdf)
// {
// 	float	zoom_x;
// 	float	zoom_y;

// 	zoom_x = (WIN_WIDTH * 0.35) / fdf->map.width;
// 	zoom_y = (WIN_HEIGHT * 0.35) / fdf->map.height;
// 	if (zoom_x < zoom_y)
// 		fdf->cam.zoom = zoom_x;
// 	else
// 		fdf->cam.zoom = zoom_y;
// 	if (fdf->cam.zoom < 1)
// 		fdf->cam.zoom = 1;
// 	fdf->cam.offset_x = WIN_WIDTH / 2;
// 	fdf->cam.offset_y = WIN_HEIGHT / 2;
// 	fdf->cam.z_scale = 1.0;
// 	set_view(fdf, 0.523, 0.523, 0.0, ISOMETRIC);
// }

// int	setup_mlx(t_fdf *fdf)
// {
// 	fdf->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "FdF - mmubina", true);
// 	if (!fdf->mlx)
// 		return (0);
// 	fdf->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
// 	if (!fdf->img)
// 	{
// 		mlx_terminate(fdf->mlx);
// 		return (0);
// 	}
// 	return (1);
// }

// int	setup_fdf(t_fdf *fdf, const char *filename)
// {
// 	ft_memset(fdf, 0, sizeof(t_fdf));
// 	fdf->map = parse_map(filename);
// 	if (!fdf->map.points)
// 		return (0);
// 	init_z_minmax(&fdf->map);
// 	return (1);
// }

// int	main(int argc, char **argv)
// {
// 	t_fdf	fdf;

// 	if (argc != 2 || !setup_fdf(&fdf, argv[1]) || !setup_mlx(&fdf))
// 		return (1);
// 	init_camera(&fdf);
// 	mlx_resize_hook(fdf.mlx, &resize_hook, &fdf);
// 	mlx_image_to_window(fdf.mlx, fdf.img, 0, 0);
// 	draw_map(&fdf);
// 	mlx_key_hook(fdf.mlx, &key_hook, &fdf);
// 	mlx_loop(fdf.mlx);
// 	return (0);
// }

#include "../include/fdf.h"

void	init_camera(t_fdf *fdf)
{
	float	zoom_x;
	float	zoom_y;

	zoom_x = (WIN_WIDTH * 0.35) / fdf->map.width;
	zoom_y = (WIN_HEIGHT * 0.35) / fdf->map.height;
	if (zoom_x < zoom_y)
		fdf->cam.zoom = zoom_x;
	else
		fdf->cam.zoom = zoom_y;
	if (fdf->cam.zoom < 1)
		fdf->cam.zoom = 1;
	fdf->cam.offset_x = WIN_WIDTH / 2;
	fdf->cam.offset_y = WIN_HEIGHT / 2;
	fdf->cam.z_scale = 1.0;
	set_view(fdf, 0, 0, 0, ISOMETRIC);
}

int	setup_mlx(t_fdf *fdf)
{
	fdf->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "FdF - mmubina", true);
	if (!fdf->mlx)
		return (0);
	fdf->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!fdf->img)
	{
		mlx_terminate(fdf->mlx);
		return (0);
	}
	return (1);
}

int	setup_fdf(t_fdf *fdf, const char *filename)
{
	ft_memset(fdf, 0, sizeof(t_fdf));
	fdf->map = parse_map(filename);
	if (!fdf->map.points)
		return (0);
	init_z_minmax(&fdf->map);
	return (1);
}

int	main(int argc, char **argv)
{
	t_fdf fdf;

	if (argc != 2 || !setup_fdf(&fdf, argv[1]) || !setup_mlx(&fdf))
		return (1);
	init_camera(&fdf);
	mlx_resize_hook(fdf.mlx, &resize_hook, &fdf);
	mlx_image_to_window(fdf.mlx, fdf.img, 0, 0);
	draw_map(&fdf);
	mlx_key_hook(fdf.mlx, &key_hook, &fdf);
	mlx_loop(fdf.mlx);
	return (0);
}