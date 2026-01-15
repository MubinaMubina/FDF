/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 07:47:20 by mmubina           #+#    #+#             */
/*   Updated: 2026/01/14 18:47:06 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	set_view(t_fdf *f, double x, double y, double z, int type)
{
	f->cam.angle_x = x;
	f->cam.angle_y = y;
	f->cam.angle_z = z;
	f->cam.type = type;
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_fdf	*f;

	f = (t_fdf *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(f->mlx);
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_UP)
			f->cam.offset_y -= 10;
		if (keydata.key == MLX_KEY_DOWN)
			f->cam.offset_y += 10;
		if (keydata.key == MLX_KEY_LEFT)
			f->cam.offset_x -= 10;
		if (keydata.key == MLX_KEY_RIGHT)
			f->cam.offset_x += 10;
		if (keydata.key == MLX_KEY_1)
			set_view(f, 0, 0, 0, PARALLEL);
		if (keydata.key == MLX_KEY_2)
			set_view(f, 1.5708, 0, 0, PARALLEL);
		if (keydata.key == MLX_KEY_3)
			set_view(f, 0, 1.5708, -1.5708, PARALLEL);
		if (keydata.key == MLX_KEY_I)
			set_view(f, -0.615480, 0.523599, 0, ISOMETRIC);
		draw_map(f);
	}
}

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	t_fdf	*f;

	(void)xdelta;
	f = (t_fdf *)param;
	if (ydelta > 0)
		f->cam.zoom *= 1.1f;
	else
		f->cam.zoom /= 1.1f;
	if (f->cam.zoom < 1.0f)
		f->cam.zoom = 1.0f;
	draw_map(f);
}

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_fdf	*f;

	f = (t_fdf *)param;
	if (width <= 0 || height <= 0)
		return ;
	mlx_delete_image(f->mlx, f->img);
	f->img = mlx_new_image(f->mlx, width, height);
	if (!f->img)
		return ;
	mlx_image_to_window(f->mlx, f->img, 0, 0);
	f->cam.offset_x = width / 2;
	f->cam.offset_y = height / 2;
	draw_map(f);
}
