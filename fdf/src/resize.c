/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:00:00 by mmubina           #+#    #+#             */
/*   Updated: 2026/01/19 23:52:05 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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

t_map	parse_map(const char *filename)
{
	t_map	map;
	int		fd;

	ft_memset(&map, 0, sizeof(t_map));
	fd = open_and_allocate(filename, &map);
	if (fd < 0)
		return (map);
	if (!read_map_lines(fd, &map))
	{
		close(fd);
		return (map);
	}
	close(fd);
	return (map);
}
