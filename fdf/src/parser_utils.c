/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 07:44:20 by mmubina           #+#    #+#             */
/*   Updated: 2026/01/14 18:46:39 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	free_split_safe(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	init_z_minmax(t_map *map)
{
	int	y;
	int	x;

	map->z_max = map->points[0][0].z;
	map->z_min = map->points[0][0].z;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->points[y][x].z > map->z_max)
				map->z_max = map->points[y][x].z;
			if (map->points[y][x].z < map->z_min)
				map->z_min = map->points[y][x].z;
			x++;
		}
		y++;
	}
}

void	free_map(t_map *map)
{
	int	i;

	if (!map || !map->points)
		return ;
	i = 0;
	while (i < map->height)
	{
		free(map->points[i]);
		i++;
	}
	free(map->points);
	ft_memset(map, 0, sizeof(t_map));
}

void	validate_and_setup(t_map *map)
{
	if (!map || !map->points || map->height <= 0 || map->width <= 0)
	{
		ft_putendl_fd("Error: Invalid map", 2);
		return ;
	}
	init_z_minmax(map);
}

int	count_width(char *line)
{
	int		count;
	char	**split;

	if (!line)
		return (0);
	split = ft_split(line, ' ');
	if (!split)
		return (0);
	count = 0;
	while (split[count])
		count++;
	free_split_safe(split);
	return (count);
}
