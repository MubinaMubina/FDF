/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 07:42:07 by mmubina           #+#    #+#             */
/*   Updated: 2026/01/04 16:53:37 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	init_camera(t_cam *cam)
{
	cam->zoom = 20;
	cam->offset_x = WIN_WIDTH / 2;
	cam->offset_y = WIN_HEIGHT / 2;
	cam->angle_x = 0;
	cam->angle_y = 0;
	cam->angle_z = 0;
}

static int	setup_mlx(t_fdf *fdf)
{
	fdf->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "FDF", false);
	if (!fdf->mlx)
		return (0);
	fdf->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!fdf->img)
		return (0);
	return (1);
}

static int	setup_fdf(t_fdf *fdf, const char *filename)
{
	ft_memset(fdf, 0, sizeof(t_fdf));
	fdf->map = parse_map(filename);
	if (!fdf->map.points)
	{
		write(2, "Error: Failed to parse map\n", 27);
		return (0);
	}
	init_z_minmax(&fdf->map);
	init_camera(&fdf->cam);
	if (!setup_mlx(fdf))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
	{
		write(2, "Usage: ./fdf <map_file>\n", 24);
		return (1);
	}
	if (!setup_fdf(&fdf, argv[1]))
		return (1);
	printf("Map parsed: %d x %d\n", fdf.map.width, fdf.map.height);
	// Debug line
	draw_map(&fdf);
	draw_map(&fdf);
	mlx_image_to_window(fdf.mlx, fdf.img, 0, 0);
	mlx_key_hook(fdf.mlx, &key_hook, &fdf);
	mlx_scroll_hook(fdf.mlx, &scroll_hook, &fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	free_map(&fdf.map);
	return (0);
}
