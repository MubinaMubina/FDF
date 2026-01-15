/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 07:47:20 by mmubina           #+#    #+#             */
/*   Updated: 2026/01/15 18:29:58 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	set_view(t_fdf *f, t_view view)
{
	f->cam.angle_x = view.angle_x;
	f->cam.angle_y = view.angle_y;
	f->cam.angle_z = view.angle_z;
	f->cam.type = view.type;
}

static t_view	make_view(double x, double y, double z, int type)
{
	t_view	v;

	v.angle_x = x;
	v.angle_y = y;
	v.angle_z = z;
	v.type = type;
	return (v);
}

static void	handle_keys(mlx_key_data_t keydata, t_fdf *f)
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
		set_view(f, make_view(0, 0, 0, PARALLEL));
	if (keydata.key == MLX_KEY_2)
		set_view(f, make_view(1.5708, 0, 0, PARALLEL));
	if (keydata.key == MLX_KEY_3)
		set_view(f, make_view(0, 1.5708, -1.5708, PARALLEL));
	if (keydata.key == MLX_KEY_I)
		set_view(f, make_view(-0.615480, 0.523599, 0, ISOMETRIC));
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_fdf	*f;

	f = (t_fdf *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(f->mlx);
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		handle_keys(keydata, f);
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
