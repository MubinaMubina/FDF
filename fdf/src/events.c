/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 07:47:20 by mmubina           #+#    #+#             */
/*   Updated: 2026/01/04 07:50:42 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(fdf->mlx);
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		fdf->cam.offset_y -= 10;
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		fdf->cam.offset_y += 10;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		fdf->cam.offset_x -= 10;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		fdf->cam.offset_x += 10;
}

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	t_fdf	*fdf;

	(void)xdelta;
	fdf = (t_fdf *)param;
	if (ydelta > 0)
		fdf->cam.zoom *= 1.1f;
	else
		fdf->cam.zoom /= 1.1f;
	if (fdf->cam.zoom < 1)
		fdf->cam.zoom = 1;
	if (fdf->cam.zoom > 200)
		fdf->cam.zoom = 200;
}

void	close_hook(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	free_map(&fdf->map);
	mlx_delete_image(fdf->mlx, fdf->img);
	mlx_terminate(fdf->mlx);
}

void	event_placeholder(void)
{
	return ;
}
