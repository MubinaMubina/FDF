/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 07:42:07 by mmubina           #+#    #+#             */
/*   Updated: 2026/01/19 20:47:03 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	calc_camera_zoom(t_fdf *fdf)
{
	float	dist_x;
	float	dist_y;
	float	z_range;

	dist_x = (fdf->map.width + fdf->map.height) * cos(0.523599);
	z_range = fdf->map.z_max - fdf->map.z_min;
	dist_y = (fdf->map.width + fdf->map.height) * sin(0.523599) + z_range;
	fdf->cam.zoom = (WIN_WIDTH * 0.7) / dist_x;
	if ((WIN_HEIGHT * 0.7) / dist_y < fdf->cam.zoom)
		fdf->cam.zoom = (WIN_HEIGHT * 0.7) / dist_y;
	if (fdf->cam.zoom < 1)
		fdf->cam.zoom = 1;
	if (z_range > (fdf->map.width + fdf->map.height))
		fdf->cam.z_scale = (float)(fdf->map.width + fdf->map.height)
			/ (z_range * 1.5);
	else
		fdf->cam.z_scale = 1.0;
}

static void	init_camera(t_fdf *fdf)
{
	t_view	iso;

	calc_camera_zoom(fdf);
	fdf->cam.offset_x = WIN_WIDTH / 2;
	fdf->cam.offset_y = WIN_HEIGHT / 2;
	iso.angle_x = 0;
	iso.angle_y = 0;
	iso.angle_z = 0;
	iso.type = ISOMETRIC;
	set_view(fdf, iso);
}

static int	setup_mlx(t_fdf *fdf)
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

static int	setup_fdf(t_fdf *fdf, const char *filename)
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
	t_fdf	fdf;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./fdf <map.fdf>", 2);
		return (1);
	}
	if (!setup_fdf(&fdf, argv[1]) || !setup_mlx(&fdf))
	{
		ft_putendl_fd("Error: Failed to initialize", 2);
		return (1);
	}
	init_camera(&fdf);
	mlx_image_to_window(fdf.mlx, fdf.img, 0, 0);
	draw_map(&fdf);
	mlx_resize_hook(fdf.mlx, &resize_hook, &fdf);
	mlx_key_hook(fdf.mlx, &key_hook, &fdf);
	mlx_scroll_hook(fdf.mlx, &scroll_hook, &fdf);
	mlx_loop(fdf.mlx);
	free_map(&fdf.map);
	mlx_terminate(fdf.mlx);
	return (0);
}
